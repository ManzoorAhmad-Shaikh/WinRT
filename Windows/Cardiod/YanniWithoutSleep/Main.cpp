//POINTS
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<Mmsystem.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#define _USE_MATH_DEFINES 1
#include<math.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define NUM_POINTS 100
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
float x = 0.0f,y = 0.0f;
float factor1 = 1.0f;
int factor = 2;
GLfloat angleTri = 0.0f;
GLfloat red = 1.0f;
GLfloat green = 0.0f;
GLfloat blue = 0.0f;
int RGBCount = 0;
float min = 0.0000001f,max = 0.0001f,avg = 0.0f;
//Callbcak declaration
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdline,int iCmdShow)
{
	int initialize(void);
	void display(void);
	void RandomNumbers(float,float);
	//variable declaration
	
	bool bDone = false;
	int iRet = 0;
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclassex;
	TCHAR szAppName[] = TEXT("Perspective PROJECTION : Line");
	
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
							TEXT("Perspective PROJECTION : Line"),
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
	PlaySound(TEXT("Yanni1.wav"),NULL,SND_FILENAME | SND_ASYNC);
	//system("pause");
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
			//here call display
			display();
			RandomNumbers(min,max);
			angleTri = angleTri + 0.05f;
			if(RGBCount == 0){
				if(blue == 1.0f){
					red = 0.0f;
					green = 0.0f;
					blue = 0.0f;
					RGBCount =1;
				}
				if(green == 1.0f){
					green = 0.0f;
					red = 0.0f;
					blue = 1.0f;
				}
				if(red == 1.0f){
					//red = red + 0.1f;
					red = 0.0f;
					green = 1.0f;
					blue = 0.0f;
				}
				
				fprintf(gpFile,"Count %d\n",RGBCount);
			}
			else{
			
				if(red < 1.0f){
					red = red +0.1f;
				}
				else{
					if(green < 1.0f){
						green = green + 0.1f;
					}
					else{
						if(blue < 1.0f){
							blue = blue + 0.1f;
						}
						else{
							red = 0.0f;
							green = 0.0f;
							blue = 0.0f;
						}
					}
				}
				fprintf(gpFile,"Count %d\n",RGBCount);
			}
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

		case WM_ERASEBKGND:
			return(0);
		case WM_DESTROY:
			uninitialize();
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

void RandomNumbers(float min,float max){
	float scale = rand()/(float)RAND_MAX;
	avg = min + scale*(max-min);
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
	
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	
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
	int i= 0,j=0;
	float angle1,angle2,r = 1.0f;
	//x = x + 0.05f;
	//y = y + 0.05f;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-3.0f);
	glBegin(GL_LINE_LOOP);
	for (int i=0;i<NUM_POINTS;i++)
	{	
		j = i%NUM_POINTS;
		angle1 = (2.0f*M_PI*i/NUM_POINTS);
		
		glColor3f(red,green,blue);
		glVertex3f( cos(angle1 + M_PI),  sin(angle1 + M_PI), 0.0f);
	}
	glEnd();
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-3.0f);
	//glRotatef(angleTri, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	for(int i=0;i<NUM_POINTS;i++){
		j = i%NUM_POINTS;
		angle1 = ((2.0f*M_PI*(i))/NUM_POINTS);
		angle2 = (2.0f*M_PI*(i*factor1)/NUM_POINTS);
		glColor3f(red,green,blue);
		glVertex3f(r * cos(angle1 + M_PI), r * sin(angle1 + M_PI), 0.0f);
		glColor3f(red,green,blue);
		glVertex3f(r * cos(angle2 + M_PI), r * sin(angle2 + M_PI), 0.0f);
		
	}
	glEnd();
	factor1 = factor1 + avg;
	//Sleep(avg);
	if(factor1 >= 10.0f)
		factor1 = 1.0f;
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
