#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;

class InputLayout
{
public:
	InputLayout() = default;
	~InputLayout() = default;

	// Inicializa el Input Layout con la descripción del layout y los datos del shader de vértices
	void init(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, ID3DBlob* VertexshaderData);

	// Método para actualizar el Input Layout (actualmente vacío)
	void update();

	// Renderiza el Input Layout estableciendo el layout en el contexto del dispositivo
	void render(DeviceContext& deviceContext);

	// Destruye el Input Layout y libera los recursos
	void destroy();


public:
	// Puntero al Input Layout de DirectX
	ID3D11InputLayout* m_inputLayout = nullptr;
};

