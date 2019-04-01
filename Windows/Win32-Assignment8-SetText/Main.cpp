//Headers
#include<Windows.h>

//global function
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

HWND gHwnd = NULL;
bool bFullScreen = false;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};

//WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR
lpszCmdLine,int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App");
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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	//register above class
	RegisterClassEx(&wndclass);
	//create window
	hwnd = CreateWindow(szAppName,
						TEXT("My Application"),
						WS_OVERLAPPEDWINDOW,
						100,
						100,
						800,
						600,
						NULL,
						NULL,
						hInstance,
						NULL);
	gHwnd = hwnd;
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
	void ToggleFullScreen(void);
	//code
	switch(iMsg)
	{
		case WM_CHAR :
			switch(wParam)
			{
			case VK_ESCAPE:
				DestroyWindow(hwnd);
				break;
			case 'f':
			case 'F':
				if(bFullScreen==false)
					ToggleFullScreen();
				else
				{
					ToggleFullScreen();
					SetWindowText(hwnd,TEXT("Manzoor : Not a Full screen"));
				}
				break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

void ToggleFullScreen(void)
{
	//code
	MONITORINFO mi;
	if(bFullScreen == false)
	{
		dwStyle = GetWindowLong(gHwnd,GWL_STYLE); /*step 2*/
		//step 3
		if(dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = {sizeof(MONITORINFO)};
			if(GetWindowPlacement(gHwnd,&wpPrev) &&
			GetMonitorInfo(MonitorFromWindow(gHwnd,MONITORINFOF_PRIMARY),&mi))
			{
			SetWindowLong(gHwnd,
						  GWL_STYLE,
						  dwStyle&~WS_OVERLAPPEDWINDOW);
			SetWindowPos(gHwnd,
						HWND_TOP,
						mi.rcMonitor.left,
						mi.rcMonitor.top,
						mi.rcMonitor.right - mi.rcMonitor.left,
						mi.rcMonitor.bottom - mi.rcMonitor.top,
						SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
		bFullScreen = true;
	}
	else
	{
		SetWindowLong(gHwnd,
					  GWL_STYLE,
					  dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(gHwnd,&wpPrev);
		SetWindowPos(gHwnd,
					HWND_TOP,
					0,
					0,
					0,
					0,
					SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);

		ShowCursor(TRUE);
		bFullScreen = false;
	}
}

