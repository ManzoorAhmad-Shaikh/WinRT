//Headers
#include<Windows.h>

//global function
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

HWND gHwnd = NULL;
bool bFullScreen = false;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
DEVMODE devmode = {sizeof(DEVMODE)};
DEVMODE devmodeOne = {sizeof(DEVMODE)};
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
		case WM_KEYDOWN :
			switch(wParam)
			{
			case VK_ESCAPE:
				DestroyWindow(hwnd);
				break;
			case 0x46:
				ToggleFullScreen();
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
	static MONITORINFOEX mi;
	static DWORD dw;
	LONG ret;
	bool result =true;
	DWORD dwCurrentSetting = 0;
	memset(&mi,0,sizeof(MONITORINFOEX));
	mi.cbSize=sizeof(MONITORINFOEX);
	
	
	devmode.dmSize = sizeof(DEVMODE);
		devmodeOne.dmSize = sizeof(DEVMODE);
		devmode.dmDriverExtra = 0;
		devmodeOne.dmDriverExtra = 0;
		EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&devmode);
		EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&devmodeOne);
		//devmodeOne.dmPelsWidth = devmode.dmPelsWidth;
			//devmodeOne.dmPelsHeight = devmode.dmPelsHeight;
			
	if(bFullScreen == false)
	{
		dwStyle = GetWindowLong(gHwnd,GWL_STYLE); /*step 2*/
		//devmode.dmSize = sizeof(DEVMODE);
		//devmodeOne.dmSize = sizeof(DEVMODE);
		//devmode.dmDriverExtra = 0;
		//EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&devmode);
		//step 3
		if(dwStyle & WS_OVERLAPPEDWINDOW)
		{
			
			//mi = {sizeof(MONITORINFOEX)};
			if(GetWindowPlacement(gHwnd,&wpPrev) &&
			GetMonitorInfo(MonitorFromWindow(gHwnd,MONITORINFOF_PRIMARY),&mi))
			{
				SetWindowLong(gHwnd,
						  GWL_STYLE,
						  dwStyle&~(WS_OVERLAPPEDWINDOW));
				devmode.dmPelsWidth = static_cast<DWORD>(800);
				devmode.dmPelsHeight = static_cast<DWORD>(600);
				devmode.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
				ChangeDisplaySettings(&devmode,CDS_FULLSCREEN);
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
		/*SetWindowPlacement(gHwnd,&wpPrev);
		SetWindowPos(gHwnd,
					HWND_TOP,
					0,
					0,
					0,
					0,
					SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
*/
		devmode.dmPelsWidth = static_cast<DWORD>(1366);
				devmode.dmPelsHeight = static_cast<DWORD>(768);
				devmode.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
				ChangeDisplaySettings(&devmode,CDS_FULLSCREEN);
		ShowCursor(TRUE);
		bFullScreen = false;
	}
}

