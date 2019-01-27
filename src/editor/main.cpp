#include <ari/Engine.hpp>
#include "ari/Program.hpp"
#include "ari/en/World.hpp"
#include "ari/en/Entity.hpp"
#include "ari/en/gui/GuiSystem.hpp"
#include "ari/en/gui/Window.hpp"
#include "ari/en/gui/CheckBox.hpp"
#include "ari/en/gui/Label.hpp"
#include "ari/en/gui/Dock.hpp"
#include "shiva/Editor.hpp"

#include "../../deps/cr/cr.h"

class ShivaEditor : public ari::IProgram
{
public:
	explicit ShivaEditor(const char* programName)
		: IProgram(programName)
	{
	}

	~ShivaEditor() override = default;

	void Init() override
	{
		// Init editor
		m_editor.Init();
	}

	bool Update(uint32_t frame_number, float elasped) override
	{
		m_editor.Update(elasped);
		return true;
	}

	int Shutdown() override
	{
		return 0;
	}

	shiva::Editor m_editor;
};

std::unique_ptr<ari::Engine> p_device(new ari::Engine());
std::shared_ptr<ari::InitParams> p(new ari::InitParams);

extern "C"
{
	CR_EXPORT int cr_main(struct cr_plugin *ctx, enum cr_op operation)
	{
		assert(ctx);
		switch (operation) {
		case CR_LOAD:
			{
				p->Program.reset(new ShivaEditor("ShivaEditor"));
				p_device->Init(p);
				p_device->plugin_manager.Load("bimg", nullptr);
				return 0;
			}
		case CR_UNLOAD:
			{
				
			}
		case CR_STEP:
			{
				return p_device->Run();
			}
		}
		return 0;
	}
}