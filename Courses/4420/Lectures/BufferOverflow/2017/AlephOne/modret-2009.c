/* file: modret .c by pmateti@cs.wright.edu; 
 * modify return address to see the effects
 */

#include <stdio.h>

void function(int a) {
  unsigned int *ret;

  ret = (int *) ((int)&ret + 8);
  printf("*ret: before = %d 0x%x, ", *ret, *ret);
  (*ret) += a;
  printf("after = %d 0x%x\n", *ret, *ret);
}

int main(int argc, char *argv[]) {
  int x, y;

  y = 15;
  if (argc > 1)
    y = atoi(argv[1]);
  x = 0;
  function(y);
  x += 22;
  x += 33;
  printf("x == %d\n",x);
  return 0;
}

/* assembly listing: gcc -Wa,-alh  modret.c > modret.txt */
/* normal compile: gcc -o modret modret.c */

/* try: ./modret 0; ./modret 9; ./modret 15; */
/* after above compile with gcc 2.96 and up */

/* -eof- */
