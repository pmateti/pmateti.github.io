/*
 * ws.c -- working-string module
 * 
 * copyright (c) 1992 prabhaker mateti
 * 
 * This module implements an abstraction of string variables that
 * can grow to arbitrary size, the only limitation being a
 * malloc() failure.  To provide greater flexibilty in its use,
 * the abstraction provided is actually a catenation of strings,
 * with the NUL char separating them.
 *
 * Expected to be highly portable across all ANSI C platforms.
 */


/*
 * This file is rather hastily extracted from another.  It is
 * prepared for use as a test input file for the CEG 460/660
 * project.  Study it also as a decent set of examples of pre
 * post conditions, even though many are weaker than they ought
 * to be.
 */


#define	NULL	((void *) 0L)
#define	reg	register

#define	gchar	char		/* with some cc, make it unsigned
				 * char */
#define	uint	unsigned int

/* uses */
void *gmalloc(unsigned int);	/* can be same as malloc(uint) */
int gfree(void *);		/* must not bomb for gfree(NULL) */

static gchar ES[] = {'\000', '\000'};

#define	Iwssz	100		/* size increment for ws */
typedef struct {
	uint sz;		/* size of malloc-d ->ps area */
	uint nc;		/* #chars used up so far */
	uint ns;		/* #stringlets in ws */
	gchar *ps;		/* ptr to malloc-d area of size
				 * sz */
} WS;


#ifdef DEBUG
/*
 * Printf the ws.  Here is an example of what your "print"
 * options could produce ;-)
 */

void 
showws(WS * ws)
{
	reg gchar *p;
	reg int n;

	if (ws == NULL) {
		printf("showws(NULL)\n");
		return;
	}
	printf("ws=0x%08lx ws->sz=%d ws->nc=%d ws->ns=%d ws->ps=0x%08lx\n",
	       ws, ws->sz, ws->nc, ws->ns, ws->ps);
	for (n = 0, p = ws->ps; n < ws->ns; n++, p += strlen(p) + 1) {
		printf("%2d |%s|\n", n, p);
	}
}

#endif



#ifdef	ASSERT
/*
 * Compute the number of ascii-NUL chars in p[0..n-1].
 */

uint nnulc(gchar * p, uint n)
{
	reg uint k = 0;
	if (p) {
		reg gchar *q = p + n;
		while (--q >= p)
			if (*q == '\000')
				k++;
	}
	return k;
}

#define	FALSE	0
#define	TRUE	!0
#define	COP_OUT	TRUE

#define invWS(ws) (ws == NULL || (ws->nc <= ws->sz && ws->ps != NULL && \
	ws->ns + 1 == nnulc(ws->ps, 1 + ws->nc))  )

#define	eqWS(u, v) (u == v || (u->nc == v->nc && u->ns == v->ns \
	&& memcmp(u->ps, v->ps, u->nc) == 0))
#endif




/*
 * Construct a new ws, and return a ptr to it.
 */

WS *
initws(void)
{

	/* pre  TRUE */
	/* post invWS(ws) */

	reg WS *ws = gmalloc(sizeof(WS));

	if (ws) {
		if (ws->ps = gmalloc(Iwssz)) {
			ws->sz = Iwssz;
			ws->nc = ws->ns = 0;
			ws->ps[0] = ws->ps[1] = '\000';
		} else {
			gfree(ws);
			ws = NULL;
		}
	}
	return ws;
}



/*
 * Free the ws.  Post condition *is* specifiable, but requires
 * more machinery than what we discussed in class.
 */

void 
freews(reg WS * ws)
{

	/* pre  invWS(ws) */
	/* post COP_OUT */

	if (ws) {
		gfree(ws->ps);
		gfree(ws);
	}
}




/*
 * Append to ws->ps the string p, and then one more '\0' if i ==
 * 1. The value of i is either 1, or 0.
 */

void 
strwcat(reg WS * ws, reg const gchar * p, reg uint i)
{
	/*- pre  invWS(ws) && p != NULL && (i == 0 || i == 1) */
	/*- post
		invWS(ws) && ws->ns == i + ws0->ns
		&& ws->nc = i + strlen(p) + ws0->nc
		&& memcmp(ws->ps, ws0->ps, ws0->nc) == 0
		&& memcmp(ws->ps + ws0->nc, p, 1+strlen(p)) == 0
		&& ws->ps[ws->nc] == '\000'
	 */

	/*
	 * You might find it pretty hard to construct ws0.  Do as
	 * much as you can. However, see dupws()
	 */

	reg uint n;
	reg gchar *q;

	if (p == NULL || ws == NULL)
		return;
	if (i)
		i = 1;
	n = strlen(p) + ws->nc;
	if (ws->sz <= n + i) {
		if (q = gmalloc(n + Iwssz)) {
			memcpy(q, ws->ps, ws->nc);
			gfree(ws->ps);
			ws->ps = q;
			ws->sz = n + Iwssz;
		} else
			return;
	}
	if (q = ws->ps) {
		strcpy(q + ws->nc, p);
		q[n + i] = '\000';
		ws->nc = n + i;
		if (i)
			ws->ns++;
	}
}



