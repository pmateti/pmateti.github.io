/* file: modret .c by pmateti@wright.edu; 
 * modify return address to see the effects
 */

/* assembly listing: gcc -Wa,-alh,-L  modret.c > modret-asm.txt */
/* normal compile: gcc -o modret modret.c */

#include <stdio.h>

void modret(int a, int b, int c) {
  unsigned int d = 0x89abcdef;
  unsigned int *zp = &a - 3;
  unsigned int i;

  for (i = 0; i < 8; i++)
    printf("%x:%x, ", i, zp[i]);
  zp[2] += a;
}

int main(int argc, char *argv[]) {
  int x = 0, y = 0;
  if (argc > 1)
    y = atoi(argv[1]);
  x += 0x11;
  modret(y, 0x234, 0x567);
  x += 0x22;
 Label33:
  x += 0x33;
  printf("main==%x, &x==%x, &y==%x; x=%x\n", main, &x, &y, x);
  return 0;
}

/* -eof- */
