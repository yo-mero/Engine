#include "RenderTargetView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "DephStencilView.h"
#include "Texture.h"

void RenderTargetView::init(Device device, Texture backBuffer, DXGI_FORMAT Format)
{
    if (device.m_device == nullptr)
    {
        ERROR("RenderTargetView", "init", "Check for Device device")
            exit(1);
    }
    /*Verifica si device.m_device y backBuffer.m_texture no son nullptr.Si alguno es nullptr,
        muestra un mensaje de error y sale del programa.*/
    else if (backBuffer.m_texture == nullptr)
    {
        ERROR("RenderTargetView", "init", "Checkfor Texture backBuffer")
            exit(1);
    }
    HRESULT hr = S_OK;

    D3D11_RENDER_TARGET_VIEW_DESC desc = {};
    desc.Format = Format;
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    hr = device.CreateRenderTargetView(backBuffer.m_texture, &desc, &m_renderTargetView);

    if (FAILED(hr))
    {
        ERROR("RenderTargetView", "init", "Checkfor CreateRenderTargetView")
            exit(1);
    }
}

void RenderTargetView::update()
{
}

void RenderTargetView::render(DeviceContext& deviceContext, DepthStencilView& depthStencilView, unsigned int numViews, float ClearColor[4])
{
    deviceContext.m_deviceContext->ClearRenderTargetView(m_renderTargetView, ClearColor);
    deviceContext.m_deviceContext->OMSetRenderTargets(numViews,
        &m_renderTargetView, depthStencilView.m_DepthStencilView);

}
//Limpieza de la Vista de Destino de Renderizado :
//Limpia la vista de destino de renderizado usando el color de limpieza proporcionado.
//Establecimiento de los Objetivos de Renderizado :
//Configura los objetivos de renderizado(OMSetRenderTargets) con la vista de destino de renderizado y la vista de profundidad / esténcil.

void RenderTargetView::destroy()
{
    SAFE_RELEASE(m_renderTargetView);
}/*Utiliza la macro SAFE_RELEASE para liberar de manera segura la vista de destino de renderizado(m_renderTargetView), 
asegurando que no se produzcan fugas de memoria.*/