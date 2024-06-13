
#include "BaseApph.h"

HRESULT BaseApp::init()
{
    return E_NOTIMPL;
}
//init: Devuelve E_NOTIMPL, que es un valor de error est�ndar en Windows indicando que la funci�n no est� implementada.
//Se espera que en una implementaci�n completa, este m�todo inicialice los recursos de la aplicaci�n.
void BaseApp::update()
{
}
//update: M�todo vac�o.En una implementaci�n completa, este m�todo actualizar�a el estado de la aplicaci�n, 
//probablemente manejando la l�gica del juego, la f�sica,
void BaseApp::render()
{
}
//render: M�todo vac�o.En una implementaci�n completa, este m�todo ser�a responsable de renderizar gr�ficos en la pantalla.
void BaseApp::destroy()
{
}
//destroy: M�todo vac�o.En una implementaci�n completa, este m�todo limpiar�a los recursos y cerrar�a la aplicaci�n de manera ordenada.
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
//run: Este m�todo es el n�cleo de la aplicaci�n, iniciando el bucle principal de mensajes de Windows.
// 
//UNREFERENCED_PARAMETER(hPrevInstance); y UNREFERENCED_PARAMETER(lpCmdLine); : Macros para evitar advertencias del compilador sobre par�metros no utilizados.
// 
//if (FAILED(m_window.Init(hInstance, nCmdShow, nullptr))) return 0; : Inicializa la ventana, y si falla, retorna 0.
// 
//if (FAILED(init())) { destroy(); return 0; } : Inicializa los recursos de la aplicaci�n y si falla, destruye los recursos y retorna 0.
// 
//while (WM_QUIT != msg.message) : Bucle principal que procesa mensajes de Windows.
// 
//PeekMessage y DispatchMessage : Procesa los mensajes de la cola de mensajes.
// 
//update() y render() : Llama a los m�todos para actualizar el estado de la aplicaci�n y renderizar gr�ficos cuando no hay mensajes.
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
//WndProc: El procedimiento de ventana maneja los mensajes de Windows.
//WM_PAINT : Inicia y finaliza la pintura de la ventana.
//WM_DESTROY : Env�a un mensaje de salida cuando la ventana se cierra.
//default: Llama al procedimiento de ventana por defecto para manejar los mensajes no procesados.