/***** uno: prnttree.h *****/

/* Copyright (c) 2000-2003 by Lucent Technologies - Bell Laboratories     */
/* All Rights Reserved.  This software is for educational purposes only.  */
/* Permission is given to distribute this code provided that this intro-  */
/* ductory message is not removed and no monies are exchanged.            */
/* No guarantee is expressed or implied by the distribution of this code. */
/* Software written by Gerard J. Holzmann based on the public domain      */
/* ANSI-C parser Ctree Version 0.14 from Shaun Flisakowski                */

/* Original version by Shawn Flisakowski, March 27, 1995 */

#ifndef   PRNTTREE_H
#define   PRNTTREE_H

#include <stdio.h>
#include "tree.h"

extern void indent(int, FILE *);
extern void  fputs_metachr(char, int);
extern void  fputs_metastr(char *);
extern char *print_ptr(void *);
extern char *toksym(int, int);

#define VERY_LARGE	131072
#define MEDIUM_LARGE	4096

#endif    /* PRNTTREE_H */
