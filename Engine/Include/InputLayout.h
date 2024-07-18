#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;

class InputLayout
{
public:
	InputLayout() = default;
	~InputLayout() = default;

	// Inicializa el Input Layout con la descripci�n del layout y los datos del shader de v�rtices
	void init(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, ID3DBlob* VertexshaderData);

	// M�todo para actualizar el Input Layout (actualmente vac�o)
	void update();

	// Renderiza el Input Layout estableciendo el layout en el contexto del dispositivo
	void render(DeviceContext& deviceContext);

	// Destruye el Input Layout y libera los recursos
	void destroy();


public:
	// Puntero al Input Layout de DirectX
	ID3D11InputLayout* m_inputLayout = nullptr;
};

