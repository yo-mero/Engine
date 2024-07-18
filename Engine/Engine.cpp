//--------------------------------------------------------------------------------------
// File: guup_enigne.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "PreRequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "swap chain.h"
#include "Texture.h"
#include "dephstencilView.h"
#include "RenderTargetView.h"
#include "ViewPort.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "SampleState.h"
#include "ModelLoader.h"
#include "fbxsdk.h"
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------

window                                  g_window;
Device									g_device;
DeviceContext							g_deviceContext;
SwapChain								g_swapchain;
Texture									g_BackBuffer;
Texture									g_DepthStencil;
DepthStencilView						g_depthStencilView;
RenderTargetView						g_RenderTargetView;
Viewport								g_viewport;
ShaderProgram							g_shaderProgram;
std::vector<Buffer>						g_vertexBuffers;
std::vector<Buffer>						g_indexBuffers;
Buffer									g_CBBufferNeverChanges;
Buffer									g_CBBufferChangeOnResize;
Buffer									g_CBBufferChangesEveryFrame;
Mesh									g_mesh;
std::vector<Texture>					modelTextures;
SamplerState							g_sampler;
ModelLoader								g_model;
Texture									g_default;
std::vector<Texture>gridTexs;


XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);
CBNeverChanges                      cbNeverChanges;
CBChangeOnResize                    cbChangesOnResize;
CBChangesEveryFrame                 cb;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------

HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();

