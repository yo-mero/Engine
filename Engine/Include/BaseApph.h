#pragma once
//#pragma once es una directiva de preprocesador que asegura que el archivo de encabezado se 
//incluya solo una vez en la compilación, evitando problemas de redefinición y conflictos.
#include "PreRequisites.h"
#include "window.h"

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

    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:

    window m_window;
    /*window m_window; : Una instancia de la clase window, que representa la ventana principal de la aplicación.*/
};
