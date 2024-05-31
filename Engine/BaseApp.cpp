
void
BaseApp :: run(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	LPWSRD lpCmdLine, int nCmdShow)

	
UNREFERENCED_PARAMETER(hPrevInstance);
UNREFERENCED_PARAMETER(lpCmdLine);
//Inicializar la ventana 
if (FAILED(InitWindow(hInstance, nCmdShow)))
return 0;
//Inicializar los recursos de la aplicacion
if (FAILED(init()))
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
        update();
        Render();
    }
}

destroy();

return (int)msg.wParam;
}
