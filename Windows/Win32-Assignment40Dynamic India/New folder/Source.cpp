
#include<stdio.h>
#include<windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#define _USE_MATH_DEFINES 1
#include<math.h>
#include<Mmsystem.h>
#include "resource.h"

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"Winmm.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define NUM_POINTS 1000
//Global variable
HDC ghdc = NULL;
HGLRC ghrc = NULL;
bool gbActiveWindow = false;
bool bFullScreen = false;
DWORD dwStyle;
HWND ghwnd = NULL;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
MONITORINFO mi;


float orange[3] = { 1.0f,153.0f / 255.0f,51.0f / 255.0f };
float green[3] = { 19.0f / 255.0f,136.0f / 255.0f,8.0f / 255.0f };
float pr = 186.0f / 255.0f, pg = 226.0f / 255.0f, pb = 238.0f / 255.0f;
int animationDone = 0, animationDoneFlag = 0;
float anglePlaneOne = 0.0f;
float anglePlaneTwo = 0.0f;
FILE *gpFile = NULL;
//Callbcak declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdline, int iCmdShow)
{
	int initialize(void);
	void display(void);
	void ToggleFullScreen(void);
	//variable declaration

	bool bDone = false;
	int iRet = 0;
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclassex;
	TCHAR szAppName[] = TEXT("Perspective PROJECTION");

	//code
	if (fopen_s(&gpFile, "Log.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Log file cannot be created\n"), TEXT("Error !!!"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Log file successfully created\n");
	}

	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclassex.cbClsExtra = 0;
	wndclassex.cbWndExtra = 0;
	wndclassex.lpfnWndProc = WndProc;
	wndclassex.hInstance = hInstance;
	wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclassex.lpszClassName = szAppName;
	wndclassex.lpszMenuName = NULL;
	wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

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
	
	if (iRet == -1)
	{
		fprintf(gpFile, "Choose Pixel Format failed\n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -2)
	{
		fprintf(gpFile, "Set Pixel Format failed\n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -3)
	{
		fprintf(gpFile, "wglCreateContext failed\n");
		DestroyWindow(hwnd);
	}
	else if (iRet == -4)
	{
		fprintf(gpFile, "wglMakeCurrent failed\n");
		DestroyWindow(hwnd);
	}
	else
	{
		fprintf(gpFile, "Initialization Successful\n");
	}

	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	if (!PlaySound(MAKEINTRESOURCE(MYSOUND), GetModuleHandle(NULL), SND_RESOURCE|SND_ASYNC))
		return 1;
	Sleep(1000);
	//PlaySound(TEXT("Yanni1.wav"), NULL, SND_FILENAME | SND_ASYNC);
	ToggleFullScreen();
	//Game Loop
	//
	
	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
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
			if (gbActiveWindow == true)
			{
				//Here call update
			}
			//here call display
			display();
		}
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declaration
	void ToggleFullScreen(void);
	void resize(int, int);
	void uninitialize(void);

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		//bFullScreen = false;
		//ToggleFullScreen();
		break;
	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;
	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		//ToggleFullScreen();
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_KEYDOWN:
		switch (wParam)
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
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullScreen(void)
{
	if (bFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };

			if (GetWindowPlacement(ghwnd, &wpPrev) &&
				GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle&~WS_OVERLAPPEDWINDOW);
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
		//bFullScreen = true;
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
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
	void resize(int, int);

	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	ghdc = GetDC(ghwnd);
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		return -1;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		return -2;
	}

	//Bridging API

	ghrc = wglCreateContext(ghdc);

	if (ghrc == NULL)
	{
		return -3;
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		return -4;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	resize(WIN_WIDTH, WIN_HEIGHT);
	return 0;
}

void resize(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, ((GLfloat)width / (GLfloat)height), 0.1f, 100.0f);
}
void I(float x) {
	/*float static x = -1.0f;
	if(x <= 0.0f){
		x = x + 0.0001f;
	}
	else
		x = 0.0f;*/
	glLoadIdentity();
	glTranslatef(x, 0.0f, -3.0f);
	glLineWidth(7.0f);
	glBegin(GL_LINES);

	//I
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.7f, 0.7f);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.5f, 0.7f);

	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.7f, -0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.5f, -0.7f);

	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.6f, 0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.6f, -0.7f);
	glEnd();

}
void N(float y) {
	glLoadIdentity();
	glTranslatef(0.0f, y, -3.0f);
	glLineWidth(7.0f);
	glBegin(GL_LINES);

	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.4f, 0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.4f, -0.7f);


	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.4f, 0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.2f, -0.7f);

	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.2f, 0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.2f, -0.7f);

	glEnd();

}
void D(void) {
	static float r = 0.0f, g = 0.0f, b = 0.0f, r1 = 0.0f, g1 = 0.0f, b1 = 0.0f;
	if (animationDoneFlag == 0) {
		if ((r == orange[0] && g == orange[1] && b == orange[2]) || (r1 == green[0] && g1 == green[1] && b1 == green[3])) {
			animationDone = 1;
			animationDoneFlag = 1;
		}
	}
	if ((r < orange[0] && g < orange[1] && b < orange[2])) {
		r = r + 0.003f;
		g = g + 0.003f;
		b = b + 0.003f;
	}
	else {
		r = orange[0];
		g = orange[1];
		b = orange[2];
	}
	if ((r1 < green[0] && g1 < green[1] && b1 < green[2])) {
		r1 = r1 + 0.003f;
		g1 = g1 + 0.003f;
		b1 = b1 + 0.003f;
	}
	else {
		r1 = green[0];
		g1 = green[1];
		b1 = green[2];
	}

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glLineWidth(7.0f);
	glBegin(GL_LINES);
	//orange[0],orange[1],orange[2]
	//green[0],green[1],green[2]
	glColor3f(r, g, b);
	glVertex2f(-0.1f, 0.7f);
	glColor3f(r1, g1, b1);
	glVertex2f(-0.1f, -0.7f);

	glColor3f(r, g, b);
	glVertex2f(-0.15f, 0.7f);
	glColor3f(r, g, b);
	glVertex2f(0.107f, 0.7f);

	glColor3f(r, g, b);
	glVertex2f(0.1f, 0.7f);
	glColor3f(r1, g1, b1);
	glVertex2f(0.1f, -0.7f);

	glColor3f(r1, g1, b1);
	glVertex2f(-0.15f, -0.7f);
	glColor3f(r1, g1, b1);
	glVertex2f(0.107f, -0.7f);

	glEnd();

}
void II(float y) {

	glLoadIdentity();
	glTranslatef(0.0f, y, -3.0f);
	glLineWidth(7.0f);
	glBegin(GL_LINES);

	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(0.2f, 0.7f);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(0.4f, 0.7f);

	glColor3f(green[0], green[1], green[2]);
	glVertex2f(0.2f, -0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(0.4f, -0.7f);

	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(0.3f, 0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(0.3f, -0.7f);

	glEnd();
}
void A(float x) {

	glLoadIdentity();
	glTranslatef(x, 0.0f, -3.0f);
	glLineWidth(7.0f);
	glBegin(GL_LINES);

	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(0.7f, 0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(0.5f, -0.7f);

	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(0.7f, 0.7f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(0.8f, -0.7f);

	glEnd();
}

void PlaneOne(float x3, float y3, float angle) {
	glLoadIdentity();

	glTranslatef(x3, y3, -3.0f);
	glRotatef(anglePlaneOne, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(pr, pg, pb);
	glVertex2f(0.05f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.15f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.15f);
	glEnd();
	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.1f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.05f, 0.2f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, 0.2f);
	glEnd();
	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);
	glEnd();

	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);
	glEnd();

	//glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.11f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.07f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.09f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.09f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.07f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.11f);
	glEnd();

	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.02f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.04f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.02f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.0f);
	glEnd();

	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, -0.01f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, -0.01f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, -0.01f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, -0.04f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.02f, -0.01f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.02f, -0.04f);
	glEnd();

	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(0.02f, 0.2f);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(0.02f, 0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.2f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.3f);

	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.02f, 0.2f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.02f, 0.3f);
	glEnd();

	fprintf(gpFile, "x1 : %f : y1 : %f\n", x3, y3);

}

