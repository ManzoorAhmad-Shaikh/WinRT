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
#define TRUE 1
#define FALSE 0

typedef int BOOL;

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


typedef struct node{
	struct node *lchild;
	float xCoord;
	float x1Coord;
	float yCoord;
	float y1Coord;
	
	//translate
	float xTranslate;
	float yTranslate;
	float zTranslate;
	
	//rotate
	float xRotate;
	float yRotate;
	float zRotate;
	
	//color
	float r;
	float g;
	float b;
	//angle of rotation
	float angle;
	struct node *rchild;
}NODE, *PNODE,**PPNODE;


void Insert(PPNODE tree,float xCoord,float yCoord,float x1Coord,float y1Coord,
			float xTranslate,float yTranslate,float zTranslate,	float xRotate,
			float yRotate,float zRotate,float r,float g,float b,float angle,int level)
{
	PNODE node = NULL;
	
	if(*tree == NULL){
		node = (PNODE)malloc(sizeof(NODE));
		node->lchild = node->rchild = NULL;
		node->xCoord = xCoord;
		node->x1Coord = x1Coord;
		node->yCoord = yCoord;
		node->y1Coord = y1Coord;
		node->xTranslate = xTranslate;
		node->yTranslate = yTranslate;
		node->zTranslate = zTranslate;
		node->xRotate = xRotate;
		node->yRotate = yRotate;
		node->zRotate = zRotate;
		node->r = r;
		node->g = g;
		node->b = b;
		node->angle = angle;
		*tree = node;
		return;
	}
	
	if(level<3){
		Insert(&((*tree)->lchild),xCoord,x1Coord,yCoord,y1Coord,xTranslate,yTranslate,
				zTranslate,xRotate,yRotate,zRotate,r,g,b,angle,level + 1);
		Insert(&((*tree)->rchild),xCoord,x1Coord,yCoord,y1Coord,xTranslate,yTranslate,
				zTranslate,xRotate,yRotate,zRotate,r,g,b,-45.0f,level + 1);
	}
	else{
		return;
	}
}



//Main code

//Callbcak declaration
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdline,int iCmdShow)
{
	int initialize(void);
	void display(PNODE);
	void update(void);
	
	//variable declaration
	PNODE root = NULL;
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
	Insert(&root,0.0f,-1.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,1.0f,0.0f,0.f,0.0f,0);
	
	Insert(&root,0.0f,0.0f,0.0f,0.5f,
			0.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,1.0f,0.0f,45.0f,0);
			
	Insert(&root,0.0f,0.0f,0.0f,0.3f,
			0.0f,0.5f,0.0f,
			0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,45.0f,0);
			
	Insert(&root,0.0f,0.0f,0.0f,0.15f,
			0.0f,0.3f,0.0f,
			0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,45.0f,0);
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
				//update();
			}
			//here call display
			display(root);
			
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

void Preorder(PNODE tree)
{
	static int flag = 0,flag1 = 0;
	
	if(tree!=NULL){
		glPushMatrix();
		glTranslatef(tree->xTranslate,tree->yTranslate,tree->zTranslate);
		glRotatef(tree->angle,tree->xRotate,tree->yRotate,tree->zRotate);
		//glTranslatef(tree->xTranslate,tree->yTranslate,tree->zTranslate);
		//if(flag == 0){
			glBegin(GL_LINES);
			//flag = 1;
		//}
		glColor3f(tree->r,tree->g,tree->b);
		glVertex3f(tree->xCoord,tree->yCoord,0.0f);
		glColor3f(tree->r,tree->g,tree->b);
		glVertex3f(tree->x1Coord,tree->y1Coord,0.0f);
		glEnd();
		
		Preorder(tree->lchild);
		Preorder(tree->rchild);
		glPopMatrix();
	}
	
}
void display(PNODE tree)
{
	int static flag = 0;
	if(flag == 0){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -3.0f);
		//flag = 1;
	}
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	if(tree!=NULL){
	//glRotatef(tree->angle,tree->xRotate,tree->yRotate,tree->zRotate);
		
			
		Preorder(tree);
		//glEnd();
	}
	/*
glRotatef(tree->angle,tree->xRotate,tree->yRotate,tree->zRotate);
	glBegin(GL_LINES);
		
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(tree->xCoord,tree->yCoord,0.0f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(tree->x1Coord,tree->y1Coord,0.0f);
		
	glEnd();
	//glRotatef(tree->rchild->angle,tree->rchild->xRotate,tree->rchild->yRotate,tree->rchild->zRotate);
	glRotatef(tree->lchild->angle,tree->lchild->xRotate,tree->lchild->yRotate,tree->lchild->zRotate);
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(tree->lchild->xCoord,tree->lchild->yCoord,0.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(tree->lchild->x1Coord,tree->lchild->y1Coord,0.0f);
		
		
	glEnd();
	glTranslatef(1.0f,0.0f,0.0f);
	//glRotatef(tree->rchild->lchild->angle,tree->rchild->lchild->xRotate,tree->rchild->lchild->yRotate,tree->rchild->lchild->zRotate);
	glBegin(GL_LINES);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(tree->rchild->lchild->xCoord,tree->rchild->lchild->yCoord,0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(tree->rchild->lchild->x1Coord,tree->rchild->lchild->y1Coord,0.0f);
		
		
	glEnd();
	*/ /*
	glRotatef(tree->rchild->lchild->angle,tree->rchild->lchild->xRotate,tree->rchild->lchild->yRotate,tree->rchild->lchild->zRotate);
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(tree->rchild->rchild->xCoord,tree->rchild->rchild->yCoord,0.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(tree->rchild->rchild->xCoord,tree->rchild->rchild->yCoord,0.0f);
		
		
	glEnd();*/
	SwapBuffers(ghdc);
}
void update(void){
	

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
