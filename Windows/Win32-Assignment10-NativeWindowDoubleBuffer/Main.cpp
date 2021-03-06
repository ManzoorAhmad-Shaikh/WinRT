#include<windows.h>
#include<gl/GL.h>
#include<stdio.h>

#pragma comment(lib,"opengl32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//callback declaration
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//global variables

HDC ghdc = NULL;
HGLRC ghrc = NULL;
bool gbActiveWindow = false;
bool bFullScreen = false;
DWORD dwStyle;
HWND ghwnd = NULL;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
MONITORINFO mi;
FILE *gpFile = NULL;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	//Function Declaration
	int initialize(void);
	void display(void);
	//variable declaration
	bool bDone = false;
	int iRet = 0;
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("My OpenGL APP");
	//code
	if(fopen_s(&gpFile,"Log.txt","w")!=0)
	{
		MessageBox(NULL,TEXT("Log file cannot be created\n"),TEXT("Error !!!"),MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile,"Log file successfully created\n");
	}
	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
	RegisterClassEx(&wndclass);
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						  szAppName,
						  TEXT("OpenGL Native Window Double Buffer"),
						  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
						  100,
						  100,
						  WIN_WIDTH,
						  WIN_HEIGHT,
						  NULL,
						  NULL,
						  hInstance,
						  NULL);
	ghwnd = hwnd;
	iRet = initialize();
	if(iRet == -1)
	{
		fprintf(gpFile,"Choose Pixel Format failed\n");
		DestroyWindow(hwnd);
	}
	else if(iRet == -2)
	{
		fprintf(gpFile,"Set Pixel Format failed\n");
		DestroyWindow(hwnd);
	}
	else if(iRet == -3)
	{
		fprintf(gpFile,"wglCreateContext failed\n");
		DestroyWindow(hwnd);
	}
	else if(iRet == -4)
	{
		fprintf(gpFile,"wglMakeCurrent failed\n");
		DestroyWindow(hwnd);
	}
	else
	{
		fprintf(gpFile,"Initialization Successful\n");
	}
	ShowWindow(hwnd,iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	//Game Loop
	while(bDone == false)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(gbActiveWindow == true)
			{
				//Here call update
			}
			//Here call Display
			display();
		}
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	//Function Declaration
	void ToggleFullScreen(void);
	void resize(int,int);
	void uninitialize(void);
	//code
	switch(iMsg)
	{
		case WM_SETFOCUS:
			gbActiveWindow = true;
			break;
		case WM_KILLFOCUS:
			gbActiveWindow = false;
			break;
		case WM_SIZE:
			resize(LOWORD(lParam),HIWORD(lParam));
			break;
		case WM_ERASEBKGND:
			return(0);
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_KEYDOWN:
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
			uninitialize();
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

int initialize(void)
{
	void resize(int,int);
	//variable declaration
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;
	//code
	//initialize pfd structure
	//step 1
	ZeroMemory(&pfd,sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	//step 2
	ghdc = GetDC(ghwnd);
	iPixelFormatIndex = ChoosePixelFormat(ghdc,&pfd);
	if(iPixelFormatIndex == 0)
	{
		return -1;
	}
	//step 3
	if(SetPixelFormat(ghdc,iPixelFormatIndex,&pfd) == FALSE)
	{
		return -2;
	}
	//Step 4 : Bridging API
	ghrc = wglCreateContext(ghdc);
	if(ghrc == NULL)
	{
		return -3;
	}
	//step 5
	if(wglMakeCurrent(ghdc,ghrc) == FALSE)
	{
		return -4;
	}
	//step 6
	glClearColor(0.0f,0.0f,1.0f,1.0f);
	//warmup call to resize
	resize(WIN_WIDTH,WIN_HEIGHT);
	return 0;
}

void resize(int width,int height)
{
	glViewport(0,0,(GLsizei)width,(GLsizei)height);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers(ghdc);
}

void uninitialize(void)
{
	if(bFullScreen == true)
	{
		//fullscreen else code. except the flag setting
		SetWindowLong(ghwnd,
					  GWL_STYLE,
					  dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd,&wpPrev);
		SetWindowPos(ghwnd,
					HWND_TOP,
					0,
					0,
					0,
					0,
					SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);

		ShowCursor(TRUE);
	}
	if(wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if(ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}
	if(ghdc)
	{
		ReleaseDC(ghwnd,ghdc);
		ghdc = NULL;
	}
	if(gpFile)
	{
		fprintf(gpFile,"Successfully closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}


void ToggleFullScreen(void)
{
	//code
	
	if(bFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd,GWL_STYLE); /*step 2*/
		//step 3
		if(dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = {sizeof(MONITORINFO)};
			if(GetWindowPlacement(ghwnd,&wpPrev) &&
			GetMonitorInfo(MonitorFromWindow(ghwnd,MONITORINFOF_PRIMARY),&mi))
			{
			SetWindowLong(ghwnd,
						  GWL_STYLE,
						  dwStyle&~WS_OVERLAPPEDWINDOW);
			SetWindowPos(ghwnd,
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
		SetWindowLong(ghwnd,
					  GWL_STYLE,
					  dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd,&wpPrev);
		SetWindowPos(ghwnd,
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


