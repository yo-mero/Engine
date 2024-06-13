#include"window.h"



HRESULT window::Init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc)
{
    m_hInst = hInstance;
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = wndproc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    RECT rc = { 0, 0, 1500, 840 };
    m_rect = rc;
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    m_hWnd = CreateWindow("TutorialWindowClass", m_windowName.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!m_hWnd)
        return E_FAIL;

    ShowWindow(m_hWnd, nCmdShow);

    GetClientRect(m_hWnd, &m_rect);
    m_width = m_rect.right - m_rect.left;
    m_height = m_rect.bottom - m_rect.top;

    return S_OK;
}
//Define una estructura WNDCLASSEX(wcex) que describe las caracter�sticas de la clase de ventana que se va a registrar.
//Carga un �cono y un cursor para la ventana.
//Configura el nombre de clase como "TutorialWindowClass".
//Registra la clase usando RegisterClassEx.

//Crea la ventana usando los par�metros definidos en wcex.
//Ajusta el tama�o de la ventana usando AdjustWindowRect.
//Establece el nombre de la ventana(m_windowName) y muestra la ventana usando ShowWindow.

//Obtiene las dimensiones del cliente de la ventana y calcula el ancho y alto de la ventana(m_width y m_height).
void window::update()
{
}

void window::render()
{
}

void window::destroy()
{
}
