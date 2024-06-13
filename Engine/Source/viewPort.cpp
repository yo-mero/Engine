#include "Viewport.h"
#include "Window.h"
#include "DeviceContext.h"

void Viewport::init(window window)
{
    if (window.m_hWnd == nullptr)
    {
        ERROR("Viewport", "init", "CHECK FOR Window window")
            exit(1);
    }
    m_viewport.Width = (float)window.m_width;
    m_viewport.Height = (float)window.m_height;
    m_viewport.MinDepth = 0.0f;
    m_viewport.MaxDepth = 1.0f;
    m_viewport.TopLeftX = 0;
    m_viewport.TopLeftY = 0;

}
//Verifica si window.m_hWnd no es nullptr.Si lo es, muestra un mensaje de error y sale del programa.
//Configura el viewport(m_viewport) utilizando las dimensiones de la ventana proporcionadas(window.m_width y window.m_height).
//Establece MinDepth y MaxDepth a valores estándar y TopLeftX, TopLeftY a 0.
void Viewport::update()
{
}

void Viewport::render(DeviceContext& deviceContext)
{
    deviceContext.RSSetViewports(1, &m_viewport);
}
//Utiliza deviceContext.RSSetViewports para establecer el
//viewport en el contexto del dispositivo.m_viewport contiene la configuración del viewport que se aplicará.
void Viewport::destroy()
{
}