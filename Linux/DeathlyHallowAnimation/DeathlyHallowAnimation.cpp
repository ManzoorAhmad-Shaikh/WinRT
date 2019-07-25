#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<unistd.h>
#include<math.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>

//opengl
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

//namespaces
using namespace std;
#define NUM_POINTS 1000
//global variables

bool bFullscreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpxVisualInfo = NULL;
Colormap gColormap;
Window gWindow;
int giWindowWidth = 800;
int giWindowHeight = 600;
float x = 0.0f,y = 0.0f;
static float Ox = 0.0f,Oy = 0.0f,radius = 0.0f;
int count = 10,flagTri = 1,flagCircle = 0,flagLine = 0;
float translateTri = 2.0f,translateCircle = -2.0f,translateLine = 2.0f;

GLXContext gGLXContext;
//entry -point function
int main(void){
	//function declaration

	void CreateWindow(void);
	void ToggleFullscreen(void);
	void uninitialize();

	//opengl

	void initialize();
	void resize(int,int);
	void display(void);
	//variable declaration
	int winWidth = giWindowHeight;
	int winHeight = giWindowHeight;
	char keys[26];
	//opengl
	bool bDone = false;

	//code
	CreateWindow();
	initialize();

	//Message Loop
	XEvent event;
	KeySym keysym;

	while(bDone == false){
		while(XPending(gpDisplay)){
			XNextEvent(gpDisplay,&event);
			switch(event.type){
				case MapNotify:
					
					break;
				case KeyPress:
					keysym = XkbKeycodeToKeysym(gpDisplay,event.xkey.keycode,0,0);
					switch(keysym){
						case XK_Escape:
							bDone = true;
							break;
						default:
							break;
					}
					XLookupString(&event.xkey, keys,sizeof(keys),NULL,NULL);
					switch(keys[0]){
						case 'F':
						case 'f':
							if(bFullscreen == false){
								ToggleFullscreen();
								bFullscreen = true;
							}
							else{
								ToggleFullscreen();
								bFullscreen = false;
							}
							break;
						default:
							break;
						}
					break;
			
			case ButtonPress:
				switch(event.xbutton.button){
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					default:
						break;
				}
				break;

			case MotionNotify:
				break;
			case ConfigureNotify:
				winWidth = event.xconfigure.width;
				winHeight = event.xconfigure.height;
				resize(winWidth,winHeight);
				break;

			case Expose:
				break;
			case DestroyNotify:
				break;
			case 33:
				bDone = true;
				break;
			default:
				break;
			}
		
		}
		//disp
		//update
		display();	
	}

	uninitialize();
	return(0);
}

void CreateWindow(void){

	//function prototype
	void uninitialize(void);

	//variables
	XSetWindowAttributes winAttribs;
	int defaultScreen;
	int defaultDepth;
	int styleMask;

	//opengl
	static int frameBufferAttributes[] = {GLX_RGBA,
						GLX_DOUBLEBUFFER,True,
						GLX_RED_SIZE,1,
						GLX_GREEN_SIZE,1,
						GLX_BLUE_SIZE,1,
						GLX_ALPHA_SIZE,1,
						None};
	//code
	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL){
		printf("ERROR : Unable to Open X Display. \n Exitting Now...\n");
		uninitialize();
		exit(1);
	}

	defaultScreen = XDefaultScreen(gpDisplay);
	defaultDepth = DefaultDepth(gpDisplay,defaultScreen);

	gpxVisualInfo = glXChooseVisual(gpDisplay,defaultScreen,frameBufferAttributes);
	
	if(gpxVisualInfo == NULL){
		printf("ERROR : Unable to get a Visual.\n Exitting now.\n");
		uninitialize();
		exit(1);
	}

	winAttribs.border_pixel = 0;
	winAttribs.border_pixmap = 0;
	winAttribs.background_pixmap = 0;
	winAttribs.background_pixel = BlackPixel(gpDisplay,defaultScreen);
	winAttribs.colormap = XCreateColormap(gpDisplay,
				RootWindow(gpDisplay,gpxVisualInfo->screen),
				gpxVisualInfo->visual,
				AllocNone);
	gColormap = winAttribs.colormap;

	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | ButtonPressMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;

	styleMask = CWBorderPixel | CWBackPixel | CWEventMask | CWColormap;

	gWindow = XCreateWindow(gpDisplay,
		RootWindow(gpDisplay,gpxVisualInfo->screen),
		0,0,giWindowWidth,giWindowHeight,
		0,
		gpxVisualInfo->depth,
		InputOutput,
		gpxVisualInfo->visual,
		styleMask,
		&winAttribs);
	if(!gWindow){
	printf("ERROR : Failed to create Main Window.\n Exitting now.\n");
	uninitialize();
	exit(1);
	}

	XStoreName(gpDisplay,gWindow,"First Window");

	Atom windowManagerDelete = XInternAtom(gpDisplay,"WM_DELETE_WINDOW",True);
	XSetWMProtocols(gpDisplay,gWindow,&windowManagerDelete,1);

	XMapWindow(gpDisplay,gWindow);
}