void Update(float DeltaTime);

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(g_window.Init(hInstance, nCmdShow, WndProc)))
		return 0;

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Update our time
			static float t = 0.0f;
			if (g_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
			{
				t += (float)XM_PI * 0.0125f;
			}
			else
			{
				static DWORD dwTimeStart = 0;
				DWORD dwTimeCur = GetTickCount();
				if (dwTimeStart == 0)
					dwTimeStart = dwTimeCur;
				t = (dwTimeCur - dwTimeStart) / 1000.0f;
			}

			Update(t);
			Render();
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	HRESULT hr = S_OK;
	//create Swapchain
	g_swapchain.init(g_device, g_deviceContext, g_BackBuffer, g_window);

	//create render target view
	g_RenderTargetView.init(g_device, g_BackBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);


	// Create depth stencil texture
	g_DepthStencil.init(g_device, g_window.m_width
		, g_window.m_height,
		DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);


	// Create the depth stencil view
	g_depthStencilView.init(g_device, g_DepthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);

	g_viewport.init(g_window);

	// Compile the vertex shader
	//ID3DBlob* pVSBlob = NULL;
	//hr = CompileShaderFromFile("guup_enigne.fx", "VS", "vs_4_0", &pVSBlob);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL,
	//		"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
	//	return hr;
	//}

	// Create the vertex shader
	//hr = g_device.m_device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
	/*hr = g_device.CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}*/

	//define the inputLayout

	std::vector<D3D11_INPUT_ELEMENT_DESC>Layout;

	D3D11_INPUT_ELEMENT_DESC position;
	position.SemanticName = "POSITION";
	position.SemanticIndex = 0;
	position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	position.InputSlot = 0;
	position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	position.InstanceDataStepRate = 0;
	Layout.push_back(position);

	D3D11_INPUT_ELEMENT_DESC texcoord;;
	texcoord.SemanticName = "TEXCOORD";
	texcoord.SemanticIndex = 0;
	texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
	texcoord.InputSlot = 0;
	texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT /*12*/;
	texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	texcoord.InstanceDataStepRate = 0;
	Layout.push_back(texcoord);

	g_shaderProgram.init(g_device, "Engine.fx", Layout);

	//load model
	g_model.LoadModel("Models/Vela2.fbx");
	/* {
		g_mesh.vertex.push_back(vertex);
	}*/

	//// NOTA: El static_cast<unsigned int�
	//se est� utilizando aqu� para convertir el resultado del m�todo size() 
	//    de un std::vector a un tipo unsigned int.
	//    El m�todo size() devuelve un valor del tipo std::size_t, 
	//    que es un tipo espec�fico de tama�o no negativo.En algunas 
	//    plataformas, std : size_t puede ser de un tama�o diferente a unsigned int. /

	//// Create vertex buffer
	for (auto& mesh : g_model.meshes)
	{
		Buffer vertexBuffer;
		vertexBuffer.init(g_device, mesh, D3D11_BIND_VERTEX_BUFFER);
		g_vertexBuffers.push_back(vertexBuffer);
		/*g_mesh.name = "HollowKnight";
		g_mesh.vertex = g_model.GetVertices();*/
		/*for (const SimpleVertex& vertex : vertices)
	{
		g_mesh.vertex.push_back(vertex);
	}*/

	//// NOTA: El static_cast<unsigned int�
	//se est� utilizando aqu� para convertir el resultado del m�todo size() 
	//    de un std::vector a un tipo unsigned int.
	//    El m�todo size() devuelve un valor del tipo std::size_t, 
	//    que es un tipo espec�fico de tama�o no negativo.En algunas 
	//    plataformas, std : size_t puede ser de un tama�o diferente a unsigned int. /

   //g_mesh.numVertex  = static_cast<unsigned int>(g_mesh.vertex.size());
   // // Create vertex buffer
   // g_vertexBuffer.init(g_device, g_mesh, D3D11_BIND_VERTEX_BUFFER);

   // // Create index buffer
		Buffer indexBuffer;
		indexBuffer.init(g_device, mesh, D3D11_BIND_INDEX_BUFFER);
		g_indexBuffers.push_back(indexBuffer);
	}
	// g_mesh.index = g_model.GetIndices();
	// g_mesh.numIndex = static_cast<unsigned int>(g_mesh.index.size());
	// // g_indexBuffer.init(g_device, g_mesh, D3D11_BIND_INDEX_BUFFER);


	// Inicializaci�n de Constant Buffers
	g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

	g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

	g_CBBufferChangesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));

	//Create SamplerState
	g_sampler.init(g_device);

	// Initialize the world matrices
	g_World = XMMatrixIdentity();

	// Load the Texture
	Texture Vela_Char_BaseColor;
	Vela_Char_BaseColor.init(g_device, "Textures/Vela/Vela_Char_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Corneas_BaseColor;
	Vela_Corneas_BaseColor.init(g_device, "Textures/Vela/Vela_Corneas_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Gun_BaseColor;
	Vela_Gun_BaseColor.init(g_device, "Textures/Vela/Vela_Gun_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Legs_BaseColor;
	Vela_Legs_BaseColor.init(g_device, "Textures/Vela/Vela_Legs_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Mechanical_BaseColor;
	Vela_Mechanical_BaseColor.init(g_device, "Textures/Vela/Vela_Mechanical_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Plate_BaseColor;
	Vela_Plate_BaseColor.init(g_device, "Textures/Vela/Vela_Plate_BaseColor.png", ExtensionType::PNG);

	Texture Vela_Visor_BaseColor;
	Vela_Visor_BaseColor.init(g_device, "Textures/Vela/Vela_Visor_BaseColor.png", ExtensionType::PNG);

	modelTextures.push_back(Vela_Corneas_BaseColor);		//1
	modelTextures.push_back(Vela_Gun_BaseColor);			//2
	modelTextures.push_back(Vela_Visor_BaseColor);			//3
	modelTextures.push_back(Vela_Legs_BaseColor);			//4
	modelTextures.push_back(Vela_Mechanical_BaseColor);		//5
	modelTextures.push_back(Vela_Char_BaseColor);			//6
	modelTextures.push_back(Vela_Plate_BaseColor);			//7
	g_default.init(g_device, "Textures/Default.png", ExtensionType::PNG);

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	g_View = XMMatrixLookAtLH(Eye, At, Up);

	cbNeverChanges.mView = XMMatrixTranspose(g_View);


	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f);

	//CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	/*g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);*/

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if (g_deviceContext.m_deviceContext) g_deviceContext.m_deviceContext->ClearState();


	g_sampler.destroy();
	for (auto& tex : modelTextures)
	{
		tex.destroy();
	}
	g_default.destroy();
	g_CBBufferNeverChanges.destroy();
	g_CBBufferChangeOnResize.destroy();
	g_CBBufferChangesEveryFrame.destroy();

	for (auto& vertexBuffer : g_vertexBuffers)
	{
		vertexBuffer.destroy();
	}
	for (auto& indexBuffer : g_indexBuffers)
	{
		indexBuffer.destroy();
	}
	g_shaderProgram.destroy();
	g_DepthStencil.destroy();
	g_depthStencilView.destroy();
	g_RenderTargetView.destroy();
	g_swapchain.destroy();
	g_deviceContext.destroy();
	g_device.destroy();

}
//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//Update everyframe
void Update(float DeltaTime)
{
	// Rotate cube around the origin
	XMVECTOR translation = XMVectorSet(0.0f, -2.0f, 0.0f, 0.0f); // Traslaci�n en x=1, y=2, z=3
	XMVECTOR rotation = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(260), XMConvertToRadians(DeltaTime * 50), 0.0f); // Rotaci�n en X=180, Y=180, Z=0
	XMVECTOR scale = XMVectorSet(.03f, .03f, .03f, 0.0f); // Escala por 2 en x, y, z

	// Combinar las transformaciones en una matriz de mundo
	g_World = XMMatrixScalingFromVector(scale) * XMMatrixRotationQuaternion(rotation) * XMMatrixTranslationFromVector(translation);
	//update constant buffer
	g_CBBufferNeverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
	g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);
	cb.mWorld = XMMatrixTranspose(g_World);
	cb.vMeshColor = g_vMeshColor;
	g_CBBufferChangesEveryFrame.update(g_deviceContext, 0, nullptr, &cb, 0, 0);
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
	// Clear the back buffer

	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	g_RenderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);

	g_viewport.render(g_deviceContext);
	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	//g_deviceContext.m_deviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	g_depthStencilView.render(g_deviceContext);

	//render cube
	g_shaderProgram.render(g_deviceContext);
	// Render the model
	for (size_t i = 0; i < g_model.meshes.size(); i++)
	{
		g_vertexBuffers[i].render(g_deviceContext, 0, 1);
		g_indexBuffers[i].render(g_deviceContext, DXGI_FORMAT_R32_UINT);
		if (i <= modelTextures.size() - 1)
		{
			modelTextures[i].render(g_deviceContext, 0, 1);
		}
		else
		{
			g_default.render(g_deviceContext, 0, 1);
		}
		//g_default.render(g_deviceContext, 0, 1);

		g_sampler.render(g_deviceContext, 0, 1);

		g_CBBufferNeverChanges.render(g_deviceContext, 0, 1); // Slot 0
		g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1); // Slot 1
		g_CBBufferChangesEveryFrame.renderModel(g_deviceContext, 2, 1); // Slot 2
		//Set primitve topology
		g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		g_deviceContext.m_deviceContext->DrawIndexed(g_model.meshes[i].numIndex, 0, 0);
	}

	//
	// Present our back buffer to our front buffer
	//
	//g_pSwapChain->Present(0, 0);
	g_swapchain.present();
}
