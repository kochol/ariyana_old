#pragma once
#include "Gui.hpp"

namespace ari
{
	class ARI_API TextBox: public Gui
	{
	public:

		TextBox(size_t maxLength = 128);

		~TextBox() override;

		bool BeginRender() override;

		void SetText(const char* _text) const;

		char* Text;
		char* Label;

	private:
		size_t m_MaxLength;

	};

} // ari
