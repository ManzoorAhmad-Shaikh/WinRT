#include<stdio.h>
#include<windows.h>
#include<GL/glew.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include"vmath.h"
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"kernel32.lib")

#pragma comment(lib,"opengl32.lib")
#pragma comment (lib,"glew32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
using namespace vmath;
enum{
	AMC_ATTRIBUTE_POSITION = 0,
	AMC_ATTRIBUTE_COLOR,
	AMC_ATTRIBUTE_NORMAL,
	AMC_ATTRIBUTE_TEXCOORD0
};
//Global variable
HDC ghdc = NULL;
HGLRC ghrc = NULL;
bool gbActiveWindow = false;
bool bFullScreen = false;
DWORD dwStyle;
HWND ghwnd = NULL;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
MONITORINFO mi;

FILE *gpFile = NULL;
float angleRotate = 0.0f;
GLenum Result;
//For Shaders
GLuint gVertex_Shader_Object;
GLuint gFragment_Shader_Object;
GLuint gShader_Program_Object;

GLint iShaderCompileStatus = 0;
GLint iInfoLogLength = 0;
GLchar *szInfoLog = NULL;
GLint iProgrmLinkStatus = 0;

GLuint vao;
GLuint vbo;
GLuint mvpUniform;
mat4 orthographicProjectionMatrix;
//Callbcak declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdline, int iCmdShow)
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

	//Game Loop
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
				//update();
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

	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;
	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
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
		bFullScreen = true;
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
	void uninitialize(void);
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
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


	Result = glewInit();

	if (Result != GLEW_OK)
	{
		uninitialize();
	}


	//For Shaders : create 
	gVertex_Shader_Object = glCreateShader(GL_VERTEX_SHADER);

	//Define VS code
	const GLchar *VertexShaderCode = "#version 450 core" \
		"\n" \
		"in vec4 vPosition;" \
		"uniform mat4 u_mvp_matrix;" \
		"void main(void)" \
		" { " \
		"gl_Position = u_mvp_matrix * vPosition ;" \
		" } ";

	//Specify code to Obj
	glShaderSource(gShader_Program_Object,
		1,
		(const GLchar**)&VertexShaderCode,
		NULL);

	//Compile the shader
	glCompileShader(gVertex_Shader_Object);

	/*	//Error Code for VS
		glGetShaderiv(gVertex_Shader_Object,
			GL_COMPILE_STATUS,
			&iShaderCompileStatus);

		if (iShaderCompileStatus == GL_FALSE)
		{
			glGetShaderiv(gVertex_Shader_Object,
				GL_INFO_LOG_LENGTH,
				&iInfoLogLength);

			if (iInfoLogLength > 0) //Error found
			{
				szInfoLog = (GLchar *)malloc(iInfoLogLength);

				if (szInfoLog != NULL)
				{
					GLsizei Written;
					glGetShaderInfoLog(gVertex_Shader_Object, iInfoLogLength, &Written, szInfoLog);

					fprintf(gpFile, "\n  Failed in Vertex Shader");
					free(szInfoLog);
					UnInitialize();
					DestroyWindow(ghwnd);
					exit(0);
				}
			}
		}

	*/
	//2 - FS
	gFragment_Shader_Object = glCreateShader(GL_FRAGMENT_SHADER);

	//Define FS code
	const GLchar *FragmentShaderCode = "#version 450 core" \
		"\n" \
		"out vec4 fragColor;" \
		"void main(void)" \
		" { " \
		"fragColor = vec4(1.0,1.0,1.0,1.0)" \
		" } ";

	//Specify code to Obj
	glShaderSource(gShader_Program_Object, 1,
		(GLchar**)&FragmentShaderCode, NULL);

	//Compile the shader
	glCompileShader(gFragment_Shader_Object);

	/*	//Error check for FS
		glGetShaderiv(gFragment_Shader_Object,
			GL_COMPILE_STATUS,
			&iShaderCompileStatus);

		if (iShaderCompileStatus == GL_FALSE)
		{
			glGetShaderiv(gFragment_Shader_Object,
				GL_INFO_LOG_LENGTH,
				&iInfoLogLength);

			if (iInfoLogLength > 0) //Error found
			{
				szInfoLog = (GLchar *)malloc(iInfoLogLength);

				if (szInfoLog != NULL)
				{
					GLsizei Written;
					glGetShaderInfoLog(gFragment_Shader_Object, iInfoLogLength, &Written, szInfoLog);

					fprintf(gpFile, "\n  Failed in Fragment Shader");
					free(szInfoLog);
					UnInitialize();
					DestroyWindow(ghwnd);
					exit(0);
				}
			}
		}
	*/

	//3 - Create Shader Program
	gShader_Program_Object = glCreateProgram();

	//attach VS & FS
	glAttachShader(gShader_Program_Object, gVertex_Shader_Object);

	glAttachShader(gShader_Program_Object, gFragment_Shader_Object);
	
	glBindAttribLocation(gShader_Program_Object,AMC_ATTRIBUTE_POSITION,"vPosition");
	//Link SP
	glLinkProgram(gShader_Program_Object);

	/*
		// Error check for SP
		glGetProgramiv(gShader_Program_Object, GL_LINK_STATUS, &iProgrmLinkStatus);

		if (iProgrmLinkStatus == GL_FALSE)
		{
			glGetProgramiv(gShader_Program_Object, GL_INFO_LOG_LENGTH, &iInfoLogLength);

			if (iInfoLogLength > 0) //Error found
			{
				szInfoLog = (GLchar *)malloc(iInfoLogLength);

				if (szInfoLog != NULL)
				{
					GLsizei Written;
					glGetProgramInfoLog(gShader_Program_Object, iInfoLogLength, &Written, szInfoLog);

					fprintf(gpFile, "\n  Failed in Shader Program Linking");
					free(szInfoLog);
					UnInitialize();
					DestroyWindow(ghwnd);
					exit(0);
				}
			}
		}
	*/

	mvpUniform =glGetUniformLocation(gShader_Program_Object,"u_mvp_matrix");
	
	
	//orthographic triangle code
	
	const GLfloat triangleVertices[]={0.0f,50.0f,0.0f,
										-50.0f,-50.0f,0.0f,
										50.0f,-50.0f,0.0f};
	
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,
				sizeof(triangleVertices),
				triangleVertices,
				GL_STATIC_DRAW);
	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION,3,
							GL_FLOAT,GL_FALSE,0,NULL);

	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	orthographicProjectionMatrix = mat4::identity();
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
if(width<= height)
	{
		glOrtho(-100.0f,
				100.0f,
				(-100.0f*((GLfloat)height/(GLfloat)width) ),
				(100.0f*((GLfloat)height/(GLfloat)width) ),
				-100.0f,
				100.0f);
	}
	else
	{
		glOrtho((-100.0f*((GLfloat)width/(GLfloat)height) ),
				(100.0f*((GLfloat)width/(GLfloat)height) ),
				-100.0f,
				100.0f,
				-100.0f,
				100.0f);
		
	}

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glUseProgram(gShader_Program_Object);
	mat4 modelViewMatrix;
	mat4 modelViewProjectionMatrix;
	
	modelViewMatrix = mat4::identity();
	modelViewProjectionMatrix = mat4::identity();
	
	//do necessary transformation
	
	//do necessary matrix multiplication
	modelViewProjectionMatrix = orthographicProjectionMatrix*modelViewMatrix;
	
	glUniformMatrix4fv(mvpUniform,1,GL_FALSE,modelViewProjectionMatrix);
	glBindVertexArray(vao);
	
	glDrawArrays(GL_TRIANGLES,0,3);
	glBindVertexArray(0);
	//code
	glUseProgram(0);


	SwapBuffers(ghdc);
}
void uninitialize(void)
{
	if(vbo){
		glDeleteBuffers(1,&vbo);
		vbo = 0;
	}
	if(vao){
		glDeleteVertexArrays(1,&vao);
		vao = 0;
	}
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
	//for Shaders
	glUseProgram(gShader_Program_Object);
	glDetachShader(gShader_Program_Object, gFragment_Shader_Object);
	glDetachShader(gShader_Program_Object, gVertex_Shader_Object);

	glDeleteShader(gFragment_Shader_Object);
	gFragment_Shader_Object = 0;

	glDeleteShader(gVertex_Shader_Object);
	gVertex_Shader_Object = 0;

	glDeleteProgram(gShader_Program_Object);
	glUseProgram(0);


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
