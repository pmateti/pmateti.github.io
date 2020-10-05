/*-
  worms12.c -- solution to Assignments 1 and 2
  cs241 Spring 96

  File worms12.doc is a detailed commentary/tutorial that goes with
  this file.

  pmateti@cs.wright.edu May 1996 
*/

#include <stdio.h>
#include <conio.h>
#define random(x) 	(rand() % x)
#define min(a, b) 	((a) < (b)? (a) : (b))
#define ESC		'\033' /* the ESCape char */
#define MAXcolors	16

typedef enum {
	N, NE, E, SE, S, SW, W, NW
} DIRECTION;

typedef signed char COORD;     /* coordinate type */

/* dx/dy changes, indexed by DIRECTION */
COORD dxa[] =
{+0, +1, +1, +1, +0, -1, -1, -1};
COORD dya[] =
{-1, -1, +0, +1, +1, +1, +0, -1};

typedef struct {
	COORD row, col;
} POSITION;

typedef struct {
	POSITION p;	       /* where the seg is at */
	char c;		       /* the letter it carries */
} SEGMENT;

typedef enum {
	VEGETARIAN, CANNIBAL, SCISSOR
} WORM_KIND;

typedef struct {
	unsigned char color;
	unsigned char capacity;
	unsigned char foodValue;
} WORM_INFO;

/* info re worm-types; indexed with WORM_KIND */
WORM_INFO worm_info[] =
{
	{GREEN, 3, 3},
	{RED, 4, 5},
	{YELLOW, 5, 4}
};

typedef enum {
	EATEN, DEAD, ALIVE
} LIFE;

#define MAXsegs	 64	       /* max # segments per worm */
typedef struct {
	LIFE status;
	WORM_KIND type;
	DIRECTION direction;   /* its (head's) direction */
	unsigned char nsegs;   /* actual # of segs in this worm */
	SEGMENT body[MAXsegs]; /* body parts */
	unsigned int stomach;
} WORM;

#define lastSeg(wp)	(wp->body + wp->nsegs)

#define MAXworms 30	       /* max # worms in our program */
WORM worm[MAXworms];	       /* vars for the worms */
int nworms;		       /* high water mark of the worm[] */

int xworms[3];		       /* counts of different worms */
#define nVegetarians	*xworms
#define nCannibals	*(xworms + 1)
#define nScissors	*(xworms + 2)
#define	nAllWorms	(nVegetarians + nCannibals + nScissors)
#define	incWorms(t)	*(xworms+t) += 1
#define	decWorms(t)	*(xworms+t) -= 1

#define MAXrow 50
#define MAXcol 80
int screenRows, screenCols;    /* the actual size of 'our' screen */
int bottom;		       /* bottom most line */

typedef struct {	       /* A Square On the Ground */
	char onec;	       /* one character */
	char attr;	       /* its color */
} ASOG;


ASOG passive[MAXrow * MAXcol]; /* for Carrots and Dead Worms */
ASOG screenImage[MAXrow * MAXcol];	/* what gets displayed */
#define	asog(ptr, row, col) (ptr + (row - 1)*screenCols + col - 1)

typedef char *CP;	       /* ptr to a char */
CP say[] =
{			       /* a few legendary programmers */
	"9876543210987654321*",
	"Richard-Stallman*",
	"Donald-Knuth*",
	"C-A-R-Hoare*",
	"Edsger-Dijkstra*"
};

#define Nsay	sizeof(say)/sizeof(CP)	/* how many sayings we have */

int nextTurn[] =
{			       /* array that controls the */
	0, 0, 0, 0,	       /* turns of the worms */
	0, 0, 0, 0,
	1, 1, 1, 7,
	7, 7, 2, 6
};

/* parameters for the 'graphical' (such as it is) display */
int slowness;		       /* slowness number */
int paused = 0;		       /* == 1 iff paused */
int idelay;		       /* delay increment */
int tdelay;		       /* total delay yet to do */


/* Change various user controllable global parameters.  If given 


   < 0, * that param is not to be changed.  */

void setSlowness(int sl, int td, int id, int pa)
{
	if (sl >= 0)
		slowness = sl;
	if (td >= 0)
		tdelay = td;
	if (id >= 0)
		idelay = id;
	if (pa >= 0)
		paused = pa;
}

/* Delay for d msec, and tell us so. */

void doDelay(int d)
{
	gotoxy(1, bottom);
	printf("delaying by %04d msec\r", d);	/* Note the \r */

	delay(d);

	/* erase the above message */
	clreol();
}