void PlaneTwo(float x3, float y3, float angle) {
	glLoadIdentity();

	glTranslatef(x3, y3, -3.0f);
	glRotatef(anglePlaneTwo, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(pr, pg, pb);
	glVertex2f(0.05f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.15f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.15f);
	glEnd();
	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.1f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.05f, -0.2f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, -0.2f);
	glEnd();
	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);
	glEnd();

	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);
	glEnd();

	//glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.11f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.07f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.09f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.09f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.07f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.11f);
	glEnd();

	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.02f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.04f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, 0.02f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, 0.0f);
	glEnd();

	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, -0.01f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.04f, -0.01f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, -0.01f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.04f, -0.04f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.02f, -0.01f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.02f, -0.04f);
	glEnd();


	//glLoadIdentity();
	//glTranslatef(x3, y3, -3.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.02f, -0.2f);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.02f, -0.3f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.0f, -0.2f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.0f, -0.3f);

	glColor3f(green[0], green[1], green[2]);
	glVertex2f(0.02f, -0.2f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(0.02f, -0.3f);
	glEnd();

	fprintf(gpFile, "x1 : %f : y1 : %f\n", x3, y3);

}


void PlaneOneTwo(float x3, float y3) {

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_QUADS);

	glColor3f(pr, pg, pb);
	glVertex2f(0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);

	glEnd();

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.1f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.2f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.2f, -0.05f);
	glEnd();
	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.2f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.05f, 0.0f);
	glEnd();

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.2f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.055f, 0.0f);
	glEnd();
	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.09f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.05f, 0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.07f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.07f, -0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.09f, -0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.05f, -0.03f);
	glEnd();

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.02f, -0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.02f, -0.03f);

	glEnd();

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.03f, -0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.03f, 0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.03f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.05f, 0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.03f, 0.01f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.05f, 0.01f);
	glEnd();
	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.2f, 0.03f);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.4f, 0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.2f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.4f, 0.0f);

	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.2f, -0.02f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.4f, -0.02f);
	glEnd();

	fprintf(gpFile, "x2 : %f : y2 : %f\n", x3, y3);

}

