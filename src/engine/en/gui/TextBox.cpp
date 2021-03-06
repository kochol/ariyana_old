#include "..\..\..\..\include\ari\en\gui\TextBox.hpp"
#include "dear-imgui/imgui.h"
#include "bx/bx.h"
#include "bx/string.h"

ari::TextBox::TextBox(size_t maxLength): Label(nullptr), m_MaxLength(maxLength)
{
	Text = new char[maxLength];
	bx::memSet(Text, 0, maxLength);
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

void ari::TextBox::SetText(const char * _text) const
{
	bx::strCopy(Text, m_MaxLength, _text);
}
