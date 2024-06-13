
#include "BaseApph.h"

HRESULT BaseApp::init()
{
    return E_NOTIMPL;
}
//init: Devuelve E_NOTIMPL, que es un valor de error estándar en Windows indicando que la función no está implementada.
//Se espera que en una implementación completa, este método inicialice los recursos de la aplicación.
void BaseApp::update()
{
}
//update: Método vacío.En una implementación completa, este método actualizaría el estado de la aplicación, 
//probablemente manejando la lógica del juego, la física,
void BaseApp::render()
{
}
//render: Método vacío.En una implementación completa, este método sería responsable de renderizar gráficos en la pantalla.
void BaseApp::destroy()
{
}
//destroy: Método vacío.En una implementación completa, este método limpiaría los recursos y cerraría la aplicación de manera ordenada.
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
            update();   //Se actualiza tod a la parte matemàtica y fìsica
            render();   //Se actualiza todo lo que tenga qwue ver con seteos o que aparezaca en pantalla
        }
    }

    destroy();

    return (int)msg.wParam;
}
//run: Este método es el núcleo de la aplicación, iniciando el bucle principal de mensajes de Windows.
// 
//UNREFERENCED_PARAMETER(hPrevInstance); y UNREFERENCED_PARAMETER(lpCmdLine); : Macros para evitar advertencias del compilador sobre parámetros no utilizados.
// 
//if (FAILED(m_window.Init(hInstance, nCmdShow, nullptr))) return 0; : Inicializa la ventana, y si falla, retorna 0.
// 
//if (FAILED(init())) { destroy(); return 0; } : Inicializa los recursos de la aplicación y si falla, destruye los recursos y retorna 0.
// 
//while (WM_QUIT != msg.message) : Bucle principal que procesa mensajes de Windows.
// 
//PeekMessage y DispatchMessage : Procesa los mensajes de la cola de mensajes.
// 
//update() y render() : Llama a los métodos para actualizar el estado de la aplicación y renderizar gráficos cuando no hay mensajes.
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
//WM_DESTROY : Envía un mensaje de salida cuando la ventana se cierra.
//default: Llama al procedimiento de ventana por defecto para manejar los mensajes no procesados.