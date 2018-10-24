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

int main(int argc, char* argv[])
{
	ari::Engine* p_device = new ari::Engine();
	ari::InitParams p{};
	p.Program = new ShivaEditor("ShivaEditor");
	p_device->Init(p);

	while (p_device->Run())
	{

	}
	delete p_device;
	return 0;
}
