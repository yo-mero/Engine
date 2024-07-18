#include "InputLayout.h"
#include "Device.h"
#include "DeviceContext.h"

void InputLayout::init(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, ID3DBlob* VertexshaderData)
{
	// Verifica si el layout está vacío
	if (Layout.size() == 0)
	{
		ERROR("InputLayout", "init", "CHECK FOR std::vector<D3D11_INPUT_ELEMENT_DESC> Layout")
			exit(1);
	}
	// Verifica si los datos del shader de vértices son nulos
	else if (VertexshaderData == nullptr)
	{
		ERROR("InputLayout", "init", "CHECK FOR  ID3DBlob* VertexsahderData")
			exit(1);
	}

	HRESULT hr = S_OK;

	// Crea el input layout usando el dispositivo, la descripción del layout y los datos del shader de vértices
	hr = device.CreateInputLayout(Layout.data(), Layout.size(),
		VertexshaderData->GetBufferPointer(),
		VertexshaderData->GetBufferSize(), &m_inputLayout);

	// Verifica si la creación del input layout falló
	if (FAILED(hr))
	{
		ERROR("InputLayout", "init", "CHECK FOR CreateInputLayout() ")
			exit(1);
	}

}

// Método para actualizar el Input Layout (actualmente vacío)
void InputLayout::update()
{
}

// Renderiza el Input Layout estableciendo el layout en el contexto del dispositivo
void InputLayout::render(DeviceContext& deviceContext)
{
	deviceContext.IASetInputLayout(m_inputLayout);
}

// Destruye el Input Layout y libera los recursos
void InputLayout::destroy()
{
	SAFE_RELEASE(m_inputLayout);
}