/***** uno: uno.c *****/

/* Copyright (c) 2000-2003 by Lucent Technologies - Bell Laboratories     */
/* All Rights Reserved.  This software is for educational purposes only.  */
/* Permission is given to distribute this code provided that this intro-  */
/* ductory message is not removed and no monies are exchanged.            */
/* No guarantee is expressed or implied by the distribution of this code. */
/* Software written by Gerard J. Holzmann  --  http://spinroot.com/gerard */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef PC
	#include <unistd.h>
	#include <signal.h>
#else
	int unlink(const char*);
	int close(int);
#endif

#ifndef BINDIR
	#ifdef PC
		#define BINDIR	""
	#else
		#define BINDIR	"/usr/bin/"
	#endif
#endif

#ifndef LX
	#define LX	"uno_local"
#endif

#ifndef GX
	#define GX	"uno_global"
#endif

static int  localonly, usecheck;
static int  glob_base, verbose, glob_prop;
static char *w_dir;

#ifdef DEBUG
	void System(char *cmd)	{ printf("<%s>\n", cmd); }
#else
	#define System(x)	{ if (verbose) printf("<%s>\n", x); system(x); }
#endif

#define BSIZE	4096

static char loc_args[BSIZE];
static char glob_cmd[BSIZE];
static char buf[BSIZE];

typedef struct Fnm Fnm;
struct Fnm {
	char *f;
	Fnm *nxt;
};

static Fnm *fnames;

static void
uno_usage(void)
{	/* duplicates function of /v/bin/uno shellscript in c-program */

	fprintf(stderr, "usage: uno [options] *.c\n");
	fprintf(stderr, "uno options:\n");
	fprintf(stderr, "\t-CPP=x	set preprocessor to x\n");
	fprintf(stderr, "\t-Dname=def	define    compiler directive\n");
	fprintf(stderr, "\t-Dname    	define    compiler directive\n");
	fprintf(stderr, "\t-Uname    	undefine  compiler directive\n");
	fprintf(stderr, "\t-Iname    	add name to list of dirs searched for include-files\n");
	fprintf(stderr, "\t-Wname       use name as working directory to store .uno files\n\n");
	fprintf(stderr, "\t-n		ignore preprocessing directives in source files\n");
	fprintf(stderr, "\t-o arg	ignored, for modest compatability with cc arguments\n");
	fprintf(stderr, "\t-m uno.dfn	use master (type) definitions file uno.dfn\n");
	fprintf(stderr, "\t-x f		declare f to be a function that does not return\n\n");
	fprintf(stderr, "\t-V        	print version number and exit\n");
	fprintf(stderr, "\t-s		print symbol table information and exit\n\n");
	fprintf(stderr, "\t-l or -c	perform only local analysis, not global\n");
	fprintf(stderr, "\t-p x		check local property def stored in file x\n");
	fprintf(stderr, "\t-g x		check global property def stored in file x\n\n");
	fprintf(stderr, "\t-a		report all error paths (local analysis)\n");
	fprintf(stderr, "\t-t		more detailed execution traces (global analysis)\n");
	fprintf(stderr, "\t-u		complain about redundancies of all sorts\n");
	fprintf(stderr, "\t-v		verbose mode (mostly for debugging)\n");
	fprintf(stderr, "\t-w		more picky, includes -u and -t\n");
	exit(1);
}

static void
add_target(char *f)
{	Fnm *n;

	if (f[0] == '_')
		return;	/* avoid re-preprocessing stale uno intermediaries */

	n = (Fnm *) malloc(sizeof(Fnm));
	n->f = (char *) malloc(strlen(f) + 1);
	strcpy(n->f, f);
	n->nxt = fnames;
	fnames = n;
}

static void
pass_loc(char *pref, char *par)
{
	strcat(loc_args, pref);
	if (par)
	{	strcat(loc_args, par);
		strcat(loc_args, " ");
	}
}

static void
set_glb(char *par)
{
	glob_prop++;
#ifndef DEBUG
	int fd;
	fd = creat("_uno_.c", 0644);
	if (fd < 0)
	{	fprintf(stderr, "uno: cannot create temp files\n");
		exit(1);
	}
	close(fd);
#else
	System("echo \"/* empty file */\" > _uno_.c");
#endif
	sprintf(buf, "%s%s -prop %s _uno_.c", BINDIR, LX, par);
	System(buf);
#if 1
	unlink("_uno_.c");
#else
	System("rm -f _uno_.c");
#endif
}

