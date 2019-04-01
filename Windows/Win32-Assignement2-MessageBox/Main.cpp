//Headers
#include<Windows.h>

//global function
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");
	//code
	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	//register above class
	RegisterClassEx(&wndclass);
	//create window
	hwnd = CreateWindow(szAppName,
						TEXT("My Application"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);
	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);
	//message loop
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	//code
	switch(iMsg)
	{
		case WM_CREATE:
			MessageBox(hwnd,TEXT("This is WM_CREATE "),TEXT("My Message"),MB_OK);
			break;
		case WM_LBUTTONDOWN:
			MessageBox(hwnd,TEXT("This is WM_LBUTTONDOWN"),TEXT("My Message"),MB_OK);
			break;
		case WM_RBUTTONDOWN:
			MessageBox(hwnd,TEXT("This is WM_RBUTTONDOWN"),TEXT("My Message"),MB_OK);
			break;
		case WM_KEYDOWN:
			switch(wParam)
			{
			case VK_ESCAPE:
				MessageBox(hwnd,TEXT("This is WM_KEYDOWN : Escape"),TEXT("My Message"),MB_OK);
				DestroyWindow(hwnd);
				break;
			case 0x46:
				MessageBox(hwnd,TEXT("This is WM_KEYDOWN : F key press"),TEXT("My Message"),MB_OK);
				break;
			}
			break;
		case WM_DESTROY:
			MessageBox(hwnd,TEXT("This is WM_DESTROY"),TEXT("My Message"),MB_OK);
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
