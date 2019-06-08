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
float year = 0, day = 0,moon = 0;
float moonColor[3] = {244.0f/255.0f,244.0f/255.0f,244.0f/255.0f};
GLUquadric *quadric[24];
bool bLight = false;
GLfloat LightAmbient [] = {0.0f,0.0f,0.0f,1.0f};
GLfloat LightDiffuse [] = {1.0f,1.0f,1.0f,1.0f};
GLfloat LightSpecular [] = {1.0f,1.0f,1.0f,1.0f};
GLfloat LightPosition [] = {0.0f,0.0f,0.0f,1.0f};

GLfloat light_model_ambient[] = {0.2f,0.2f,0.2f,1.0f};
GLfloat light_model_local_viewer[] = {0.0f};

GLfloat angleOfXRotation = 0.0f;
GLfloat angleOfYRotation = 0.0f;
GLfloat angleOfZRotation = 0.0f;

GLint keyPressed = 0;
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
void update(void){
	angleOfXRotation = angleOfXRotation + 0.2f;
	if(angleOfXRotation >=360.0f)
		angleOfXRotation = 0.0f;
	angleOfYRotation = angleOfYRotation + 0.2f;
	if(angleOfYRotation >=360.0f)
		angleOfYRotation = 0.0f;
	angleOfZRotation = angleOfZRotation + 0.2f;
	if(angleOfZRotation >=360.0f)
		angleOfZRotation = 0.0f;
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
			switch(wParam){
				
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
				case 'x':
				case 'X':keyPressed = 1;
							angleOfXRotation = 0.0f;
							break;
				case 'y':
				case 'Y':keyPressed = 2;
							angleOfYRotation = 0.0f;
							break;
				case 'z':
				case 'Z':keyPressed = 3;
							angleOfZRotation = 0.0f;
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
	glClearColor(0.25f,0.25f,0.25f,1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	
	//lights
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiffuse);
	//glLightfv(GL_LIGHT0,GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT0,GL_POSITION,LightPosition);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_model_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER,light_model_local_viewer);
	glEnable(GL_LIGHT0);
	
	for(int i = 0;i<24;i++){
		quadric[i] = gluNewQuadric();
	}
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
	
	if(width<= height)
	{
		glOrtho(0.0f,
				15.5f,
				0.0f,
				(15.5f*((GLfloat)height/(GLfloat)width) ),
				-10.0f,
				10.0f);
	}
	else
	{
		glOrtho(0.0f,
				(15.5f*((GLfloat)width/(GLfloat)height) ),
				0.0f,
				15.5f,
				-10.0f,
				10.0f);
		
	}
}

void display(void)
{
	void Draw24Sphere(void);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if(keyPressed == 1){
		glRotatef(angleOfXRotation,1.0f,0.0f,0.0f);
		LightPosition[0] = angleOfXRotation;
		LightPosition[1] = 0.0f;
		LightPosition[2] = 0.0f;
	}
	else if(keyPressed == 2){
		glRotatef(angleOfYRotation,0.0f,1.0f,0.0f);
		LightPosition[1] = angleOfYRotation;
		LightPosition[0] = 0.0f;
		LightPosition[2] = 0.0f;
	}
	else if(keyPressed == 3){
		glRotatef(angleOfZRotation,0.0f,0.0f,1.0f);
		LightPosition[2] = angleOfZRotation;
		LightPosition[0] = 0.0f;
		LightPosition[1] = 0.0f;
	}
	
	glLightfv(GL_LIGHT0,GL_POSITION,LightPosition);
	Draw24Sphere();
		
	SwapBuffers(ghdc);
}

void Draw24Sphere(void){
	
	//common lines for 24 sphere
	GLfloat MaterialAmbient [4];
	GLfloat MaterialDiffuse [4];
	GLfloat MaterialSpecular [4];
	GLfloat MaterialShininess[1];
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//1st sphere
	MaterialAmbient[0] = 0.0215f;
	MaterialAmbient[1] = 0.1745f;
	MaterialAmbient[2] = 0.0215f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.07568f;
	MaterialDiffuse[1] =0.61424f;
	MaterialDiffuse[2] =0.07568f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.633f;
	MaterialSpecular[1] = 0.727811f;
	MaterialSpecular[2] =0.633f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.6f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f,14.0f,0.0f);
	gluSphere(quadric[0],1.0f,30,30);
	
	//2nd sphere
	MaterialAmbient[0] =0.135f;
	MaterialAmbient[1] = 0.2225f;
	MaterialAmbient[2] = 0.1575f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.54f;
	MaterialDiffuse[1] = 0.89f;
	MaterialDiffuse[2] =0.63f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.316228f;
	MaterialSpecular[1] = 0.316228f;
	MaterialSpecular[2] =0.316228f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.1f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f,11.91f,0.0f);
	gluSphere(quadric[1],1.0f,30,30);
	
	//3rd sphere
	MaterialAmbient[0] = 0.05375f;
	MaterialAmbient[1] = 0.05f;
	MaterialAmbient[2] = 0.06625f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.18275f;
	MaterialDiffuse[1] =0.17f;
	MaterialDiffuse[2] =0.22525f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.332741f;
	MaterialSpecular[1] = 0.328634f;
	MaterialSpecular[2] =0.346435f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.3f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f,9.83f,0.0f);
	gluSphere(quadric[2],1.0f,30,30);
	
	//4th sphere
	MaterialAmbient[0] = 0.25f;
	MaterialAmbient[1] = 0.20725f;
	MaterialAmbient[2] = 0.20725f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 1.0f;
	MaterialDiffuse[1] =0.829f;
	MaterialDiffuse[2] =0.829f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.296648f;
	MaterialSpecular[1] = 0.296648f;
	MaterialSpecular[2] = 0.296648f;
	MaterialSpecular[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.088f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f,7.75f,0.0f);
	gluSphere(quadric[3],1.0f,30,30);
	
	//5th sphere
	MaterialAmbient[0] = 0.1745f;
	MaterialAmbient[1] = 0.01175f;
	MaterialAmbient[2] = 0.01175f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.61424f;
	MaterialDiffuse[1] =0.04136f;
	MaterialDiffuse[2] =0.04136f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.727811f;
	MaterialSpecular[1] = 0.626959f;
	MaterialSpecular[2] =0.626959f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.6f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f,5.67f,0.0f);
	gluSphere(quadric[4],1.0f,30,30);
	
	//6th SPhere
	
	MaterialAmbient[0] = 0.1f;
	MaterialAmbient[1] = 0.18725f;
	MaterialAmbient[2] = 0.1745f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.396f;
	MaterialDiffuse[1] = 0.74151f;
	MaterialDiffuse[2] =0.69102f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.297254f;
	MaterialSpecular[1] = 0.30829f;
	MaterialSpecular[2] =0.306678f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.1f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.5f,3.59f,0.0f);
	gluSphere(quadric[5],1.0f,30,30);
	
	//7th sphere
	
	MaterialAmbient[0] = 0.329412f;
	MaterialAmbient[1] = 0.223529f;
	MaterialAmbient[2] = 0.027451f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.780392f;
	MaterialDiffuse[1] =0.568627f;
	MaterialDiffuse[2] =0.113725f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.992157f;
	MaterialSpecular[1] = 0.941176f;
	MaterialSpecular[2] =0.807843f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.21794872f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(4.62f,14.0f,0.0f);
	gluSphere(quadric[6],1.0f,30,30);
	
	//8th sphere
	MaterialAmbient[0] = 0.2125f;
	MaterialAmbient[1] = 0.1275f;
	MaterialAmbient[2] = 0.054f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.714f;
	MaterialDiffuse[1] =0.4284f;
	MaterialDiffuse[2] =0.18144f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.393548f;
	MaterialSpecular[1] = 0.271906f;
	MaterialSpecular[2] =0.166721f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.2f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(4.62f,11.91f,0.0f);
	gluSphere(quadric[7],1.0f,30,30);
	
	//9 sphere
	MaterialAmbient[0] = 0.25f;
	MaterialAmbient[1] = 0.25f;
	MaterialAmbient[2] = 0.25f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.4f;
	MaterialDiffuse[1] =0.4f;
	MaterialDiffuse[2] =0.4f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.774597f;
	MaterialSpecular[1] = 0.774597f;
	MaterialSpecular[2] =0.774597f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.6f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(4.62f,9.83f,0.0f);
	gluSphere(quadric[8],1.0f,30,30);
	
	//10
	MaterialAmbient[0] = 0.19125f;
	MaterialAmbient[1] = 0.0735f;
	MaterialAmbient[2] = 0.0225f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.7038f;
	MaterialDiffuse[1] =0.27048f;
	MaterialDiffuse[2] =0.0828f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.256777f;
	MaterialSpecular[1] = 0.137622f;
	MaterialSpecular[2] =0.086014f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.1f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(4.62f,7.75f,0.0f);
	gluSphere(quadric[9],1.0f,30,30);
	
	//11
	MaterialAmbient[0] = 0.24725f;
	MaterialAmbient[1] = 0.1995f;
	MaterialAmbient[2] = 0.0745f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.75164f;
	MaterialDiffuse[1] =0.60648f;
	MaterialDiffuse[2] =0.22648f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.628281f;
	MaterialSpecular[1] = 0.555802f;
	MaterialSpecular[2] =0.366065f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.4f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(4.62f,5.67f,0.0f);
	gluSphere(quadric[10],1.0f,30,30);
	
	//12
	
	MaterialAmbient[0] = 0.19225f;
	MaterialAmbient[1] = 0.19225f;
	MaterialAmbient[2] = 0.19225f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.50754f;
	MaterialDiffuse[1] =0.50754f; 
	MaterialDiffuse[2] =0.50754f;
	MaterialDiffuse[3] =1.0f; 
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.508273f; 
	MaterialSpecular[1] = 0.508273f; 
	MaterialSpecular[2] =0.508273f; 
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.4f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(4.62f,3.59f,0.0f);
	gluSphere(quadric[11],1.0f,30,30);
	
	//13
	MaterialAmbient[0] = 0.0f;
	MaterialAmbient[1] = 0.0f;
	MaterialAmbient[2] = 0.0f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.01f;
	MaterialDiffuse[1] =0.01f; 
	MaterialDiffuse[2] =0.01f; 
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.50f;
	MaterialSpecular[1] = 0.50f;
	MaterialSpecular[2] =0.50f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.25f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.74f,14.0f,0.0f);
	gluSphere(quadric[12],1.0f,30,30);
	
	//14
	MaterialAmbient[0] = 0.0f;
	MaterialAmbient[1] = 0.1f;
	MaterialAmbient[2] = 0.06f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.0f;
	MaterialDiffuse[1] =0.50980392f;
	MaterialDiffuse[2] =0.50980392f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.50196078f;
	MaterialSpecular[1] = 0.50196078f;
	MaterialSpecular[2] =0.50196078f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.25f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.74f,11.91f,0.0f);
	gluSphere(quadric[13],1.0f,30,30);
	
	//15
	MaterialAmbient[0] = 0.0f;
	MaterialAmbient[1] = 0.0f;
	MaterialAmbient[2] = 0.0f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.1f;
	MaterialDiffuse[1] =0.35f;
	MaterialDiffuse[2] =0.1f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.45f;
	MaterialSpecular[1] = 0.55f;
	MaterialSpecular[2] =0.45f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.25f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.74f,9.83f,0.0f);
	gluSphere(quadric[14],1.0f,30,30);
	
	//16
	MaterialAmbient[0] = 0.0f;
	MaterialAmbient[1] = 0.0f;
	MaterialAmbient[2] = 0.0f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.5f;
	MaterialDiffuse[1] =0.0f;
	MaterialDiffuse[2] =0.0f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.7f;
	MaterialSpecular[1] = 0.6f;
	MaterialSpecular[2] =0.6f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.25f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.74f,7.75f,0.0f);
	gluSphere(quadric[15],1.0f,30,30);
	
	//17
	MaterialAmbient[0] = 0.0f;
	MaterialAmbient[1] = 0.0f;
	MaterialAmbient[2] = 0.0f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.55f;
	MaterialDiffuse[1] =0.55f;
	MaterialDiffuse[2] =0.55f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.70f;
	MaterialSpecular[1] = 0.70f;
	MaterialSpecular[2] =0.70f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.25f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.74f,5.67f,0.0f);
	gluSphere(quadric[16],1.0f,30,30);
	
	//18
	MaterialAmbient[0] = 0.0f;
	MaterialAmbient[1] = 0.0f;
	MaterialAmbient[2] = 0.0f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.5f;
	MaterialDiffuse[1] =0.5f;
	MaterialDiffuse[2] =0.0f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.60f;
	MaterialSpecular[1] = 0.60f;
	MaterialSpecular[2] =0.50f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.25f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(7.74f,3.59f,0.0f);
	gluSphere(quadric[17],1.0f,30,30);
	
	//19
	
	MaterialAmbient[0] = 0.02f;
	MaterialAmbient[1] = 0.02f;
	MaterialAmbient[2] = 0.02f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.1f;
	MaterialDiffuse[1] =0.01f;
	MaterialDiffuse[2] =0.01f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.4f;
	MaterialSpecular[1] = 0.4f;
	MaterialSpecular[2] =0.4f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.078125f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10.86f,14.0f,0.0f);
	gluSphere(quadric[18],1.0f,30,30);
	
	//20
	MaterialAmbient[0] = 0.0f;
	MaterialAmbient[1] = 0.05f;
	MaterialAmbient[2] = 0.05f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.4f;
	MaterialDiffuse[1] =0.5f;
	MaterialDiffuse[2] =0.5f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.04f;
	MaterialSpecular[1] = 0.7f;
	MaterialSpecular[2] =0.7f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.078125f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10.86f,11.91f,0.0f);
	gluSphere(quadric[19],1.0f,30,30);
	
	//21
	
	MaterialAmbient[0] = 0.0f;
	MaterialAmbient[1] = 0.05f;
	MaterialAmbient[2] = 0.0f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.4f;
	MaterialDiffuse[1] =0.5f;
	MaterialDiffuse[2] =0.4f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.04f;
	MaterialSpecular[1] = 0.7f;
	MaterialSpecular[2] =0.04f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.078125f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10.86f,9.83f,0.0f);
	gluSphere(quadric[20],1.0f,30,30);
	
	//22
	MaterialAmbient[0] = 0.05f;
	MaterialAmbient[1] = 0.0f;
	MaterialAmbient[2] = 0.0f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.5f;
	MaterialDiffuse[1] =0.4f;
	MaterialDiffuse[2] =0.4f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.7f;
	MaterialSpecular[1] = 0.04f;
	MaterialSpecular[2] =0.04f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.078125f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10.86f,7.75f,0.0f);
	gluSphere(quadric[21],1.0f,30,30);
	
	//23
	MaterialAmbient[0] = 0.05f;
	MaterialAmbient[1] = 0.05f;
	MaterialAmbient[2] = 0.05f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.5f;
	MaterialDiffuse[1] =0.5f;
	MaterialDiffuse[2] =0.5f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.7f;
	MaterialSpecular[1] = 0.7f;
	MaterialSpecular[2] =0.7f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.078125f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10.86f,5.67f,0.0f);
	gluSphere(quadric[22],1.0f,30,30);
	
	//24
	
	MaterialAmbient[0] = 0.05f;
	MaterialAmbient[1] = 0.05f;
	MaterialAmbient[2] = 0.0f;
	MaterialAmbient[3] = 1.0f;
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	
	MaterialDiffuse[0] = 0.5f;
	MaterialDiffuse[1] =0.5f;
	MaterialDiffuse[2] =0.4f;
	MaterialDiffuse[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	
	MaterialSpecular[0] = 0.7f;
	MaterialSpecular[1] = 0.7f;
	MaterialSpecular[2] =0.04f;
	MaterialSpecular[3] =1.0f;
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	
	MaterialShininess[0] = 0.078125f * 128;
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(10.86f,3.59f,0.0f);
	gluSphere(quadric[23],1.0f,30,30);
}
void uninitialize(void)
{	
	for(int i=0;i<24;i++){
		if(quadric[i])
			gluDeleteQuadric(quadric[i]);
		quadric[i] = NULL;
	}
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