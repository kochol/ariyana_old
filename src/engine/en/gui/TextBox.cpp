#include "..\..\..\..\include\ari\en\gui\TextBox.hpp"
#include "dear-imgui/imgui.h"

ari::TextBox::TextBox(size_t maxLength): Label(nullptr), m_MaxLength(maxLength)
{
	Text = new char[maxLength];
}

ari::TextBox::~TextBox()
{
	delete[] Text;
}

bool ari::TextBox::BeginRender()
{
	ImGui::InputText(Label, Text, m_MaxLength);
	return true;
}
