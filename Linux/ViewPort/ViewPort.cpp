#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

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

//global variables

bool bFullscreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpxVisualInfo = NULL;
Colormap gColormap;
Window gWindow;
int giWindowWidth = 800;
int giWindowHeight = 600;
int x=0,y=0,w=0,h=0;

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
	w = giWindowHeight;
	h = giWindowHeight;
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
						case '1':
							x = 0;
							y=0;
							resize(w/2,h/2);
							break;
						case '2':
							x = w/2;
							y=0;
							resize(w/2,h/2);
							break;
						case '3':
							x = w/2;
							y=h/2;
							resize(w/2,h/2);
							break;
						case '4':
							x = 0;
							y=h/2;
							resize(w/2,h/2);
							break;
						case '5':
							x = 0;
							y=0;
							resize(w/2,h);
							break;
						case '6':
							x = w/2;
							y=0;
							resize(w/2,h);
							break;
						case '7':
							x = 0;
							y=h/2;
							resize(w,h/2);
							break;
						case '8':
							x = 0;
							y=0;
							resize(w,h/2);
							break;
						case '9':
							x = (w/2)/2;
							y=(h/2)/2;
							resize(w/2,h/2);
							break;
						case '0':
							x = 0;
							y=0;
							resize(w,h);
							break;
						default:
							break;
						}
					break;
			
			case ButtonPress:
				switch(event.xbutton.button){
					
					default:
						break;
				}
				break;

			case MotionNotify:
				break;
			case ConfigureNotify:
				winWidth = event.xconfigure.width;
				winHeight = event.xconfigure.height;
				w = event.xconfigure.width;
				h =event.xconfigure.height; 
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
	glViewport(x,y,(GLsizei)width,(GLsizei)height);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex2f(0.0f,1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex2f(-1.0f,-1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex2f(1.0f,-1.0f);
	glEnd();
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
