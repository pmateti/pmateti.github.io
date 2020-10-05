/*
  Filename: turnin.c
  Amitava Datta 1989, Prabhaker Mateti 1998 - 2013

  Usage: turnin <project-name> <list-of-files-to-turnin>

  E.g.:  turnin P1 *.c Makefile

Instructors: Verify please
--------------------------

0. The turnin executable should be owned by the INSTRUCTOR, and setuserid-ed:
   chmod ugo+s turnin

1. Create subdirs within $SUBMITHOME corresp to the names in *pnames[]
   below.  The directory $SUBMITHOME/<project-name> must exist with
   permission 700 (rwx------), and owned by the INSTRUCTOR.  All the
   dirs on the way to this must be searchable.  Periodically verify
   that the permissions have remained so.

2. Verify: SUBMITHOME COURSE CLOSED EMAILADDR INSTRUCTOR

*/

#define SUBMITHOME SUBMITPARENT
/* Home dir for class. The directory where assignment dirs reside. */
#ifndef SUBMITHOME
error define SUBMITHOME as in  "/home/pmateti/CEG460-Turnins/2010-Winter"
#endif

char *pnames[] =   {
    "L0",    "L1",    "L2",    "L3",    "L4",    "L5",    "L6",    "L7",
    "L8",    "L9",    "La",    "Lb",    "Lc",    "Ld",    "Le",    "MT",
    "FI",    0
  };


/* user name of instructor; also used as e-mail address. */
#define INSTRUCTOR "pmateti"
#define EMAILADDR "pmateti@wright.edu"

/* Name of file in the assignment directory whose existence implies
   that turnins have been closed. */
#define CLOSED "CLOSED"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/errno.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <fcntl.h>

extern int errno;

char msgbuf[4096];		/* message buffer */
int gargc;			/* ==argc */
char ** gargv;			/* ==argv */
int studentsUid;		/* the student's */
int instructorsUid;		/* the instructor's */
int euid;			/* the instructor's id */
char studentsName[1024];	/* students loginId */
char studentsDir[MAXPATHLEN];	/* students files will be here */
char assignDir[MAXPATHLEN];	/* which will be copied to here */
struct stat st;

void setGlobals()
{
    instructorsUid = getpwnam(INSTRUCTOR)->pw_uid;
    studentsUid = getuid();
    euid = geteuid();
    strncpy(
	    studentsName, 
	    getpwuid(studentsUid)->pw_name,
	    sizeof(studentsName));
}

int owner(char * fnm)
{
  struct stat s;
  int x = stat(fnm, &s);
  return (x == 0? s.st_uid : 0);
}

/* Signal handler for SIGINT and SIGTSTP. Ignores the signal. */

void ignore(int signo)
{
    signal(signo, ignore);
}

void *gmalloc(int n)
{
  return malloc(n);
}

int gfree(void *p) {
  if (p)
	  free(p);
  return 0;
}


typedef unsigned int uint;

#define	Iwssz	100		/* size increment for WS */

typedef struct {
  uint sz;			/* size of malloc-d ->ps area */
  uint nc;			/* #chars used up so far */
  uint ns;			/* #stringlets in ws */
  char *ps;			/* ptr to malloc-d area of size sz */
} WS;


/*
 * Construct a new ws, and return a ptr to it.
 */