void PlaneCentre(float x3) {

	glLoadIdentity();
	glTranslatef(x3, 0.0f, -3.0f);
	glBegin(GL_QUADS);

	glColor3f(pr, pg, pb);
	glVertex2f(0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);

	glEnd();

	glLoadIdentity();
	glTranslatef(x3, 0.0f, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.1f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.2f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.2f, -0.05f);
	glEnd();
	glLoadIdentity();
	glTranslatef(x3, 0.0f, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.2f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.05f, 0.0f);
	glEnd();

	glLoadIdentity();
	glTranslatef(x3, 0.0f, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.2f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.055f, 0.0f);
	glEnd();
	glLoadIdentity();
	glTranslatef(x3, 0.0f, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.09f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.05f, 0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.07f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.07f, -0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.09f, -0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.05f, -0.03f);
	glEnd();

	glLoadIdentity();
	glTranslatef(x3, 0.0f, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.02f, -0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.02f, -0.03f);

	glEnd();

	glLoadIdentity();
	glTranslatef(x3, 0.0f, -3.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.03f, -0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.03f, 0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.03f, 0.03f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.05f, 0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.03f, 0.01f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.05f, 0.01f);
	glEnd();
	glLoadIdentity();
	glTranslatef(x3, 0.0f, -3.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.2f, 0.03f);
	glColor3f(orange[0], orange[1], orange[2]);
	glVertex2f(-0.4f, 0.03f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.2f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.4f, 0.0f);

	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.2f, -0.02f);
	glColor3f(green[0], green[1], green[2]);
	glVertex2f(-0.4f, -0.02f);
	glEnd();

	//fprintf(gpFile,"x2 : %f : y2 : %f\n",x3,y3);

}
void DrawLine(float x5, float x2, float x3, float y, float y1) {
	static float r = orange[0], g = orange[1], b = orange[2], r1 = green[0], g1 = green[1], b1 = green[2], rw = 1.0f, gw = 1.0f, bw = 1.0f;
	static float x = -0.7f, x1 = -0.7f;
	static int count = 0;
	if (x1 > 1.0f) {
		//x = x + 0.0001f;
		r = r - 0.0005f;
		g = g - 0.0005f;
		b = b - 0.0005f;
		r1 = r1 - 0.0005f;
		g1 = g1 - 0.0005f;
		b1 = b1 - 0.0005f;
		rw = rw - 0.0005f;
		gw = gw - 0.0005f;
		bw = bw - 0.0005f;
	}
	/*if(x >= 2.0f){
		I(0.0f);
		A(0.0f);
		N(0.0f);
		II(0.0f);
		D();
	}*/
	x1 = x1 + 0.0008f;
	if (x5 - 0.8f < -0.7f) {
		return;
	}
	else {
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);

		glColor3f(r, g, b);
		glVertex2f(-0.7f, 0.01f);
		glColor3f(r, g, b);
		glVertex2f(x, 0.01f);

		glColor3f(rw, gw, bw);
		glVertex2f(-0.7f, 0.0f);
		glColor3f(rw, gw, bw);
		glVertex2f(x, 0.0f);

		glColor3f(r1, g1, b1);
		glVertex2f(-0.7f, -0.01f);
		glColor3f(r1, g1, b1);
		glVertex2f(x, -0.01f);

		glEnd();
	}

	if (x <= 0.75f)
		x = x + 0.0009f;

	if (x >= 0.75f) {
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);
		glLineWidth(7.0f);

		glBegin(GL_LINES);
		glColor3f(orange[0], orange[1], orange[2]);
		glVertex2f(0.6f, 0.02f);
		glColor3f(orange[0], orange[1], orange[2]);
		glVertex2f(0.75f, 0.02f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(0.6f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(0.75f, 0.0f);

		glColor3f(green[0], green[1], green[2]);
		glVertex2f(0.6f, -0.02f);
		glColor3f(green[0], green[1], green[2]);
		glVertex2f(0.75f, -0.02f);

		glEnd();

		I(0.0f);
		A(0.0f);
		N(0.0f);
		II(0.0f);
		D();

	}
}

