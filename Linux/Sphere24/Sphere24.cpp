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
float angleRotate = 0.0f;
GLXContext gGLXContext;

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

void display(void){
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
	
	glXSwapBuffers(gpDisplay,gWindow);
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


void uninitialize(void){
	for(int i=0;i<24;i++){
		if(quadric[i])
			gluDeleteQuadric(quadric[i]);
		quadric[i] = NULL;
	}
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