#include<stdio.h>
#include<windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"kernel32.lib")

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

struct Light{
	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightSpecular[4];
	GLfloat LightPosition[4];
};
//Global variable
HDC ghdc = NULL;
HGLRC ghrc = NULL;
bool gbActiveWindow = false;
bool bFullScreen = false;
DWORD dwStyle;
HWND ghwnd = NULL;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
MONITORINFO mi;

FILE *gpFile = NULL;
float angleRotate = 0.0f;
bool bLight = false;

//Light struct
struct Light light[2] = {{{0.0f,0.0f,0.0f,1.0f},{1.0f,0.0f,0.0f,1.0f},{1.0f,0.0f,0.0f,1.0f},{-2.0f,0.0f,0.0f,1.0f}},
							{{0.0f,0.0f,0.0f,1.0f},{0.0f,0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f,1.0f},{2.0f,0.0f,0.0f,1.0f}}
						};
						
GLfloat LightAmbientZero[] = {0.0f,0.0f,0.0f,1.0f};
GLfloat LightDiffuseZero[] = {1.0f,0.0f,0.0f,1.0f};
GLfloat LightSpecularZero[] = {1.0f,0.0f,0.0f,1.0f};
GLfloat LightPositionZero[] = {-2.0f,0.0f,0.0f,1.0f};

GLfloat LightAmbientOne[] = {0.0f,0.0f,0.0f,1.0f};
GLfloat LightDiffuseOne[] = {0.0f,0.0f,1.0f,1.0f};
GLfloat LightSpecularOne[] = {0.0f,0.0f,1.0f,1.0f};
GLfloat LightPositionOne[] = {2.0f,0.0f,0.0f,1.0f};

GLfloat MaterialAmbient [] = {0.0f,0.0f,0.0f,1.0f};
GLfloat MaterialDiffuse [] = {1.0f,1.0f,1.0f,1.0f};
GLfloat MaterialSpecular [] = {1.0f,1.0f,1.0f,1.0f};
GLfloat MaterialShininess[] = {128.0f};
//Callbcak declaration
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdline,int iCmdShow)
{
	int initialize(void);
	void display(void);
	void update(void);
	//variable declaration
	
	bool bDone = false;
	int iRet = 0;
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclassex;
	TCHAR szAppName[] = TEXT("Perspective PROJECTION");
	
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
	
	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclassex.cbClsExtra = 0;
	wndclassex.cbWndExtra = 0;
	wndclassex.lpfnWndProc = WndProc;
	wndclassex.hInstance = hInstance;
	wndclassex.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclassex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclassex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclassex.lpszClassName = szAppName;
	wndclassex.lpszMenuName = NULL;
	wndclassex.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	
	RegisterClassEx(&wndclassex);
	
	//create window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
							szAppName,
							TEXT("Perspective PROJECTION"),
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
				update();
			}
			//here call display
			display();
			
		}
	}
	
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	//function declaration
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
		case WM_CHAR:
			switch(wParam)
			{
				case 'L':
				case 'l':
					if(bLight == false){
						bLight = true;
						glEnable(GL_LIGHTING);
					}
					else{
						bLight = false;
						glDisable(GL_LIGHTING);
					}
					break;
			}
			break;
		case WM_ERASEBKGND:
			return(0);
		case WM_DESTROY:
			uninitialize();
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

void ToggleFullScreen(void)
{
	if(bFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd,GWL_STYLE);
		
		if(dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = {sizeof(MONITORINFO)};
			
			if(GetWindowPlacement(ghwnd,&wpPrev) &&
				GetMonitorInfo(MonitorFromWindow(ghwnd,MONITORINFOF_PRIMARY),&mi))
			{
				SetWindowLong(ghwnd,GWL_STYLE,dwStyle&~WS_OVERLAPPEDWINDOW);
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
		SetWindowLong(ghwnd,GWL_STYLE,dwStyle | WS_OVERLAPPEDWINDOW);
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

int initialize(void)
{
	void resize(int,int);
	
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;
	
	//code
	ZeroMemory(&pfd,sizeof(PIXELFORMATDESCRIPTOR));
	
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	
	ghdc = GetDC(ghwnd);
	iPixelFormatIndex = ChoosePixelFormat(ghdc,&pfd);
	
	if(iPixelFormatIndex == 0)
	{
		return -1;
	}
	
	if(SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		return -2;
	}
	
	//Bridging API
	
	ghrc = wglCreateContext(ghdc);
	
	if(ghrc == NULL)
	{
		return -3;
	}
	
	if(wglMakeCurrent(ghdc,ghrc) == FALSE)
	{
		return -4;
	}
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	
	//Light
	/*glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbientZero);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiffuseZero);
	glLightfv(GL_LIGHT0,GL_SPECULAR,LightSpecular);	
	glLightfv(GL_LIGHT0,GL_POSITION,LightPositionZero);
	glEnable(GL_LIGHT0);
	
	glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmbientOne);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuseOne);
	glLightfv(GL_LIGHT1,GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT1,GL_POSITION,LightPositionOne);
	glEnable(GL_LIGHT1);*/
	
	glLightfv(GL_LIGHT0,GL_AMBIENT,light[0].LightAmbient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light[0].LightDiffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light[0].LightSpecular);	
	glLightfv(GL_LIGHT0,GL_POSITION,light[0].LightPosition);
	glEnable(GL_LIGHT0);
	
	glLightfv(GL_LIGHT1,GL_AMBIENT,light[1].LightAmbient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light[1].LightDiffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light[1].LightSpecular);
	glLightfv(GL_LIGHT1,GL_POSITION,light[1].LightPosition);
	glEnable(GL_LIGHT1);
	resize(WIN_WIDTH,WIN_HEIGHT);
	return 0;
}

void resize(int width,int height)
{
	if(height ==0)
	{
		height = 1;
	}
	glViewport(0,0,(GLsizei)width,(GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f,((GLfloat)width/(GLfloat)height),0.1f,100.0f);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-4.0f);
	glRotatef(angleRotate,0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);
	
	glNormal3f(0.0f,0.447214f,0.894427f);
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	
	glNormal3f(0.894427f, 0.447214f, 0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	
	glNormal3f(0.0f, 0.447214f, -0.894427f);
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	
	glNormal3f(-0.894427f, 0.447214f, 0.0f);
	glVertex3f(0.0f,1.0f,0.0f);	
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	
	glEnd();
	
	SwapBuffers(ghdc);
}
void update(void){
	angleRotate = angleRotate +0.2f;
	if(angleRotate >=360.0f){
		angleRotate = 0.0f;
	}

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