void showControlPanel()
{
	gotoxy(1, bottom - 3);

	/*
	 * Long strings can be written as one string after
	 * another. Study the lexical structure of the printf's
	 * arguments.  */
	printf(
		"ESC terminates,""k kill-a-worm,""w create-a-worm,"
		"SPC %s execution"  "\n"
		"s show-worms," "+ reduces-slowness,""- increases-slowness,"
		"f full-speed"  "\n"
		"slowness %04d ""Vegetarians %02d Cannibals %02d "
		"Scissor-heads %02d hi-water-mark %02d"  "\n"
		      ,(paused ? "resumes" : "pauses")
		      ,slowness,nVegetarians, nCannibals, nScissors, nworms
	  );
}

/* pre: s != NULL; post: Prompt the user to type two digits in
   decimal notation.  Return the given number if it is in the
   range 0..nworms-1, ow return -1. */

int getWormNumber(CP s)
{
#define isDigit(x) ('0' <= x && x <= '9')

	int a, b, wn = -1;

	gotoxy(1, bottom);
	printf("give the number of the worm to be %s"
	       "(using two decimal digits):", s);

	a = getch();
	b = getch();
	if (isDigit(a) && isDigit(b)) {
		wn = (a - '0') * 10 + b - '0';
		if (wn > nworms)
			wn = -1;
	}
	return wn;
}


void sprinkleCarrots()
{
	ASOG *p = asog(passive, screenRows + 1, 1);

	while (p > passive) {
		p--;
		p->attr = BROWN;
		p->onec = '.';
	}
}

/* Draw the segment bp of the worm wp on the ASOG f[]. */

void drawSegment(WORM * wp, SEGMENT * bp, ASOG * f)
{
	POSITION p = bp->p;
	ASOG *g = asog(f, p.row, p.col);

	g->attr = worm_info[wp->type].color;
	g->onec = bp->c;
}

/* Draw a single worm.  pre: wp != NULL.  post: It is drawn on
   passive[] if it is dead.  If alive, it is drawn on
   screenImage.  If eaten, not drawn.  */

void drawAWorm(WORM * wp)
{
	if (wp->status != EATEN) {
		ASOG *f = (wp->status == ALIVE ? screenImage : passive);
		SEGMENT *bp, *lp = lastSeg(wp);
		for (bp = wp->body + 1; bp <= lp; bp++)
			drawSegment(wp, bp, f);
	}
}

/* Draw all the worms */

void drawWorms()
{
	WORM *wp, *lastWorm = worm + nworms;

	for (wp = worm; wp < lastWorm; wp++)
		drawAWorm(wp);
}


/* pre: none; post: Show on the CRT, the carrots, the dead
   worms, and the current positions of one/all worms that are
   alive.  screenImage as above.  globals: passive[] read-only.
   */

void showWormsAndCarrots(WORM * wp)
{
	ASOG *sp = screenImage, *se = asog(screenImage, screenRows + 1, 1);
	ASOG *pp = passive;

	/* copy the Carrots */
	while (sp < se)
		*sp++ = *pp++;

	if (wp == NULL)
		drawWorms();
	else
		drawAWorm(wp);

	puttext(1, 1, screenCols, screenRows, screenImage);	/* Turbo-C

								 */
}

/* Set the row# or col# to be within the range of
   1..screenRows/Cols. Illustrates call-by-ref parameters.  int
   rowf == 1, if row, ow col.  */

void setRowCol(COORD * k, int rowf)
{
	int mx = (rowf ? screenRows : screenCols);
	if (*k < 1)
		*k = 1;
	if (*k > mx)
		*k = mx - 1;
}

/* pre: none; post: Compute the next position if the worm's head 
   moves in the direction dir, and the current position is p.  */

POSITION nextPosition(DIRECTION dir, POSITION p)
{
	p.row += *(dya + dir);
	p.col += *(dxa + dir);

	setRowCol(&p.row, 1);
	setRowCol(&p.col, 0);
	return p;
}


/* pre: wp->status == ALIVE; post: Make the worm wp crawl by one
   step. Just crawl.  No eating.  */

void crawl(WORM * wp)
{
	SEGMENT *bp, *lp = lastSeg(wp);

	for (bp = wp->body; bp < lp; bp++)	/* < not <= */
		bp->p = (bp + 1)->p;

	wp->direction = (wp->direction + nextTurn[random(16)]) % 8;
	lp->p = nextPosition(wp->direction, lp->p);
}


/* pre: wp != NULL; post: Return 1 if worm wp is hungry;
   otherwise return 0.  It is hungry if its tummy is at least
   25% empty.  */

int isHungry(WORM * wp)
{
	int m = wp->stomach;
	int n = wp->nsegs * worm_info[wp->type].capacity;

	return (wp->status == ALIVE && 4 * m < 3 * n);
}


POSITION posOfHead(WORM * wp)
{
	return lastSeg(wp)->p;
}

/* pre: wp != NULL */

