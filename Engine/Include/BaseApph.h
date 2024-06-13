#pragma once
//#pragma once es una directiva de preprocesador que asegura que el archivo de encabezado se 
//incluya solo una vez en la compilaci�n, evitando problemas de redefinici�n y conflictos.
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
   /* HRESULT init(); : Un m�todo para inicializar la aplicaci�n.HRESULT es un tipo de datos utilizado en Windows 
   para representar c�digos de error y estado.
        void update(); : Un m�todo para actualizar el estado de la aplicaci�n.
        void render(); : Un m�todo para renderizar la ventana o gr�ficos.
        void destroy(); : Un m�todo para limpiar y destruir la aplicaci�n.
        int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow); : 
        Un m�todo que inicia el bucle principal de la aplicaci�n, recibiendo par�metros est�ndar de una aplicaci�n de Windows.*/

    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:

    window m_window;
    /*window m_window; : Una instancia de la clase window, que representa la ventana principal de la aplicaci�n.*/
};
