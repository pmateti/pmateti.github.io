/*
 * file: modret.c by pmateti@wright.edu 2013 oct 10; 
 * modify return address to see the effects
 *
 * compile: gcc -o modret -ansi -pedantic -Wall -Wno-format modret.c
 * get asm listing: gcc -Wa,-alh,-L -ansi -pedantic -Wall -Wno-format modret.c
 */

#include <stdio.h>
#include <stdlib.h>

void printStack(int n, int *zp) {	/* print a few stack items */
  int i;
  for (i = -4; i < 4; i++)
    printf("%x: zp[%x] %x:%x\n", n, i,  &zp[i], zp[i]);
}

void modret(int a, int b, int c) {
  int d = 0x89abcdef;           /* just a recognizable number */
  int *zp = &a;
  printf("2: &a %x &b %x &c %x &d %x a %x b %x c %x d %x\n",
         &a, &b, &c, &d, a, b, c, d);
  printStack(3, zp);
  printf("4: zp[b] %x", zp[b]);
  zp[b] += a;                   /* modifying a stack location */
  printf(" %x\n", zp[b]);
  printf("5: &a %x &b %x &c %x &d %x a %x b %x c %x d %x\n",
         &a, &b, &c, &d, a, b, c, d);
  printStack(6, zp);
}

int main(int argc, char *argv[]) {
  int x = 0x11, y = 0, z = 0;
  printf("0: sizeof int %x long %x int * %x; main %x\n",
         sizeof(int), sizeof(long), sizeof(int *), main);
  if (argc < 3) return 0;       /* should give two int args */

  y = atoi(argv[1]);
  z = atoi(argv[2]);
  printf("1: &x %x &y %x &z %x x %x y %x z %x\n",
         &x, &y, &z, x, y, z);
  modret(y, z, 0x234);          /* an easy to recognize number */
  x += 0x22;
  x += 0x33;
  printf("7: x %x\n",  x);
  return 0;
}

/* -eof- */
