/*
 * xwindow.c
 */


#include <stdio.h>
#include <X11/Xlib.h>

/* Following typedef is compatible with SR's linecoords rec */
typedef struct {
	int             x1, y1, x2, y2;
}               linecoords;

typedef struct {
	Display        *display;
	Window          window;
	GC              gc;
}               xwindow;


static xwindow  xw;


/*
 * Open an X window on display screen whose name is given in dispnm[]; the
 * title of the window will be wintitle[].  The private var xw of this module
 * gets initialized as a result.  The window so created will appear as soon
 * as trackpointer() is called.  dispnm[] is of the form "machinename:0.0",
 * wintitle[] is any arbitrary C string of non-control chars.
 */

int
openxwindow(char dispnm[], char wintitle[])
{
	Display        *d = XOpenDisplay(dispnm);	/* connect to X */
	int             screen;
	int             dw, dh;
	XGCValues       values;

	if (d == NULL) {
		/* "can't connect to X server; was dispnm bad? */
		return -1;
	}
	xw.display = d;

	/* get screen size from display structure macro */
	screen = DefaultScreen(d);
	dw = DisplayWidth(d, screen);
	dh = DisplayHeight(d, screen);

	/* create opaque window */
	xw.window = XCreateSimpleWindow
		(d, RootWindow(d, screen),
		 dw / 3, dh / 3, 350, dh / 4, 4,
		 BlackPixel(d, screen),
		 WhitePixel(d, screen));

	/* set window/icon titles */
	XSetStandardProperties
		(d, xw.window, wintitle, "Doodle", None, 0, 0, 0);

	/* Select event types wanted */
	XSelectInput(d, xw.window, 0x00FFFFFF);

	/* Display window */
	XMapWindow(d, xw.window);

	/* Create Graphics Context */
	xw.gc = XCreateGC(d, xw.window, 0L, &values);

	/* Set Foreground color to black */
	XSetForeground(d, xw.gc, BlackPixel(d, screen));

	return 0;
}


/*
 * Close the X window opened by openxwindow().
 */

int
closexwindow(void)
{
	return XCloseDisplay(xw.display);
}

/*
 * Draw a straight line from (coord.x1, coord.y1) to (coord.x2, coord.y2).
 */

void
drawline(int x1, int y1, int x2, int y2)
{
	XDrawLine(xw.display, xw.window, xw.gc,
		  x1, y1, x2, y2);
}



/*
 * "Track" the mouse ptr of the X window server to which we established
 * connection via openxwindow().  The routine does *not* draw an individual
 * line (unless "exposed"), *nor* does it return until the mouseptr (a)
 * enters our window from outside, (b) leaves our window, or (c) mouse ptr is
 * inside the window, and one of the three mouse buttons is pressed.  Events
 * (a) and (b) return 0, event (c) returns the number of the button 1..3.
 * The routine remembers upto 2000 points, which is a hack.  When our window
 * gets (partially) hidden, and later revealed again (i.e., "exposed"), the
 * routine draws the lines it had (subject to this limit).  Ofcourse, the
 * routine assumes you properly opened a window via openxwindow().
 */

int
trackpointer(linecoords * newseg)
{
	XEvent          report;
	Window          rootw, childw;
	int             rootx, rooty, wx, wy;
	unsigned int    keys_buttons;
	static XPoint   points[2000] = {0, 0};
	static int      index = 0, npts;


     	if (!XCheckWindowEvent(xw.display, xw.window, 0xFFFFFFFFL, &report))
		return -1;

	switch (report.type) {
	case ButtonPress:
		if (report.xbutton.button == 3)
			return 3;

		/* now get current position */
		XQueryPointer
			(xw.display, report.xmotion.window,
			 &rootw, &childw, &rootx, &rooty,
			 &wx, &wy, &keys_buttons);

		newseg->x1 = points[index].x;
		newseg->y1 = points[index].y;

		index++;
		if (index >= 2000)
			index = 0;
		else
			npts = index;
		newseg->x2 = points[index].x = wx;
		newseg->y2 = points[index].y = wy;
		return report.xbutton.button;

	case Expose:
		XDrawLines
			(xw.display, xw.window, xw.gc,
			 points, npts, CoordModeOrigin);
		return 4;

	case EnterNotify:
		/*XSelectInput(xw.display, xw.window,
			  ExposureMask | LeaveWindowMask | ButtonPressMask);*/
		return 5;

	case LeaveNotify:
		/*XSelectInput(xw.display, xw.window, EnterWindowMask | 
ExposureMask);*/
		return 6;
	}
	return 0;
}



#ifdef  MAIN

/*
 * Invoke the resulting a.out with two arguments: (1) name of the display
 * screen (e.g., "diamond:0.0"), and (2) a name that shows up in the
 * title-bar of the window (e.g., "hello"). Also try illegal args.
 */

void
main(int argc, char *argv[], char *envp)
{
	linecoords      seg = {0, 0, 100, 100};
	int             b;

	printf("openxwindow(\"%s\", \"%s\") returned %d\n",
	       argv[1], argv[2], openxwindow(argv[1], argv[2]));
	printf("press Return to enter trackpointer()");
	getchar();

	do {
		b = trackpointer(&seg);
		printf("line from (%2d, %2d) to (%2d, %2d) button %d\n",
		       seg.x1, seg.y1, seg.x2, seg.y2, b);
		drawline(seg.x1, seg.y1, seg.x2, seg.y2, b);
	} while (b != 3);
	printf("button %d pressed; press Return to terminate", b);
	getchar();
	closexwindow();
}
#endif




/* -eof- */
 


