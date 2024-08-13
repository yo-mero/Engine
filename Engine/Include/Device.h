#pragma once
#include "PreRequisites.h"

class Device{
public:
    Device() = default;
    ~Device() = default;

	// Inicializa el dispositivo
    void init();
	// Actualiza el dispositivo (actualmente vacío)
    void update();
	// Renderiza el dispositivo (actualmente vacío)
    void render();
	// Destruye el dispositivo y libera los recursos
    void destroy();

	// Crea una vista de render target
    HRESULT CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView);

	// Crea una textura 2D
    HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D);

	// Crea una vista de profundidad y stencil
    HRESULT CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);

	// Crea un shader de vértices
    HRESULT CreateVertexShader(const void* pShaderBytecode, unsigned int BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader);
	
	// Crea un input layout
	HRESULT  CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
		unsigned int  NumElements,
		const void* pShaderBytecodeWithInputSignature,
		unsigned int  BytecodeLength,
		ID3D11InputLayout** ppInputLayout);

	// Crea un shader de píxeles
	HRESULT  CreatePixelShader(const void* pShaderBytecode,
		unsigned int BytecodeLength,
		ID3D11ClassLinkage* pClassLinkage,
		ID3D11PixelShader** ppPixelShader);

	// Crea un buffer
	HRESULT  CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
		const D3D11_SUBRESOURCE_DATA* pInitialData,
		ID3D11Buffer** ppBuffer);

	// Crea un estado de sampler
	HRESULT  CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);

    ID3D11Device* m_device = nullptr;
private:

};