void gotEaten(WORM * wp)
{
	if (wp->status == ALIVE) {
		wp->status = EATEN;
		decWorms(wp->type);
	}
}

/* pre: wp->status == ALIVE; post: if stomach is 0 or less, mark 

   it dead, and send its body to the cemetary for burial. */

void checkStomach(WORM * wp)
{
	if (wp->stomach <= 0) {
		wp->status = DEAD;
		decWorms(wp->type);
		drawAWorm(wp); /* mv the body to passive */
	}
}

/* pre: wp->status == ALIVE; post: Eat a carrot, if available. */

void eatACarrot(WORM * wp)
{
	POSITION p = posOfHead(wp);
	ASOG *s = asog(passive, p.row, p.col);

	if ('.' == s->onec) {
		wp->stomach += 2;
		s->onec = ' ';
	}
}

/* pre: wp != NULL; post: Check if any segment of worm wp is at
   the position po. Return this segment's number.  Note that
   body[0] is just an eraser-blank, not really a part of the
   worm. */

int isAt(WORM * wp, POSITION po)
{
	SEGMENT *bp = lastSeg(wp);
	int sn;

	for (sn = wp->nsegs; sn > 0; sn--) {
		if ((bp->p.row == po.row) && (bp->p.col == po.col))
			break;
		bp--;
	}

	return sn;
}


/* The following two vars should be 'out' parameters (var
   params), but for ease of understanding, let us declare these
   as globals. */

WORM *victimWormp;
int victimSegNum;

/* pre: me != NULL; post: Find a worm that is on the same square 
   as "my" head.  victimSegNum > 0 => victimWormp != NULL and
   victimWormp's victimSegNum segment is at the same square as
   the head of me.  */

void setVictimWorm(WORM * me)
{
	POSITION p = posOfHead(me);
	WORM *lastWormp = worm + nworms, *wp;

	victimWormp = NULL;
	victimSegNum = 0;
	for (wp = worm; wp < lastWormp; wp++) {
		if (wp != me && wp->status == ALIVE) {
			victimSegNum = isAt(wp, p);
			if (victimSegNum > 0) {
				victimWormp = wp;
				return;		/* found the victim */
			}
		}
	}
}

/* pre: 0 <= nworms <= MAXworms; post: We have a new worm about
   to  join.  Find a slot for it in our worm[] array, and return 

   a ptr to  it.  Return NULL, if we do not succeed in finding a 

   slot.  */

WORM *findSlot()
{
	WORM *wp, *zp = worm + nworms;

	/* see if we have vacant slots */
	if (nworms < MAXworms) {
		nworms++;
		return zp;
	}
	/* see if there are any dead/eaten worms */
	for (wp = worm; wp < zp; wp++)
		if (wp->status != ALIVE)
			return wp;
	return NULL;
}

/* pre: vp != NULL && 0 < vsn <= vp->nsegs; post: Copy the body
   segments: old body[vsn+1..end] should become new
   body[1..new-length]; body[0] remains as the eraser-blank */

void shiftBodyDown(WORM * vp, int vsn)
{
	int tsegs = vp->nsegs;
	SEGMENT *dp = vp->body + 1;	/* destination */
	SEGMENT *sp = vp->body + vsn + 1;	/* source */
	SEGMENT *lp = lastSeg(vp);

	while (sp <= lp)
		*dp++ = *sp++;
	vp->nsegs -= vsn;
	vp->stomach = vp->stomach / tsegs * vp->nsegs;
	checkStomach(vp);
}

/* pre: vp != NULL && 0 < vsn <= vp->nsegs; post: A scissor-head 

   or cannibal hit the victim at segment number vsn.  Split the
   victim into two.  The first one with vp->body[1..vsn-1]  and
   the second one with vp->body[vsn+1..vp->nsegs] as its new
   body.  */

WORM *splitTheVictim(WORM * vp, int vsn)
{
	WORM *wp = findSlot();
	int tsegs = vp->nsegs;

	if (wp == NULL)
		/* could not find a slot; so return vp as-is */
		return vp;

	incWorms(vp->type);

	/* the bottom-half */
	*wp = *vp;	       /* copy status, dir, body, etc. */
	wp->nsegs = vsn - 1;
	wp->stomach = vp->stomach / tsegs * wp->nsegs;
	checkStomach(wp);

	/* the top-half: cut the original victim to size */
	shiftBodyDown(vp, vsn);

	return wp;
}

/* pre: isHungry(wp) && wp->status == ALIVE; post: Eat whatever
   you find at the wp's head.  If wp is a cannibal or
   scissor-head it will also eat a carrot if available. Update 
   the stomach contents.  */

