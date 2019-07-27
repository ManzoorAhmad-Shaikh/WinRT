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
struct MyLights{
	GLfloat Ambient[4];
	GLfloat Diffuse[4];
	GLfloat Specular[4];
	GLfloat Position[4];
};

float year = 0, day = 0,moon = 0;
float moonColor[3] = {244.0f/255.0f,244.0f/255.0f,244.0f/255.0f};
GLUquadric *quadric;

struct MyLights light[3] = {{{0.0f,0.0f,0.0f,1.0f},{1.0f,0.0f,0.0f,1.0f},{1.0f,0.0f,0.0f,1.0f},{0.0f,0.0f,0.0f,1.0f}},
							{{0.0f,0.0f,0.0f,1.0f},{0.0f,1.0f,0.0f,1.0f},{0.0f,1.0f,0.0f,1.0f},{0.0f,0.0f,0.0f,1.0f}},
							{{0.0f,0.0f,0.0f,1.0f},{0.0f,0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f,1.0f},{0.0f,0.0f,0.0f,1.0f}}};
GLfloat LightAmbientZero [] = {0.0f,0.0f,0.0f,1.0f};
GLfloat LightDiffuseZero [] = {1.0f,0.0f,0.0f,1.0f};
GLfloat LightSpecularZero [] = {1.0f,0.0f,0.0f,1.0f};
GLfloat LightPositionZero [] = {0.0f,0.0f,0.0f,1.0f};

GLfloat LightAmbientOne [] = {0.0f,0.0f,0.0f,1.0f};
GLfloat LightDiffuseOne [] = {0.0f,1.0f,0.0f,1.0f};
GLfloat LightSpecularOne [] = {0.0f,1.0f,0.0f,1.0f};
GLfloat LightPositionOne [] = {0.0f,0.0f,0.0f,1.0f};

GLfloat LightAmbientTwo [] = {0.0f,0.0f,0.0f,1.0f};
GLfloat LightDiffuseTwo [] = {0.0f,0.0f,1.0f,1.0f};
GLfloat LightSpecularTwo [] = {0.0f,0.0f,1.0f,1.0f};
GLfloat LightPositionTwo [] = {0.0f,0.0f,0.0f,1.0f};


GLfloat MaterialAmbient [] = {0.0f,0.0f,0.0f,1.0f};
GLfloat MaterialDiffuse [] = {1.0f,1.0f,1.0f,1.0f};
GLfloat MaterialSpecular [] = {1.0f,1.0f,1.0f,1.0f};
GLfloat MaterialShininess[] = {128.0f};
//light 0
/*light[0].Ambient[0]=0.0f;
light[0].Ambient[1]=0.0f;
light[0].Ambient[2]=0.0f;
light[0].Ambient[3]=1.0f;
light[0].Diffuse[0]=1.0f;
light[0].Diffuse[1]=0.0f;
light[0].Diffuse[2]=0.0f;
light[0].Diffuse[3]=1.0f;
light[0].Specular[0]=1.0f;
light[0].Specular[1]=0.0f;
light[0].Specular[2]=0.0f;
light[0].Specular[3]=1.0f;
light[0].Position[0]=0.0f;
light[0].Position[1]=0.0f;
light[0].Position[2]=0.0f;
light[0].Position[3]=1.0f;
//light 1
light[1].Ambient[0]=0.0f;
light[1].Ambient[1]=0.0f;
light[1].Ambient[2]=0.0f;
light[1].Ambient[3]=1.0f;
light[1].Diffuse[0]=0.0f;
light[1].Diffuse[1]=1.0f;
light[1].Diffuse[2]=0.0f;
light[1].Diffuse[3]=1.0f;
light[1].Specular[0]=0.0f;
light[1].Specular[1]=1.0f;
light[1].Specular[2]=0.0f;
light[1].Specular[3]=1.0f;
light[1].Position[0]=0.0f;
light[1].Position[1]=0.0f;
light[1].Position[2]=0.0f;
light[1].Position[3]=1.0f;
//light2
light[2].Ambient[0]=0.0f;
light[2].Ambient[1]=0.0f;
light[2].Ambient[2]=0.0f;
light[2].Ambient[3]=1.0f;
light[2].Diffuse[0]=0.0f;
light[2].Diffuse[1]=0.0f;
light[2].Diffuse[2]=1.0f;
light[2].Diffuse[3]=1.0f;
light[2].Specular[0]=0.0f;
light[2].Specular[1]=0.0f;
light[2].Specular[2]=1.0f;
light[2].Specular[3]=1.0f;
light[2].Position[0]=0.0f;
light[2].Position[1]=0.0f;
light[2].Position[2]=0.0f;
light[2].Position[3]=1.0f;*/
GLfloat LightAngleZero = 0.0f,LightAngleOne = 0.0f,LightAngleTwo = 0.0f;


