#include "Texture.h"
#include "Device.h"
#include"DeviceContext.h"

HRESULT Texture::init(Device device, std::string TextureName)
{
	HRESULT hr = S_OK;
	if (device.m_device == nullptr)
	{
		ERROR("Texture", "init", "CHECK FOR Device device on texture loading method")
			exit(1);
	}
	hr = D3DX11CreateShaderResourceViewFromFile(device.m_device,
		TextureName.c_str(),
		nullptr, nullptr,
		&m_textureFromImg, nullptr);
	if (FAILED(hr))
	{
		ERROR("Texture", "init", "Error data from params [CHECH FOR string textureName -> Verify correct texture mane in filepath]")
			exit(1);

	}
	return hr;
}
//Verifica si device.m_device no es nullptr.Si es nullptr, muestra un mensaje de error y sale del programa.
//Utiliza D3DX11CreateShaderResourceViewFromFile para cargar la textura desde un archivo.Si falla, muestra un 
//mensaje de error y sale del programa.
void Texture::init(Device device, unsigned int width, unsigned int height, DXGI_FORMAT Format, unsigned int Bindflags)
{
	if (device.m_device == nullptr)
	{
		ERROR("Texture", "init", "CHECK FOR Device device on texture loading method")
			exit(1);
	}
	else if (width <= 0 || height <= 0)
	{
		ERROR("Texture", "init", "CHECK FOR unsigned int width OR unsigned int height")
			exit(1);
	}
	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = Format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = Bindflags;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	hr = device.CreateTexture2D(&desc, nullptr, &m_texture);
	if (m_texture == nullptr)
	{
		ERROR("Texture", "init", "Error in data from params [CHECK FOR m_texture]")
			exit(1);
	}
	else if (FAILED(hr))
	{
		ERROR("Texture", "init", "Error in data from resources [CHECK FOR CreateTexture2D]")
			exit(1);
	}
}
//Verifica si device.m_device no es nullptr y si width y height son mayores que 0. Si alguna condición falla, 
//muestra un mensaje de error y sale del programa.
//Configura un descriptor de textura(D3D11_TEXTURE2D_DESC) y llama a CreateTexture2D para crear la textura.Si falla,
//muestra un mensaje de error y sale del programa.

void Texture::update()
{
}

void Texture::render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews)
{
	if (m_textureFromImg != nullptr)
	{
		ID3D11ShaderResourceView* nullSRV[] = { nullptr };
		deviceContext.PSSetShaderResources(StartSlot, NumViews, nullSRV);
		deviceContext.PSSetShaderResources(StartSlot, NumViews, &m_textureFromImg);
	}
}
//Establece la textura como recurso de sombreado en el dispositivo de contexto(deviceContext)
//.Si m_textureFromImg no es nullptr, establece la textura desde la imagen.
void Texture::destroy()
{
	if (m_texture != nullptr)
	{
		SAFE_RELEASE(m_texture);
	}
	else if (m_textureFromImg != nullptr)
	{
		SAFE_RELEASE(m_textureFromImg);
	}
}
//Utiliza la macro SAFE_RELEASE para liberar de manera segura m_texture o m_textureFromImg,
//asegurando que no se produzcan fugas de memoria.



