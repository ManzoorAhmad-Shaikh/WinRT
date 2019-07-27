#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>
#include<math.h>

//opengl
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#define NUM_POINTS 5000
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
float angle = 0.0f;
GLXContext gGLXContext;

float orange[3] = { 1.0f,153.0f / 255.0f,51.0f / 255.0f };
float green[3] = { 19.0f / 255.0f,136.0f / 255.0f,8.0f / 255.0f };
float pr = 186.0f / 255.0f, pg = 226.0f / 255.0f, pb = 238.0f / 255.0f;
int animationDone = 0, animationDoneFlag = 0;
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
		//update();
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
		r = r + 0.00003f;
		g = g + 0.00003f;
		b = b + 0.0000f;
	}
	else {
		r = orange[0];
		g = orange[1];
		b = orange[2];
	}
	if ((r1 < green[0] && g1 < green[1] && b1 < green[2])) {
		r1 = r1 + 0.00003f;
		g1 = g1 + 0.00003f;
		b1 = b1 + 0.00003f;
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
	glRotatef(-angle, 0.0f, 0.0f, 1.0f);
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
	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.1f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.05f, 0.2f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, 0.2f);
	glEnd();
	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);
	glEnd();

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);
	glEnd();

	glTranslatef(x3, y3, -3.0f);
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

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
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

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
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

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glLineWidth(7.0f);
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

	

}

void PlaneTwo(float x3, float y3, float angle) {
	glLoadIdentity();

	glTranslatef(x3, y3, -3.0f);
	glRotatef(-angle, 0.0f, 0.0f, 1.0f);
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
	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.1f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.05f, -0.2f);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.05f, -0.2f);
	glEnd();
	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);
	glEnd();

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(pr, pg, pb);
	glVertex2f(-0.15f, 0.0f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, 0.05f);
	glColor3f(pr, pg, pb);
	glVertex2f(0.0f, -0.05f);
	glEnd();

	glTranslatef(x3, y3, -3.0f);
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

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
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

	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
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


	glLoadIdentity();
	glTranslatef(x3, y3, -3.0f);
	glLineWidth(7.0f);
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

	

}
void DrawLine(float x5, float x2, float x3, float y, float y1) {
	static float r = orange[0], g = orange[1], b = orange[2], r1 = green[0], g1 = green[1], b1 = green[2], rw = 1.0f, gw = 1.0f, bw = 1.0f;
	static float x = -0.7f, x1 = -0.7f;
	static int count = 0;
	if (x1 > 1.0f) {
		//x = x + 0.0001f;
		r = r - 0.0001f;
		g = g - 0.0001f;
		b = b - 0.0001f;
		r1 = r1 - 0.0001f;
		g1 = g1 - 0.0001f;
		b1 = b1 - 0.0001f;
		rw = rw - 0.0001f;
		gw = gw - 0.0001f;
		bw = bw - 0.0001f;
	}
	/*if(x >= 2.0f){
		I(0.0f);
		A(0.0f);
		N(0.0f);
		II(0.0f);
		D();
	}*/
	x1 = x1 + 0.0001f;
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
		x = x + 0.0001f;

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

void display(void){
	float angle, h, k, r = 1.0f;
	static float x = -2.0f, y = 2.0f, x1 = 2.0f, y1 = -2.0f;
	static float x3 = 0.0f, y3 = 0.0f, x4 = 0.0f, y4 = 0.0f, x5 = -2.0f, x6 = 0.0f, y6 = 0.0f, x7 = 0.0f, y7 = 0.0f;
	static int myCount = 0, tot = 0, flag = 0, flag1 = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	if (x < 0.0f) {
		x = x + 0.001f;
	}
	else {
		x = 0.0f;
		myCount = 1;
	}
	I(x);
	glLoadIdentity();

	if (x == 0.0f) {
		if (x1 > 0.0f) {
			x1 = x1 - 0.001f;
		}
		else {
			x1 = 0.0f;
		}
		A(x1);
		if (x1 == 0.0f) {
			if (y > 0.0f) {
				y = y - 0.001f;
			}
			else {
				y = 0.0f;
			}
			N(y);

			if (y == 0.0f) {
				if (y1 < 0.0f) {
					y1 = y1 + 0.001f;
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
	

	if (animationDone == 1) {

		if (tot >= NUM_POINTS) {
			if (y3 < 0.0f) {
				x3 = x3 + 0.0001f;

				y3 = y3 - 0.0001f;
			}
			else {
				x3 = x3 + 0.0001f;
				y3 = 0.0f;
			}
			if (y4 > 0.0f) {
				x4 = x4 - 0.0001f;
				y4 = y3 + 0.0001f;
			}
			else {
				x4 = x4 + 0.00001f;
				y4 = 0.0f;
			}
		}
		x5 = x5 + 0.0002f;
		if (tot <= NUM_POINTS) {
			if (flag == 0) {
				h = -1.0f;
				k = 1.0f;

				angle = (2.0f*(M_PI / 4)*tot) / NUM_POINTS;
				x3 = h + r * cos(angle - M_PI);
				y3 = k + r * sin(angle - M_PI);
				PlaneOne(x3, y3, angle);
				h = -1.0f;
				k = -1.0f;
				angle = (2.0f*(-M_PI)*tot) / NUM_POINTS;
				x4 = h - r * cos((angle + M_PI / 4));
				y4 = k - r * sin((angle + M_PI / 4));
				PlaneTwo(x3, -y3, angle);
				PlaneCentre(x5);
				//if()
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
					PlaneCentre(x5);
					tot++;
				}
				//Sleep(10);
				PlaneOneTwo(x6, y6);
				DrawLine(x5, x, x1, y, y1);
				x6 = x6 + 0.0001f;
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
	
	glXSwapBuffers(gpDisplay,gWindow);
}

void update(void){
	angle = angle +0.5f;
	if(angle >=360.0f){
		angle = 0.0f;
	}

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