bool bFullscreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpxVisualInfo = NULL;
Colormap gColormap;
Window gWindow;
int giWindowWidth = 800;
int giWindowHeight = 600;
float angleRotate = 0.0f;
GLXContext gGLXContext;

bool bLight = false;
//Lights
//entry -point function
int main(void){
	//function declaration

	void CreateWindow(void);
	void ToggleFullscreen(void);
	void uninitialize();
	void update(void);
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
		update();
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
						GLX_DEPTH_SIZE,24,
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
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	//Light
	
	glLightfv(GL_LIGHT0,GL_AMBIENT,light[0].Ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light[0].Diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light[0].Specular);
	
	glLightfv(GL_LIGHT1,GL_AMBIENT,light[1].Ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light[1].Diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light[1].Specular);
	
	glLightfv(GL_LIGHT2,GL_AMBIENT,light[2].Ambient);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,light[2].Diffuse);
	glLightfv(GL_LIGHT2,GL_SPECULAR,light[2].Specular);
	//glLightfv(GL_LIGHT0,GL_POSITION,LightPosition);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialAmbient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialDiffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialSpecular);
	glMaterialfv(GL_FRONT,GL_SHININESS,MaterialShininess);
	
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

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f,0.0f,3.0f,
				0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f);
	
	glPushMatrix();
	//Light 0
	
	glPushMatrix();
	glRotatef(LightAngleZero,1.0f,0.0f,0.0f);
	light[0].Position[1] = LightAngleZero;
	glLightfv(GL_LIGHT0,GL_POSITION,light[0].Position);
	glPopMatrix();
	
	//Light 1
	
	glPushMatrix();
	glRotatef(LightAngleOne,0.0f,1.0f,0.0f);
	light[1].Position[0] = LightAngleOne;
	glLightfv(GL_LIGHT1,GL_POSITION,light[1].Position);
	glPopMatrix();
	
	//Light 2
	
	glPushMatrix();
	glRotatef(LightAngleTwo,0.0f,0.0f,1.0f);
	light[2].Position[0] = LightAngleTwo;
	glLightfv(GL_LIGHT2,GL_POSITION,light[2].Position);
	glPopMatrix();
	//Sun
	//glRotatef(90.0f,1.0f,0.0f,0.0f);
	//glTranslatef(0.0f,0.0f,-0.70f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	quadric = gluNewQuadric();
	
	//glColor3f(1.0f,1.0f,0.0f);
	gluSphere(quadric,0.5f,30,30);

	
	glXSwapBuffers(gpDisplay,gWindow);
}

void update(void){
	LightAngleZero = LightAngleZero + 0.2f;
	if(LightAngleZero >=360.0f)
		LightAngleZero = 0.0f;
	LightAngleOne = LightAngleOne + 0.2f;
	if(LightAngleOne >=360.0f)
		LightAngleOne = 0.0f;
	LightAngleTwo = LightAngleTwo + 0.2f;
	if(LightAngleTwo >=360.0f)
		LightAngleTwo = 0.0f;

}
void uninitialize(void){
	if(quadric)
		gluDeleteQuadric(quadric);
	quadric = NULL;
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
