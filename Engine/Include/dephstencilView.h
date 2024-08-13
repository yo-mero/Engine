#pragma once
#include "PreRequisites.h"

// Declaración adelantada de clases para evitar dependencias cíclicas
class Device;
class DeviceContext;
class Texture;

// Clase DepthStencilView que maneja una vista de stencil de profundidad en DirectX 11
class DepthStencilView{
public:
	// Constructor y destructor por defecto
	DepthStencilView() = default;
	~DepthStencilView() = default;

	// Inicializa la vista de stencil de profundidad
	void init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

	// Actualiza la vista de stencil de profundidad 
	void update();
	// Renderiza usando la vista de stencil de profundidad 
	void render(DeviceContext& deviceContext);
	// Destruye la vista de stencil de profundidad, liberando recursos
	void destroy();


public:
	// Puntero a la vista de stencil de profundidad de DirectX 11
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
};
#pragma once
