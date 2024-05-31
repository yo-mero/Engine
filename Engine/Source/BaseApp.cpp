
#include "BaseApph.h"

HRESULT BaseApp::init()
{
    return E_NOTIMPL;
}

void BaseApp::update()
{
}

void BaseApp::render()
{
}

void BaseApp::destroy()
{
}

int
BaseApp::run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //inicializa la ventana
    if (FAILED(m_window.Init(hInstance, nCmdShow, nullptr)))
        return 0;

    //inicializa los recursos de la app
    if (FAILED(init()))
    {
        destroy();
        return 0;
    }

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            update();   //Se actualiza tod a la parte matem�tica y f�sica
            render();   //Se actualiza todo lo que tenga qwue ver con seteos o que aparezaca en pantalla
        }
    }

    destroy();

    return (int)msg.wParam;
}

LRESULT BaseApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}