#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>

Display *dis; //display points to the X server.
int screen; // screen refers to which screen of the display to use

/**
The display points to X server. The screen refers to which screen
of the display to use. Setting up the connection fromn the X client
to the X server typically involves a line like
setenv Display my.machine.where.ever:0.
the my.machine.where.ever. is tied in with the Display* and the
screen is connected wuth the :0 part of the variable.
**/
Window win; //The Window controls the actual window itself.
GC gc; // GC is the graphic context

void init_x();
void close_x();
void redraw();


void main () {
	XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */	
	char text[255];		/* a char buffer for KeyPress Events */

	init_x();

	/* look for events forever... */
	while(1) {		
		/* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/
		XNextEvent(dis, &event);
	
		if (event.type==Expose && event.xexpose.count==0) {
		/* the window was exposed redraw it! */
			redraw();
		}
		if (event.type==KeyPress&&
		    XLookupString(&event.xkey,text,255,&key,0)==1) {
		/* use the XLookupString routine to convert the invent
		   KeyPress data into regular text.  Weird but necessary...
		*/
			if (text[0]=='q') {
				close_x();
			}
			printf("You pressed the %c key!\n",text[0]);
		}
		if (event.type==ButtonPress) {
		/* tell where the mouse Button was Pressed */
			int x=event.xbutton.x,
			    y=event.xbutton.y;

			strcpy(text,"X is FUN!");
			XSetForeground(dis,gc,rand()%event.xbutton.x%255);
			XDrawString(dis,win,gc,x,y, text, strlen(text));
		}
	}
	return;
}

int sadsadasmain(){
	XEvent event; /* the XEvent declaration */
	KeySym key; /* a dealie-bob to handle keypress events */
	char text[255]; /* a char buffer for keypress events */
	init_x();
	/*look for events forever...*/
	while(1) {
		/*
		get the next event and stuff it into our event variable.
		Note: only event we set the mask for are detected.
		*/
		XNextEvent( dis, &event);
		if (event.type == Expose && event.xexpose.count == 0) {
			/* the window was exposed redraw it! */
			redraw();
		}
		if (event.type == KeyPress &&
			XLookupString(&event.xkey,text,255,&key,0) ==1) {
			/*
			use the XLookUpString routine to convert 
			the event KeyPress data into regular text.

			*/
			 if (text[0] == 'q') {
			 	close_x();
			 }
			 printf("You pressed the %c key!\n", text[0]);

		}
		if (event.type == ButtonPress) {
			//tel where the mouse button was pressed
			int x = event.xbutton.x;
			int y = event.xbutton.y;
			strcpy( text, "X is FUN!!");
			XSetForeground(dis, gc, rand()%event.xbutton.x%255);
			XDrawString(dis, win,gc, x, y, text, strlen(text));

		}
	}
	return 0;
}

void ddsfsdfinit_x() {
/* get the colors black and white (see section for details) */        
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		300, 300, 5,black, white);
	XSetStandardProperties(dis,win,"Howdy","Hi",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
        gc=XCreateGC(dis, win, 0,0);        
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
};


void init_x(){
	/* get the colors black and white */
	unsigned long black, white;
	/* use the information from the environment variable DISPLAY
	to create the X connection; */
	dis = XOpenDisplay((char *)0);
	screen = DefaultScreen(dis);
	black = BlackPixel(dis, screen); /* get color black */
	white = WhitePixel(dis,screen); /* get color white */
	/*
		once the display is initialized create the window.
		This windows will be have 200 pixels acroos and 300 down.
		It will have the foreground white and background black
	*/
	win = XCreateSimpleWindow(dis, DefaultRootWindow(dis),
				0,0,200,300,5,black,white);

	/*
	Here is where some properties of the window can be set.
	the third and fourth items indicate the name which appears at 
	the top of the window and the minimized window respectively
	*/

	XSetStandardProperties(dis,win,"My Window", "HI!!", None,
					NULL, 0, NULL);
	/*
	this routine determines which type of input are allowed int he input.

	*/
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

	/*create the Graphics context */
	gc = XCreateGC(dis, win, 0,0);

	/* here is another routine to set the foreground and background
	colors _currently_ in use in the window.
	*/

	XSetBackground(dis, gc, white);
	XSetForeground(dis,gc,black);

	/* clear the window and bring it on top of the other windows */
	XClearWindow(dis,win);
	XMapRaised(dis,win);


};

void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);
	exit(1);
};	

void redraw() {
	XClearWindow(dis, win);
};