void eat(WORM * wp)
{
	WORM *zp;

	if (wp->type != VEGETARIAN) {
		setVictimWorm(wp);
		if (victimWormp != NULL) {
			/* eat the segment ahead */
			wp->stomach += worm_info[victimWormp->type].foodValue;
			/* slice the victim into two */
			zp = splitTheVictim(victimWormp, victimSegNum);
			if (wp->type == CANNIBAL && zp->status == ALIVE) {
				wp->stomach += zp->nsegs
				  * worm_info[zp->type].foodValue;
				gotEaten(zp);
			}
		}
	}
	eatACarrot(wp);
}

void lifeCycle(WORM * wp)
{
	crawl(wp);
	wp->stomach--;
	if (isHungry(wp))
		eat(wp);
	checkStomach(wp);
}

/* pre: s != NULL; post: Create the next worm so that it is just 

   long enough to carry the phrase s[].  It is going to crawl
   out of a random hole. */

void createWorm(WORM_KIND type, CP s)
{
	int n = min(1 + strlen(s), MAXsegs - 1);
	WORM *wp = findSlot();
	SEGMENT *bp, *lp;
	POSITION p;

	if (wp == NULL)
		return;	       /* no room for a new worm */

	incWorms(type);

	wp->status = ALIVE;
	wp->direction = N;
	wp->type = type;
	wp->stomach = n * worm_info[type].capacity;
	wp->nsegs = n;

	/* birth place of this worm */
	p.row = 1 + random(screenRows);
	p.col = 1 + random(screenCols);

	bp = wp->body;
	lp = lastSeg(wp);
	bp->c = ' ';	       /* works as an "eraser" */
	bp->p = p;
	for (bp++; bp <= lp; bp++) {
		bp->c = *s++;  /* store the phrase s[] */
		bp->p = p;
	}
}

void killAWorm()
{
	int wn = getWormNumber("killed");
	if (wn >= 0)
		gotEaten(worm + wn);
}

void printWormData(int wn)
{
	WORM *wp = worm + wn;
	gotoxy(1, bottom);
	clreol();
	printf("worm#%02d type %d status %d nsegs %d stomach %d",
		wn, wp->type, wp->status, wp->nsegs, wp->stomach);
}


void showWormsOneAtATime()
{
	int i;

	for (i = 0; i < nworms; i++) {
		printWormData(i);
		showWormsAndCarrots(worm + i);
		getch();
	}
}


/* pre: none; post: User can control the speed, etc. via this
   procedure.  See the printf() of showControlPanel for a
   description of which key controls what.  The total delay
   required, tdelay, is  doled out in increments of idelay so
   that keyboard interaction is more responsive.  */

int userControl()
{
	char c;

	tdelay = slowness;
	showControlPanel();
	do {
		idelay = min(tdelay, min(slowness, 10));
		c = (kbhit()? getch() : '\0');	/* conditional exp */
		switch (c) {
			case '+':
				setSlowness(slowness - 100, 0, 0, 0);
				break;
			case '-':
				setSlowness(slowness + 100, -1, -1, 0);
				break;
			case 'f':
				setSlowness(0, 0, 0, 0);
				break;
			case 'k':
				killAWorm();
				break;
			case 's':
				showWormsOneAtATime();
				break;
			case 'w':
				createWorm(random(3), say[random(Nsay)]);
				break;
			case '\0':
				if (paused)
					setSlowness(-1, 100, 50, -1);
				break;
			case ' ':
				setSlowness(-1, 0, 0, paused ^ 1);
				showControlPanel();
				break;
			case ESC:
				return ESC;
		}
		if (idelay > 0)
			doDelay(idelay);
		tdelay -= idelay;
	} while (tdelay > 0);
	return '\0';
}

/* where the story begins ... */

int main(int argc)
{
	int i;
	struct text_info ti;

	textmode(C4350);       /* Turbo-C: 43-or-50x80 text */
	gettextinfo(&ti);      /* Turbo-C */
	bottom = ti.screenheight;
	screenRows = bottom - 4;
	screenCols = ti.screenwidth;

	do {
		clrscr();      /* start with a clean slate */
		slowness = 100 * (argc - 1);	/* initial slowness */
		srand(time());

		nworms = nVegetarians = nCannibals = nScissors = 0;
		for (i = random(8) + 3; i > 0; i--)
			createWorm(random(3), *(say + random(Nsay)));

		sprinkleCarrots();
		do {
			WORM *wp;

			/* nworms may ++ in each lifeCycle */
			for (wp = worm; wp < worm + nworms; wp++)
				if (wp->status == ALIVE)
					lifeCycle(wp);
			showWormsAndCarrots(NULL);
		} while (userControl() != ESC && nAllWorms > 0);

		printf("press ESC to terminate, or any other key to re-run");
	} while (getch() != ESC);

	textmode(LASTMODE);
	return 0;
}

/* -eof- */

