#include "dephstencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "DephStencilView.h"


void DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format) //doble puntero apunta al puntero del recurso.
{
	if (device.m_device == nullptr)
	{
		ERROR("DepthStencilView", "init", "CHECK FOR Device device")
			exit(1);
	}
	/*Verifica si device.m_device es nullptr.Si es así, imprime un mensaje de error y sale del programa.
		Verifica si depthStencil.m_texture es nullptr.Si es así, imprime un mensaje de error y sale del programa.*/

	
		/*Se llena la estructura D3D11_DEPTH_STENCIL_VIEW_DESC con valores por defecto y se especifica el formato y la dimensión de la vista de profundidad y estencil.*/
	/*Llama a CreateDepthStencilView en el dispositivo para crear la vista de profundidad y estencil.Si falla, imprime un mensaje de error y sale del programa.*/
	else if (depthStencil.m_texture == nullptr)
	{
		ERROR("DepthStencilView", "init", "CHECK FOR ID3D11Resources* depthStencil")
			exit(1);
	}
	HRESULT hr = S_OK;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	memset(&descDSV, 0, sizeof(descDSV));
	descDSV.Format = format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	device.CreateDepthStencilView(depthStencil.m_texture, &descDSV, &m_DepthStencilView);

	if (FAILED(hr))
	{
		ERROR("DepthStencilView", "init", "CHECK FOR CreateDepthStencilView")
			exit(1);
	}

}

void DepthStencilView::render(DeviceContext& deviceContext)
{
	deviceContext.m_deviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
//Limpia la vista de profundidad y estencil utilizando el método ClearDepthStencilView del DeviceContext.
//Establece la profundidad a 1.0f y el estencil a 0.
void DepthStencilView::destroy()
{
	SAFE_RELEASE(m_DepthStencilView);
}
/*Libera la vista de profundidad y estencil usando una macro SAFE_RELEASE que maneja la liberación segura del recurso Direct3D.*/
