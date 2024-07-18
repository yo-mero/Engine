#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;

class SamplerState
{
public:
	SamplerState() = default;
	~SamplerState() = default;


	// Inicializa el estado de muestreo
	void init(Device device);

	// Actualmente no implementado
	void update();
	// Establece el estado de muestreo en el contexto del dispositivo
	void render(DeviceContext& deviceContext, unsigned int StartSlot,
		unsigned int NumSamplers);
	// Libera los recursos asociados con el estado de muestreo
	void destroy();

private:
	// Puntero al estado de muestreo de DirectX 11
	ID3D11SamplerState* m_sampler = nullptr;

};