static void
cleanup(int unused)
{	int i;

	if (verbose) return;

	if ((int) strlen(glob_cmd) > glob_base)
	{	for (i = 0; i < glob_base; i++)
			glob_cmd[i] = ' ';
#ifdef PC_
		glob_cmd[0] = 'd';
		glob_cmd[1] = 'e';
		glob_cmd[2] = 'l';
#else
		glob_cmd[0] = 'r';
		glob_cmd[1] = 'm';
		glob_cmd[2] = ' ';
		glob_cmd[3] = '-';
		glob_cmd[4] = 'f';
#endif
		if (w_dir)
		{	char *p = malloc(strlen(glob_cmd) + strlen("cd ;") + strlen(w_dir) + 1);
			sprintf(p, "cd %s; %s\n", w_dir, glob_cmd);
			System(p);
		} else
		{	System(glob_cmd);
	}	}
}

static void
version_info(void)
{	strcat(loc_args, "-V");
	System(loc_args);
	exit(0);
}

static void
run_uno(void)
{	char *p;

	while (fnames)
	{	strcpy(buf, loc_args);
		strcat(buf, fnames->f);
		System(buf);

		strcat(glob_cmd, fnames->f);
		p = strrchr(glob_cmd, '.');
		if (!p)
		{	fprintf(stderr, "uno: cannot happen1\n");
			exit(1);
		}
		*p = '\0'; /* replace .c with .uno */
		strcat(glob_cmd, ".uno ");

		fnames = fnames->nxt;
	}
	if (!localonly)
	{
		if (glob_prop)
			strcat(glob_cmd, "_uno_.uno ");
		if (w_dir)
		{	p = malloc(strlen(glob_cmd) + strlen("cd ;") + strlen(w_dir) + 1);
			sprintf(p, "cd %s; %s\n", w_dir, glob_cmd);
			System(p);
		} else
		{	System(glob_cmd);
	}	}
	cleanup(0);
}

int
main(int argc, char *argv[])
{
	strcpy(loc_args, BINDIR);
	strcat(loc_args, LX);
	strcat(loc_args, " ");

	strcpy(glob_cmd, BINDIR);
	strcat(glob_cmd, GX);
	strcat(glob_cmd, " ");

	argc--;
	while (argc-- > 0)	/* @uno_suppress side-effect */
	{	argv++;
		if (0) printf("%3d: '%s'\n", argc, *argv);
		if ((*argv)[0] == '-')
		{	if (0) printf("option '%c' -- '%s'\n", (*argv)[1], *argv);
			switch((*argv)[1]) {
			case 'C':	/* -CPP=... */
			case 'D':
			case 'U':
			case 'I':
				pass_loc(*argv, "");
				break;

			case 'W':
				w_dir = malloc(strlen(*argv)+1-2);
				strcpy(w_dir, &(*argv)[2]);
				pass_loc(*argv, "");
				break;
			case 'a':	/* l */
				pass_loc("-allerr ", NULL);
				break;
			case 'g':	/* g */
				argv++; argc--;
				set_glb(*argv);
				break;
			case 'c':	/* absorb cc args */
			case 'l':	/* l */
				localonly = 1;
				pass_loc("-localonly ", NULL);
				break;
			case 'm':	/* l */
				argv++; argc--;
				pass_loc("-master ", *argv);
				break;
			case 'n':	/* l */
				pass_loc("-nopre ", NULL);
				break;
			case 'o':	/* absorb cc args */
				argv++; argc--;
				break;
			case 'p':	/* l */
				argv++; argc--;
				pass_loc("-prop ", *argv);
				break;
			case 's':	/* l */
				pass_loc("-s ", NULL);
				localonly = 1;
				break;
			case 't':	/* g */
				strcat(glob_cmd, "-l ");
				break;	/* g */
			case 'V':	/* l */
				version_info();
				break;
			case 'v':	/* g,l */
				pass_loc("-v ", NULL);
				strcat(glob_cmd, "-v ");
				verbose = 1;
				break;
			case 'w':	/* g,l */
				pass_loc("-picky ", NULL);
				strcat(glob_cmd, "-l ");
			case 'u':	/* g,l  @uno_suppress: fall through on switch */
				usecheck = 1;
				pass_loc("-use ", NULL);
				strcat(glob_cmd, "-u ");
				break;
			case 'x':	/* l */
				argv++; argc--;
				pass_loc("-exit ", *argv);
				break;
			default :
				uno_usage();
				break;
			}
		} else if (strstr(*argv, ".c") != NULL)
			add_target(*argv);
		else
			uno_usage();
	}
	if (!fnames)
		uno_usage();

#ifndef PC
	signal(SIGINT, cleanup);
#endif

	glob_base = (int) strlen(glob_cmd);

	run_uno();

	if (!usecheck)
	printf("uno:\tcheck completed, try 'uno -h' for different checks\n");

	return 0;
}
