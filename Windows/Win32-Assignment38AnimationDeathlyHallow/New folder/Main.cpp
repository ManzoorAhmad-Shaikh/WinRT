//POINTS
#include<stdio.h>
#include<windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#define _USE_MATH_DEFINES 1
#include<math.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

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
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
MONITORINFO mi;

FILE *gpFile = NULL;
float x = 0.0f,y = 0.0f;
static float Ox = 0.0f,Oy = 0.0f,radius = 0.0f;
int count = 10,flagTri = 1,flagCircle = 0,flagLine = 0;
float translateTri = 2.0f,translateCircle = -2.0f,translateLine = 2.0f;
//static float Ox = 0.0f,Oy = -0.38f,radius = 0.62f;;
//Callbcak declaration
float angleTri = 0.0f;
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
void update(void){
	angleTri = angleTri +0.2f;
	if(angleTri >=360.0f){
		angleTri = 0.0f;
	}

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

void Calculate(float x1,float y1,float x2,float y2,float x3,float y3){
	float a,b,c, p;
	c = pow((y2 - y1),2)+pow((x2-x1),2);
	c = sqrt(c);
	
	a = pow((y3 - y2),2) + pow((x3 - x2),2);
	a = sqrt(a);
	
	b = pow((y3 - y1),2) + pow((x3 - x1),2);
	b = sqrt(b);
	
	p = (a+b+c);
	Ox = ((a*x1)+(b*x2)+(c*x3))/p;
	Oy = ((a*y1)+(b*y2)+(c*y3))/p;
	
	radius = y1 + Oy;
	fprintf(gpFile,"x1 %f\n x2 %f\n x3 %f\n y1 %f\n y2 %f\n y3 %f\n a %f\n b %f\n c %f\n Ox %f\n Oy %f\n radius %f\n",x1,x2,x3,y1,y2,y3,a,b,c,Ox,Oy,radius);
	
}


void Triangle(){
	glLoadIdentity();
	glTranslatef(translateTri,-translateTri,-4.0f);
	glRotatef(angleTri,0.0f,1.0f,0.0f);
	glBegin(GL_LINES);
	
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(0.0f,1.0f);//Top
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(-1.0f,-1.0f);//Top
	
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(-1.0f,-1.0f);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(1.0f,-1.0f);
	
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(1.0f,-1.0f);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(0.0f,1.0f);
	
	
	glEnd();	
	//Sleep(60);
	
}

void Circle(float Ox,float Oy,float angle,float radius){
	glLoadIdentity();
	glTranslatef(translateCircle,translateCircle,-4.0f);
	glRotatef(angleTri,0.0f,1.0f,0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i=0;i<NUM_POINTS;i++)
	{
		angle = (2.0f*M_PI*i/NUM_POINTS);
		
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f((Ox+radius*cos(angle)), (Oy+radius*sin(angle)), 0.0f);
	}

	glEnd();
//	Sleep(60);
}

void Line(){
	glLoadIdentity();
	glTranslatef(0.0f,translateLine,-4.0f);
	glRotatef(angleTri,0.0f,1.0f,0.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(0.0f,1.0f);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(0.0f,-1.0f);
	glEnd();
	//Sleep(60);
}

void display(void)
{
	int i= 0;
	
	float angle ,x1,x2,y1,y2;
	
	x1 = 0.0f;
	y1 = 1.0f;
	x2 = 1.0f;
	y2 = 1.0f;
	//x3 = 1.0f;
	//y3 = -1.0f;
	
	//x = x + 0.05f;
	//y = y + 0.05f;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	Calculate(x1,y1,-x2,-y2,x2,-y2);
	glLoadIdentity();
	if(flagTri == 1){
		if(translateTri >= 0.0f){
			glLoadIdentity();
			Triangle();
			translateTri = translateTri - 0.002f;
			
		}else{
			flagTri = 0;
			flagCircle = 1;
			count=10;
		}
	}else{
		translateTri = 0.0f;
		Triangle();
	}
	if(flagCircle == 1){
		if(translateCircle <= 0){
			glLoadIdentity();
			Circle(Ox,Oy,angle,radius);
			translateCircle = translateCircle + 0.002f;
		}
		else{
			flagCircle = -1;
			count = 10;
			flagLine = 1;
		}
	}else if(flagCircle == -1){
		glLoadIdentity();
		translateCircle = 0.0f;
		Circle(Ox,Oy,angle,radius);
	}
	else{}
	
	if(flagLine == 1){
		if(translateLine >= 0.0f){
			glLoadIdentity();
			Line();
			translateLine = translateLine - 0.002f;
		}
		else{
			flagLine = -1;
			count = 0;
		}
	}
	else if(flagLine == -1){
		glLoadIdentity();
		translateLine = 0.0f;
		Line();
	}
	else{}
	count--;
	fprintf(gpFile,"Count : %d\n",count);
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