void display(void)
{
	float angle, h, k, r = 1.0f;
	static float x = -2.0f, y = 2.0f, x1 = 2.0f, y1 = -2.0f;
	static float x3 = 0.0f, y3 = 0.0f, x4 = 0.0f, y4 = 0.0f, x5 = -2.0f, x6 = 0.0f, y6 = 0.0f, x7 = 0.0f, y7 = 0.0f;
	static int myCount = 0, tot = 0, flag = 0, flag1 = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	if (x < 0.0f) {
		x = x + 0.005f;
	}
	else {
		x = 0.0f;
		myCount = 1;
	}
	I(x);
	glLoadIdentity();

	if (x == 0.0f) {
		if (x1 > 0.0f) {
			x1 = x1 - 0.005f;
		}
		else {
			x1 = 0.0f;
		}
		A(x1);
		if (x1 == 0.0f) {
			if (y > 0.0f) {
				y = y - 0.005f;
			}
			else {
				y = 0.0f;
			}
			N(y);

			if (y == 0.0f) {
				if (y1 < 0.0f) {
					y1 = y1 + 0.005f;
				}
				else {
					y1 = 0.0f;
				}
				II(y1);

				if (y1 == 0.0f) {
					D();
				}
			}
		}
	}
	
	//animationDone = 1;

	if (animationDone == 1) {

		if (tot >= NUM_POINTS) {
			if (y3 < 0.0f) {
				x3 = x3 + 0.0008f;

				y3 = y3 - 0.0008f;
			}
			else {
				x3 = x3 + 0.0008f;
				y3 = 0.0f;
			}
			if (y4 > 0.0f) {
				x4 = x4 - 0.0008f;
				y4 = y3 + 0.0008f;
			}
			else {
				x4 = x4 + 0.00008f;
				y4 = 0.0f;
			}
		}
		x5 = x5 + 0.001f;
		if (tot <= NUM_POINTS) {
			if (flag == 0) {
				h = -1.0f;
				k = 1.0f;

				angle = (2.0f*(M_PI / 4)*tot) / NUM_POINTS;
				x3 = h + r * cos(angle - M_PI);
				y3 = k + r * sin(angle - M_PI);
				PlaneOne(x3, y3, anglePlaneOne);
				h = -1.0f;
				k = -1.0f;
				angle = (2.0f*(-M_PI)*tot) / NUM_POINTS;
				x4 = h - r * cos((angle + M_PI / 4));
				y4 = k - r * sin((angle + M_PI / 4));
				PlaneTwo(x3, -y3, angle);
				PlaneCentre(x5);
				if (anglePlaneOne == 88.0f) {
					anglePlaneOne = 90.0f;
				}
				
					anglePlaneOne = anglePlaneOne + 0.02f;
				

				if (anglePlaneTwo == 88.0f) {
					anglePlaneTwo = 90.0f;
				}
				
					anglePlaneTwo = anglePlaneTwo - 0.02f;
				
				tot++;
			}
			else {

				if (x6 > 1.7f) {
					h = 1.0f;
					k = 1.0f;

					angle = (2.0f*(M_PI / 2)*tot) / NUM_POINTS;
					x3 = h + r * cos(angle - M_PI / 4);
					y3 = k + r * sin(angle - M_PI / 4);
					PlaneOne(x3, -y3, angle);
					h = 1.0f;
					k = -1.0f;
					angle = (2.0f*(-M_PI)*tot) / NUM_POINTS;
					x4 = h - r * cos((angle + M_PI / 4));
					y4 = k - r * sin((angle + M_PI / 4));
					PlaneTwo(x3, y3, angle);
					PlaneCentre(x6);
					x6 = x6 + 0.0008f;
					if (anglePlaneOne < 89.0f) {
						anglePlaneOne = anglePlaneOne - 0.02f;
					}
					else {
						anglePlaneOne = 90.0f;
					}

					if (anglePlaneTwo < 89.0f) {
						anglePlaneTwo = anglePlaneTwo + 0.02f;
					}
					else {
						anglePlaneTwo = 90.0f;
					}
					tot++;
				}
				//Sleep(10);
				PlaneOneTwo(x6, y6);
				DrawLine(x5, x, x1, y, y1);
				x6 = x6 + 0.0008f;
				y6 = 0.0f;
				if (x6 >= 1.9f)
					animationDone = 2;
				//tot++;
			}
		}
		else {
			PlaneOneTwo(x3, y3);
			x6 = x3;
			y6 = y3;
			anglePlaneOne = 0.0f;
			anglePlaneTwo = 0.0f;
			DrawLine(x5, x, x1, y, y1);
			if (x3 > 0.8f) {
				tot = 1;
				flag = 1;
			}
		}

		myCount = 1;
	}
	if (animationDone == 2) {
		DrawLine(x5, x, x1, y, y1);
	}

	SwapBuffers(ghdc);
	//fprintf(gpFile,"x : %f : y : %f\n",x,y);
}

void uninitialize(void)
{
	if (bFullScreen == true)
	{
		//fullscreen else code. except the flag setting
		SetWindowLong(ghwnd,
			GWL_STYLE,
			dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
			HWND_TOP,
			0,
			0,
			0,
			0,
			SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);

		ShowCursor(TRUE);

	}

	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}
	if (gpFile)
	{
		fprintf(gpFile, "Successfully closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}

}