/*
 * Make a duplicate of ws, and return a ptr to it.  The dup and
 * the orig will not share memory areas.  Again, this *is*
 * specifiable, but we need more machinery.
 */

WS *
dupws(reg WS * ws)
{
	/* pre  invWS(ws) */
	/*
	 * post w2 == NULL || eqWS(ws, w2) && eqWS(ws, ws0) &&
	 * COP_OUT
	 */


	reg WS *w2;

	if (ws == NULL)
		return NULL;
	w2 = (WS *) gmalloc(sizeof(WS));
	if (w2) {
		if (w2->ps = gmalloc(ws->nc)) {
			w2->sz = w2->nc = ws->nc;
			w2->ns = ws->ns;
			memcpy(w2->ps, ws->ps, ws->nc);
		} else {
			gfree(w2);
			w2 = NULL;
		}
	}
	return w2;
}




/*
 * Return ptr to n-th stringlet from ws->ps.  Stringlets are
 * numbered 0 to ws->ns - 1.
 */

gchar * nthstr(reg const WS * ws, reg int n)
{
	/* pre   invWS(ws) && ws->ns > n && n >= 0 */
	/*
	 * post  eqWS(ws, ws0) && nnulc(ws->ps, result - ws->ps)
	 * == n0
	 */


	reg gchar *p = (ws ? ws->ps : NULL);
	if ((n < 0) || (p == NULL))
		return ES;
	for (p = ws->ps, n++; --n && *p;)
		p += strlen(p) + 1;
	return p;
}


/*
 * In ws, find if the string p exists.  If so, return its index,
 * otherwise return -1.
 */

int 
findstr(reg WS * ws, reg const gchar * p)
{
	/*- pre  invWS(ws) && p != NULL */
	/*- post
		eqWS(ws, ws0) && strcmp(p, p0) == 0
		&& result >= -1
		&& result >= 0 => strcmp(nthstr(ws, result), p) == 0
	*/

	/*- The post is too weak.  We should include
	    result == -1 =>
		forall(i, 0, ws->ns - 1):
			strcmp(nthstr(ws, i), p) != 0
	*/

	if (p && ws) {
		reg gchar *q = ws->ps;
		reg int n = 0;
		for (; *q; n++, q += strlen(q) + 1)
			if (strcmp(p, q) == 0)
				return n;
	}
	return -1;
}



/*
 * Make a new WS which has the stringlets of ws each prefixed
 * with p.
 */
WS *
prefixws(reg const gchar * p, reg WS * ws)
{

	/* pre  invWS(ws) */
	/* post eqWS(ws, ws0) && invWS(result) && COP_OUT */

	/*- One more place for forall:
		forall(i, 0, ws->ns -1):
			strcmp(
				nthstr(result, i),
				strcat(p, nthstr(ws, i))
			) == 0
	*/


	reg WS *w = initws();
	if (w && ws) {
		reg gchar *q = ws->ps;
		while (*q) {
			strwcat(w, p, 0);
			strwcat(w, q, 1);
			q += strlen(q) + 1;
		}
	}
	return w;
}



/*
 * Append to u the stringlets indexed m  upwards of v.
 */

void 
appendws(reg WS * u, reg WS * v, reg int m)
{

	/*- pre  invWS(u) && invWS(v) && 0 <= m && m <= v->ns */
	/*- post
		eqWS(v, v0) && invWS(u)
		&& u->ns == u0->ns + v->ns - m
		&& COP_OUT
	 */

	/*- post should include:
		(forall(i, 0, u0->ns -1):
			strcmp(nthstr(u0, i), nthstr(u, i)) == 0)
	&&	(forall(i, m, v->ns -1):
			strcmp(nthstr(v, i), nthstr(u, u0->ns + i - m)) == 0)
	*/


	reg int n;
	reg gchar *p;

	if (u == NULL || v == NULL)
		return;
	n = v->ns;
	if (m < 0 || n < m)
		return;
	p = nthstr(v, m);
	while (m++ < n) {
		strwcat(u, p, 1);
		p += strlen(p) + 1;
	}
}



/*
 * Shift the [m..] stringlets left by losing the (m-1)-th one.
 */

void 
shiftws(reg WS * ws, reg const int m)
{
	/* pre  EXERCISE_TO_YOU */
	/* post EXERCISE_TO_YOU */

	reg gchar *q;
	reg uint n, k;

	if (ws == NULL || m > ws->ns || m <= 0)
		return;
	q = nthstr(ws, m - 1);
	n = strlen(q) + 1;
	k = ws->nc - (uint) (q - ws->ps) - n;
	memcpy(q, q + n, k);
	ws->ns--;
	ws->nc -= n;
}

/* -eof- */
