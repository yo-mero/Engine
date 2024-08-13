#pragma once
#include "PreRequisites.h"

class DeviceContext{
public:
	DeviceContext() = default;
	~DeviceContext() = default;

	void init();

	void update();

	void render();

	void destroy();
	// Establece recursos de shader para el sombreador de píxeles
	void PSSetShaderResources(unsigned int StartSlot, unsigned int NumViews,
		ID3D11ShaderResourceView* const* ppShaderResourceViews);
	// Establece los viewports de renderización
	void RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);
	// Establece el layout de entrada para la etapa de entrada-ensamblador de vértices
	void IASetInputLayout(ID3D11InputLayout* pInputLayout);
	// Establece el shader de vértices
	void VSSetShader(ID3D11VertexShader* pVertexShader,
		ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances);
	// Establece el shader de píxeles
	void PSSetShader(ID3D11PixelShader* pPixelShader,
		ID3D11ClassInstance* const* ppClassInstances, unsigned int NumClassInstances);

	// Actualiza un subrecurso de un recurso de origen a un recurso de destino
	void UpdateSubresource(ID3D11Resource* pDstResource,
		unsigned int DstSubresource,
		const D3D11_BOX* pDstBox, const void* pSrcData,
		unsigned int SrcRowPitch,
		unsigned int SrcDepthPitch);

	// Establece los buffers de vértices para la etapa de entrada-ensamblador de vértices
	void IASetVertexBuffers(unsigned int StartSlot, unsigned int NumBuffers,
		ID3D11Buffer* const* ppVertexBuffers,
		const unsigned int* pStrides,
		const unsigned int* pOffsets);

	// Establece el buffer de índices para la etapa de entrada-ensamblador de vértices
	void IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
		DXGI_FORMAT Format,
		unsigned int Offset);
	// Establece los samplers para el sombreador de píxeles
	void PSSetSamplers(unsigned int StartSlot, unsigned int NumSamplers,
		ID3D11SamplerState* const* ppSamplers);

public:
	// Puntero al contexto del dispositivo D3D11
	ID3D11DeviceContext* m_deviceContext = nullptr;
};

