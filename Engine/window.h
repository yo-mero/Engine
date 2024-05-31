#pragma once
#include"PreRequisites.h"

class
	window {
public:
	Window() = default;
	~Window() = default;

	HRESULT Init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);
	void update();
	void render();
	void destroy();
public:
	HWND m_hWnd = nullptr;
	using int m_width;
	using int m_height;
private:
	HINSTANCE m_hInst = nullptr;
	RECT m_rect;
  std :: string m_windowName = "Engine";

};