WS *
initws(void)
{

  WS *ws = gmalloc(sizeof(WS));

  if (ws) {
    ws->ps = gmalloc(Iwssz);
    if (ws->ps) {
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


void 
freews(WS * ws)
{

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
strwcat(WS * ws, const char * p, uint i)
{
  /*- pre  invWS(ws) && p != NULL && (i == 0 || i == 1) */
  /*- post
    invWS(ws) && ws->ns == i + ws0->ns
    && ws->nc = i + strlen(p) + ws0->nc
    && memcmp(ws->ps, ws0->ps, ws0->nc) == 0
    && memcmp(ws->ps + ws0->nc, p, 1+strlen(p)) == 0
    && ws->ps[ws->nc] == '\000'
  */

  uint n;
  char *q;

  if (p == NULL || ws == NULL)
    return;
  if (i)
    i = 1;
  n = strlen(p) + ws->nc;
  if (ws->sz <= n + i) {
    q = gmalloc(n + Iwssz);
    if (q == NULL)
      return;
    memcpy(q, ws->ps, ws->nc);
    gfree(ws->ps);
    ws->ps = q;
    ws->sz = n + Iwssz;
  }
  q = ws->ps;
  if (q) {
    strcpy(q + ws->nc, p);
    q[n + i] = '\000';
    ws->nc = n + i;
    if (i)
      ws->ns++;
  }
}


void catargs(WS * w, int k)
{
  int i = k;
  for (; i < gargc; i++) {
    strwcat(w, gargv[i], 0);
    strwcat(w, " ", 0);
  }
}

/* Inform the instructor by e-mailing a summary of the fatal "event."
   Sends copies of userid argc argv[] and the msg. */

void informInstructor(char * msg, int enable)
{

#if 1
  printf("please inform your instructor of the following:\n"
	 "%s\n", msg);
#else
  {
  WS *w = initws();

  sprintf(msgbuf, "userid=%s; argc=%d; msg=%s;\n",
	  studentsName, gargc, msg);

  strwcat(w, msgbuf, 0);
  strwcat(w, "argv[]=", 0);
  catargs(w, 0);

  if (w->nc > sizeof(msgbuf) - 20) {
    w->ps[sizeof(msgbuf) - 20] = 0;
  }
  sprintf(msgbuf, "mail -s 'turnin:%s [%s]' %s << EOF\n"
	  "%s\n"
	  "EOF",
	  COURSE, msg, EMAILADDR, 
	  w->ps);
  system(msgbuf);
  freews(w);
  }
#endif
  exit(0);
}

/* Inform the student: List the studentsDir contents. */

void filesOfStudent()
{
  if (chdir(studentsDir) == 0)  {
    fprintf(stdout, 
	    "\nAs of now, your dir for %s %s contains the following files.\n"
	    "(Ignore the 'total #' line -- that number is not a file count.)\n",
	    COURSE, gargv[1]);
    sprintf(msgbuf, "ls -lAqsR");
    system(msgbuf);
  }
  else {
    fprintf(stdout, 
	    "\nCould not cd to your dir %s for %s %s; errno = %d\n",
	    studentsDir,
	    COURSE, gargv[1], errno);

  }
}

/* Submit the files named. Function that actually performs the copy of
   all files. */

#if 0

/* C language version */

void submitAll()
{
    int i, from, to, numbytes;
    char buffer[4096];
    
    for(i = 2; i < gargc; i++)
    {
      char * cfnm = gargv[i];

      fprintf(stderr, "file %s ", cfnm);
      from = open(cfnm, O_RDONLY);
      if (from < 0) {
	perror(cfnm);
	continue;
      }

      sprintf(msgbuf, "%s/%s", studentsDir, cfnm);
      to = open(msgbuf, O_RDWR | O_CREAT | O_TRUNC, 0644);
      if (to < 0) {
	sprintf
	  (msgbuf, "couldn't be copied into %s\n", studentsDir);
	perror(msgbuf);
	close(from);
	continue;
      }

      /* Both files are open. Start copying. */
      while((numbytes = read(from, buffer, sizeof(buffer))) > 0) {
	    if (write(to, buffer, numbytes) != numbytes) {
		perror("copy error");
		break;
	    }
      }

      /* Check if there was any error in last read operation. */
      if (numbytes < 0) {
	perror("read error");
      }

      close(from);
      close(to);

      /* so that instructor/TA can read them. */
      chmod(msgbuf, 0644);
      fprintf(stderr, "submitted\n");
      filesOfStudent();
    }
}
#else

/* Shell version: Construct a 'cp -ap f1.c ... sdir; chmod 644 sdir/\*'
   command, and run it. */

void submitAll()
{
  WS * w = initws();

  strwcat(w, "cp -p ", 0);
  catargs(w, 2);
  strwcat(w, " ", 0);
  strwcat(w, studentsDir, 0);
  strwcat(w, "&& chmod 644 ", 0);
  strwcat(w, studentsDir, 0);
  strwcat(w, "/* ; cd ", 0);
  strwcat(w, studentsDir, 0);

  strwcat(w, "&& echo We now have the following files from you"
	  "&& ls -lAqsR", 0);
  system(w->ps);
  freews(w);
}
#endif

/* Typical problem: student copies this turnin file */

void exitIfNotInstructorsProg() {
    if (owner(gargv[0]) != instructorsUid
	|| euid != instructorsUid) {
      fprintf(stderr,
	      "\n"
	      "The program you just ran should be owned by your instructor.\n"
	      "But it is not, possibly because you copied it"
	      "instead of just linking it.\n"
	      "So, it is quitting.\n"
	      "\n");

      exit(2);
    }
}

/* Check that the Assignment dir exists.  Do not create it.  But do
   change permissions temporarily to rwx everybody.  This is a gaping
   security/privacy hole that can be exploited.  */

void exitIfAssignDirDoesNotExist()
{
    /* Build the pathname to the assignment directory. */
    sprintf(assignDir,"%s/%s", SUBMITHOME, gargv[1]);
    if (chmod(assignDir, 0777)) {
      fprintf(stderr, "\n"
	      "%s: this directory does not exist\n"
	      "Check if you mistyped the name [%s] for the submission\n",
	      assignDir, gargv[1]);
      exit(3);
    }
}

/* Construct the destination directory, if it is not already there.
   Temporarily, set the permissions to rwx everybody.  Each student
   has a directory in the turnin directory with the user name as the
   name of the directory. */

void exitIfStudentsDirCouldNotBeMade()
{
    sprintf(studentsDir,"%s/%s/%s", SUBMITHOME, gargv[1], studentsName);

    /* Check if students directory exists. */
    if (stat(studentsDir, &st) < 0) {
	/* Directory does not exist. Ok to make it. On BSDs this new
	   directory will have effective uid as owner, i.e. the
	   instructor. */
	mkdir(studentsDir, 0777);
    }

    /* Need to explicitly change the permissions.  If it was just
       created, the permissions will not be 0777 if the umask is not
       22. */
    if (chmod(studentsDir, 0777)) {
      /* Something went wrong.  It is not safe to proceed. */
      informInstructor ("studentsDir chmod 0777 failed", 1);
      exit(4);
    }
}

int main(int argc, char *argv[])
{

    int ok = 0;

    /* Ignore these signals. Otherwise the dirs may have undesirable
       permissions. */
    signal(SIGINT, ignore);
    signal(SIGTSTP, ignore);
    signal(SIGQUIT, ignore);
    
    gargc = argc;
    gargv = argv;
    setGlobals();

    fprintf(stderr, "\nThis is a 'turnin' program for %s %s instructor %s\n",
	    TERM, COURSE, EMAILADDR);

    if (argc < 2) {
      fprintf(stderr, "usage: %s <project-name> [<filenames>]\n",
	      gargv[0]);
      exit(1);
    }

    exitIfNotInstructorsProg();
    exitIfAssignDirDoesNotExist();
    exitIfStudentsDirCouldNotBeMade();    

    if (argc == 2) {
 	fprintf(stderr,
		"\nYou did not name any files to turnin.\n"
		"Perhaps you merely wish to check what files"
		"you already turned in for %s.\n", gargv[1]);
	ok = -1;
    }
	
    /* Check if turnin is still open for this assignment. TBD */
    sprintf(msgbuf, "%s/%s", assignDir, CLOSED);
    if (!stat(msgbuf, &st)) {
      fprintf(stderr, "Sorry, turnin closed for %s %s\n", COURSE, gargv[1]);
      ok = -1;
    }

    /* We will need to do the actual copying in the child. */
    if (ok == 0) {
      int xx = fork();

      if (xx == -1)
	informInstructor("fork failed.", 1);

      if (xx == 0) {
	/* Now we need to change the euid of the process to the uid so
	   that the students files can be accessed. setuid() sets both
	   uid and euid to the arg uid passed. */
	if (setuid(studentsUid) < 0) {
	    informInstructor("Couldn't change uid", 1);
	}
	
	/* At this point the process is completely the student's and
	   he/she has read permissions to his/her files and also write
	   permissions to the directory where we need to copy the
	   files. */
	  
	submitAll();
	exit(0);
      }
      /* In the parent. Wait for child to die. Should check STATUS
	 on return from wait(). */
      wait(&xx);

      /* change permissions of directories. */
      chmod(studentsDir, 0700);
      chmod(assignDir, 0700);
    }
    
    if (ok == -1) filesOfStudent();
    return 0;
}


/* -eof- */
