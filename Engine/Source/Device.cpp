#include "Device.h"
// Método para inicializar el dispositivo
void Device::init()
{
}

void Device::update()
{
}

void Device::render()
{
}

void Device::destroy()
{
    SAFE_RELEASE(m_device);
}
//Libera el dispositivo usando una macro SAFE_RELEASE, que maneja la liberación segura del recurso Direct3D.
// Crea una vista de render target
HRESULT Device::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
{
    HRESULT hr = S_OK;
    //Check if the resource and RTView exist
    if (pResource != nullptr || ppRTView != nullptr)
    {
        hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);
        MESSAGE("Device", "CreateRenderTarfetView", "OK")
    }
    else
    {
        ERROR("Device", "CreateRenderTargetView", "CHECK FOR CREATION METHOD")
            exit(1);
    }
    return hr;
}
//Verifica si pResource y ppRTView no son nullptr.Si son válidos, llama a CreateRenderTargetView y muestra un mensaje de éxito.
//Si alguno de los punteros es nullptr, muestra un mensaje de error y sale del programa.
// Crea una textura 2D
HRESULT Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
{
    {
        HRESULT hr = S_OK;
        //Check if the resource and RTView exist
        if (pDesc != nullptr || ppTexture2D != nullptr)
        {
            hr = m_device->CreateTexture2D(pDesc,pInitialData,ppTexture2D);
            MESSAGE("Device", "CreateRenderTarfetView", "OK")
        }
        else
        {
            ERROR("Device", "CreateTexture2D", "CHECK FOR CREATION METHOD")
                exit(1);
        }
        return hr;
    }
}
//Verifica si pDesc y ppTexture2D no son nullptr.Si son válidos, llama a CreateTexture2D y muestra un mensaje de éxito.
//Si alguno de los punteros es nullptr, muestra un mensaje de error y sale del programa.

HRESULT Device::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
{
    HRESULT hr = S_OK;
    //Check if the resource and RTView exist
    if (pResource == nullptr)
    {
        ERROR("Device", "CreateDepthStencilView", "CHECK FOR CreateDepthStencilView METHOD")
            exit(1);
    }
    else if (ppDepthStencilView == nullptr)
    {
        ERROR("Device", "CreateDepthStencilView", "CHECK FOR ID2D11DepthStencilView** ppDepthStencilView")
            exit(1);
    }
    else
    {
        hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
        MESSAGE("Device", "CreateRenderTarfetView", "OK")
    }
    return hr;
}
//Verifica si pResource y ppDepthStencilView no son nullptr.Si son válidos, llama a CreateDepthStencilView y muestra un mensaje de éxito.
//Si alguno de los punteros es nullptr, muestra un mensaje de error específico y sale del programa.
HRESULT Device::CreateVertexShader(const void* pShaderBytecode, unsigned int BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
{
    HRESULT hr = S_OK;
    //Check if the resource and RTView exist
    if (pShaderBytecode == nullptr)
    {
        ERROR("Device", "CreateVertexShader", "CHECK FOR const void* pShaderBytecode")
            exit(1);
    }
    else if (ppVertexShader == nullptr)
    {
        ERROR("Device", "CreateVertexShader", "CHECK FOR ID2D11VertexShader** ppVertexShader")
            exit(1);
    }
    else
    {
        hr = m_device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
        MESSAGE("Device", "CreateVertexShader", "OK")
    }
    return hr;

}
HRESULT Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, unsigned int NumElements, const void* pShaderBytecodeWithInputSignature, unsigned int BytecodeLength, ID3D11InputLayout** ppInputLayout)
{
    HRESULT hr = S_OK;
    hr = m_device->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);

    if (pInputElementDescs == nullptr)
    {
        ERROR("Device", "CreateInputLayout", "CHECK FOR D3D11_INPUT_ELEMENT_DESC* pInputElementDescs")
            exit(1);
    }
    else if (pShaderBytecodeWithInputSignature == nullptr)
    {
        ERROR("Device", "CreateInputLayout", "CHECK FOR const void* pShaderBytecodeWithInputSignature")
            exit(1);
    }
    else if (ppInputLayout == nullptr)
    {
        ERROR("Device", "CreateInputLayout", "CHECK FOR ID3D11InputLayout** ppInputLayout")
            exit(1);
    }
    else
    {
        hr = m_device->CreateInputLayout(pInputElementDescs,
            NumElements,
            pShaderBytecodeWithInputSignature,
            BytecodeLength,
            ppInputLayout);
        MESSAGE("device", "CreateInputLayout", "OK")
    }
    return hr;

}

HRESULT Device::CreatePixelShader(const void* pShaderBytecode, unsigned int BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
{
    HRESULT hr = S_OK;
    if (pShaderBytecode == nullptr)
    {
        ERROR("Device", "CreatePixelShader", "CHECK FOR const void* pShaderBytecode")
            exit(1);
    }
    else if (ppPixelShader == nullptr)
    {
        ERROR("Device", "CreatePixelShader", "CHECK FOR ID3D11PixelShader** ppPixelShader")
            exit(1);
    }
    else
    {
        hr = m_device->CreatePixelShader(pShaderBytecode,
            BytecodeLength,
            pClassLinkage,
            ppPixelShader);
        MESSAGE("device", "CreatePixelShader", "OK")
    }
    return hr;
}

HRESULT Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
{
    HRESULT hr = S_OK;
    if (pDesc == nullptr)
    {
        ERROR("Device", "CreateBuffer", "CHECK FOR const D3D11_BUFFER_DESC* pDesc")
            exit(1);
    }
    else if (ppBuffer == nullptr)
    {
        ERROR("Device", "CreateBuffer", "CHECK FOR ID3D11Buffer** ppBuffer")
            exit(1);
    }
    else
    {
        hr = m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);
        MESSAGE("device", "CreateBuffer", "OK")
    }
    return hr;
}

HRESULT Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
{
    HRESULT hr = S_OK;
    if (pSamplerDesc == nullptr)
    {
        ERROR("Device", "CreateSamplerState", "CHECK FOR const D3D11_SAMPLER_DESC* pSamplerDesc")
            exit(1);
    }
    else if (ppSamplerState == nullptr)
    {
        ERROR("Device", "CreateSamplerState", "CHECK FOR ID3D11SamplerState** ppSamplerState")
            exit(1);
    }
    else
    {
        hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);
        MESSAGE("Device", "CreateSamplerState", "OK")
    }
    return hr;
}
/*Verifica si pShaderBytecode y ppVertexShader no son nullptr.Si son válidos, llama a CreateVertexShader y muestra un mensaje de éxito.
Si alguno de los punteros es nullptr, muestra un mensaje de error específico y sale del programa.*/