void ToggleFullscreen(void){
	//variable
	Atom wm_state;
	Atom fullscreen;
	XEvent xev={0};

	//code
	wm_state = XInternAtom(gpDisplay,"_NET_WM_STATE",False);
	memset(&xev,0,sizeof(xev));

	xev.type = ClientMessage;
	xev.xclient.window = gWindow;
	xev.xclient.message_type=wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0]=bFullscreen ? 0 : 1;

	fullscreen = XInternAtom(gpDisplay,"_NET_WM_STATE_FULLSCREEN",False);
	xev.xclient.data.l[1] = fullscreen;

	XSendEvent(gpDisplay,
	RootWindow(gpDisplay,gpxVisualInfo->screen),
	False,
	StructureNotifyMask,
	&xev);
}

void initialize(void){
	void uninitialize(void);
	void resize(int,int);

	gGLXContext = glXCreateContext(gpDisplay,gpxVisualInfo,NULL,GL_TRUE);
	glXMakeCurrent(gpDisplay,gWindow,gGLXContext);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	resize(giWindowWidth,giWindowHeight);
}

void resize(int width,int height){
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
	
	
}


void Triangle(){
	glLoadIdentity();
	glTranslatef(translateTri,-translateTri,-4.0f);
	//glRotatef(angleRotate,0.0f,1.0f,0.0f);
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
	sleep(5);
	
}

void Circle(float Ox,float Oy,float angle,float radius){
	glLoadIdentity();
	glTranslatef(translateCircle,translateCircle,-4.0f);
	//glRotatef(angleRotate,0.0f,1.0f,0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i=0;i<NUM_POINTS;i++)
	{
		angle = (2.0f*M_PI*i/NUM_POINTS);
		
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f((Ox+radius*cos(angle)), (Oy+radius*sin(angle)), 0.0f);
	}

	glEnd();
	sleep(5);
}

void Line(){
	glLoadIdentity();
	glTranslatef(0.0f,translateLine,-4.0f);
	//glRotatef(angleRotate,0.0f,1.0f,0.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(0.0f,1.0f);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex2f(0.0f,-1.0f);
	glEnd();
	sleep(5);
}
void display(void){
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
			translateTri = translateTri - 0.02f;
			
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
			translateCircle = translateCircle + 0.02f;
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
			translateLine = translateLine - 0.02f;
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
	
	glXSwapBuffers(gpDisplay,gWindow);
}

void uninitialize(void){

	GLXContext currentGLXContext = glXGetCurrentContext();
	if(currentGLXContext != NULL && currentGLXContext == gGLXContext){
		glXMakeCurrent(gpDisplay,0,0);	
	}
	if(gGLXContext){
		glXDestroyContext(gpDisplay,gGLXContext);
	}
	if(gWindow){
	XDestroyWindow(gpDisplay,gWindow);
	gWindow = 0;
	}

	if(gColormap){
	XFreeColormap(gpDisplay,gColormap);
	gColormap = 0;
	}

	if(gpxVisualInfo){
	free(gpxVisualInfo);
	gpxVisualInfo = NULL;
	}

	if(gpDisplay){
	XCloseDisplay(gpDisplay);
	gpDisplay = NULL;
	}
}
