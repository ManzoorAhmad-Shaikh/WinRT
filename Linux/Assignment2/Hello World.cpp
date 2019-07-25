#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>

//namespaces
using namespace std;

//global variables
bool bFullscreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpxVisualInfo = NULL;
//XVisualInfo gxVisualInfo;
Colormap gColormap;
Window gWindow;
int giWindowWidth = 800;
int giWindowHeight = 600;

//entry -point function
int main(void){
	//function declaration

	void CreateWindow(void);
	void ToggleFullscreen(void);
	void uninitialize();

	//variable declaration
	int winWidth = giWindowHeight;
	int winHeight = giWindowHeight;

	//for hello world

	static XFontStruct *pXFontStruct = NULL;
	static GC gc;
	XGCValues gcValues;
	XColor textColor;
	char str[255] = "Hellow World !!!";
	int strLength = 0,strWidth = 0,fontHeight = 0;
	char keys[26];

	//code
	CreateWindow();

	//Message Loop
	XEvent event;
	KeySym keysym;

	while(1){
		XNextEvent(gpDisplay,&event);
		switch(event.type){
			case MapNotify:
				pXFontStruct = XLoadQueryFont(gpDisplay,"fixed");
				break;
			case KeyPress:
				keysym = XkbKeycodeToKeysym(gpDisplay,event.xkey.keycode,0,0);
				switch(keysym){
				
					case XK_Escape:
						uninitialize();
						exit(0);
					/*case XK_F:
					case XK_f:
						if(bFullscreen == false){
							ToggleFullscreen();
							bFullscreen = true;
						}
						else{
							ToggleFullscreen();
							bFullscreen = false;
						}
						break;
					*/
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
				break;

			case Expose:
			gc = XCreateGC(gpDisplay,gWindow,0,&gcValues);
			XSetFont(gpDisplay,gc,pXFontStruct->fid);
			XAllocNamedColor(gpDisplay,gColormap,"green",&textColor,&textColor);
			XSetForeground(gpDisplay,gc,textColor.pixel);
			strLength = strlen(str);
			strWidth = XTextWidth(pXFontStruct,str,strLength);
			fontHeight = pXFontStruct->ascent + pXFontStruct->descent;
			XDrawString(gpDisplay,gWindow,gc,(winWidth/2) - (strWidth/2), (winHeight/2) - (fontHeight/2),str,strLength);
				break;
			case DestroyNotify:
				break;
			case 33:
			XFreeGC(gpDisplay,gc);
			XUnloadFont(gpDisplay,pXFontStruct->fid);
				uninitialize();
				exit(0);
			default:
				break;
			}
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

	//code
	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL){
	printf("ERROR : Unable to Open X Display. \n Exitting Now...\n");
	uninitialize();
	exit(1);
	}

	defaultScreen = XDefaultScreen(gpDisplay);
	defaultDepth = DefaultDepth(gpDisplay,defaultScreen);

	gpxVisualInfo = (XVisualInfo *)malloc(sizeof(XVisualInfo));
	if(gpxVisualInfo == NULL){
	printf("ERROR : Unable to allocate memory for Visual Info.\n Exitting now.\n");
	uninitialize();
	exit(1);
	}
	XMatchVisualInfo(gpDisplay,defaultScreen,defaultDepth,TrueColor,gpxVisualInfo);

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

void uninitialize(void){

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
