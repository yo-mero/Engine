#include "DeviceContext.h"

void DeviceContext::destroy()
{
	SAFE_RELEASE(m_deviceContext);
}
//Utiliza la macro SAFE_RELEASE para liberar de manera segura el recurso m_deviceContext,
//asegurando que no se produzcan fugas de memoria.

void DeviceContext::PSSetShaderResources(unsigned int StartSlot, unsigned int NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	if (ppShaderResourceViews == nullptr)
	{
		ERROR("DeviceContext", "PSSetShaderResources", " CHECK FOR  ID3D11ShaderResourceView* const* ppShaderResourceViews")
			exit(1);
	}
	else
	{
		m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}
//Verifica si ppShaderResourceViews no es nullptr.Si es nullptr, muestra un mensaje de error y sale del programa.
//Si ppShaderResourceViews es válido, llama a PSSetShaderResources del dispositivo.
void DeviceContext::RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports)
{

	if (pViewports == nullptr)
	{
		ERROR("DeviceContext", "RSSetViewports", "CHECK for const D3D11_VIEWPORT* pViewports")
			exit(1);
	}
	else
	{
		m_deviceContext->RSSetViewports(NumViewports, pViewports);
	}
}/*Verifica si pViewports no es nullptr.Si es nullptr, muestra un mensaje de error y sale del programa.
Si pViewports es válido, llama a RSSetViewports del dispositivo.*/