#include "swap chain.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Window.h"
#include "Texture.h"



void SwapChain::init(Device& device, DeviceContext& deviceContext, Texture& backBuffer, window window)
{
	//check ifwindow resource exist
	if (window.m_hWnd == nullptr)
	{
		ERROR("Swapchain", "init", "CHECK FOR window window")
			exit(1);
	}
	unsigned int createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = window.m_width;
	sd.BufferDesc.Height = window.m_height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = window.m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	HRESULT hr = S_OK;

	for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_swapChain, &device.m_device, &m_featureLevel, &deviceContext.m_deviceContext);

		if (SUCCEEDED(hr))
		{
			break;
		}

		if (FAILED(hr))
		{
			ERROR("Swapchain", "init", "CHECK FOR D3D11CreateDeviceAndSwapChain()")
				exit(1);
		}

	}
	// Create a render target view
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer.m_texture);
	if (FAILED(hr))
	{
		ERROR("Swapchain", "init", "CHECK FOR m_swapChain->GetBuffer()")
			exit(1);
	}
}
//Verifica si window.m_hWnd no es nullptr.Si es nullptr, muestra un mensaje de error y sale del programa.
//Configuraci�n de DXGI_SWAP_CHAIN_DESC :
//Configura la descripci�n de la cadena de intercambio(sd) con las caracter�sticas adecuadas(ancho, alto, formato, tasa de refresco, etc.).
//Creaci�n del Dispositivo y la Cadena de Intercambio :
//Intenta crear el dispositivo y la cadena de intercambio con diferentes tipos de controlador(driverTypes).Si falla en todas las pruebas, 
// muestra un mensaje de error y sale del programa.
//Creaci�n de la Vista de Destino de Renderizado :
//Obtiene el b�fer de la cadena de intercambio y lo asigna a backBuffer.m_texture.Si falla, muestra un mensaje de error y sale del programa.

void SwapChain::update()
{
}

void SwapChain::render()
{
}

void SwapChain::destroy()
{
	SAFE_RELEASE(m_swapChain);
}
//Utiliza la macro SAFE_RELEASE para liberar de manera segura la cadena de intercambio(m_swapChain), asegurando que no se produzcan fugas de memoria.

void SwapChain::present()
{
	m_swapChain->Present(0, 0);
}
//Llama a Present en la cadena de intercambio para mostrar el contenido renderizado en la pantalla.