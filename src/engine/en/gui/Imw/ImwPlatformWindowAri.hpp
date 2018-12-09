#pragma once
#include "ImwPlatformWindow.h"

namespace ari
{
	class ImwPlatformWindowAri: public ImWindow::ImwPlatformWindow
	{
	public:
		ImwPlatformWindowAri(ImWindow::EPlatformWindowType eType, bool bCreateContext);
		~ImwPlatformWindowAri() override;

		bool Init(ImwPlatformWindow* pParent) override;

		ImVec2 GetPosition() const override;
		ImVec2 GetSize() const override;
		ImVec2 GetNormalPosition() const override;
		ImVec2 GetNormalSize() const override;

		bool IsWindowMaximized() const override;
		bool IsWindowMinimized() const override;

		void Show(bool bShow) override;
		void SetSize(int iWidth, int iHeight) override;
		void SetPosition(int iX, int iY) override;
		void SetWindowMaximized(bool bMaximized) override;
		void SetWindowMinimized(bool bMinimized) override;
		void SetTitle(const char* pTtile) override;

	protected:
		void PreUpdate() override;
		void PreRender() override;
		void OnOverlay() override;
		void RenderDrawLists(ImDrawData* pDrawData) override;
	};

} // ari
