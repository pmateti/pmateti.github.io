
/* recurse.c -- illustrate stack growth. Causes segmentation fault. */

#include <stdio.h>

int x = 0;                      /* recursion depth */

/* ignore gcc warning: control reaches end of non-void function
 * [-Wreturn-type]
 */
unsigned long get_sp(void) {
  __asm__("movl %esp,%eax");
}

void recurse() {
  char a[1024*1024];
  
  printf("x %d sp %lx\n", x, get_sp());
  x++;
  a[1] = 1;
  a[9] = a[1];
  recurse();
}

int main() {
  recurse();
  return 0;
}

/* -eof- */
