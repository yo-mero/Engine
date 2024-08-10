#pragma once
//#pragma once es una directiva de preprocesador que asegura que el archivo de encabezado se 
//incluya solo una vez en la compilación, evitando problemas de redefinición y conflictos.
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
#include "UserInterface.h"
#include "Actor.h"
class BaseApp
{
public:
    BaseApp() = default;
    ~BaseApp() = default;

    HRESULT init();

    void update();

    void render();

    void destroy();
   /* HRESULT init(); : Un método para inicializar la aplicación.HRESULT es un tipo de datos utilizado en Windows 
   para representar códigos de error y estado.
        void update(); : Un método para actualizar el estado de la aplicación.
        void render(); : Un método para renderizar la ventana o gráficos.
        void destroy(); : Un método para limpiar y destruir la aplicación.
        int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow); : 
        Un método que inicia el bucle principal de la aplicación, recibiendo parámetros estándar de una aplicación de Windows.*/

    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC wndproc);

    void
        CreateGrid(int width, int depth, float spacing);
private:
    window                                  m_window;
    Device								      	          m_device;
    DeviceContext							              m_deviceContext;
    SwapChain							      	          m_swapchain;
    Texture									                m_BackBuffer;
    Texture								                	m_DepthStencil;
    DepthStencilView					  	          m_depthStencilView;
    RenderTargetView					  	          m_RenderTargetView;
    Viewport								                m_viewport;
    ShaderProgram							              m_shaderProgram;
    std::vector<Buffer>						          m_vertexBuffers;
    std::vector<Buffer>						          m_indexBuffers;
    Buffer									                m_CBBufferNeverChanges;
    Buffer								      	          m_CBBufferChangeOnResize;
    Buffer								      	          m_CBBufferChangesEveryFrame;
    std::vector<Texture>					          modelTextures;
    SamplerState						    	          m_sampler;
    ModelLoader							    	          m_model;
    Texture								      	          m_default;
    std::vector<Texture>					          gridTexs;
    UserInterface                           m_UserInterface;
    //XMMATRIX                              m_World;
    XMMATRIX                                m_View;
    XMMATRIX                                m_Projection;
    XMFLOAT4                                m_vMeshColor;
    CBNeverChanges                          cbNeverChanges;
    CBChangeOnResize                        cbChangesOnResize;
    CBChangesEveryFrame                     cb;
    //Grid Data
    MeshComponent                          MC;

    EngineUtilities::TSharedPointer<Actor>  AGrid;
   
    //Vela Actor
    EngineUtilities::TSharedPointer<Actor>  AVela;
 
    /*window m_window; : Una instancia de la clase window, que representa la ventana principal de la aplicación.*/
};
