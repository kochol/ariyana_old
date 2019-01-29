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

static CR_STATE ari::Engine* p_device = nullptr;
static CR_STATE ari::InitParams* p = new ari::InitParams;
static CR_STATE ShivaEditor* prog = new ShivaEditor("ShivaEditor");

extern "C"
{
	CR_EXPORT int cr_main(struct cr_plugin *ctx, enum cr_op operation)
	{
		assert(ctx);
		switch (operation) {
		case CR_LOAD:
			{
				if (p_device == nullptr)
				{
					printf("CR_LOAD\n");
					p_device = new ari::Engine();
					p->Program = prog;
					p_device->Init(p);
					p_device->plugin_manager.Load("bimg", nullptr);
				}
				else
				{
					printf("Reloaded: %d\n", ctx->version);
					ari::g_pEngine = p_device;
					p->Program = prog;
					p_device->SetParams(p);
					p_device->UnlockUpdateThread();
				}
				return 0;
			}
		case CR_UNLOAD:
			{
				printf("CR_UNLOAD\n");
				p->Program = nullptr;
				p_device->LockUpdateThread();
			}
		case CR_STEP:
			{
				return p_device->Run();
			}
		}
		return 0;
	}
}