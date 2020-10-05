
/* A tiny program to study deeply. */

#include <stdio.h>

unsigned long get_sp(void) {
   __asm__("movl %esp,%eax");
}

void recurse() {
  char a[1024*1024];
  static int x  = 0;
  
  printf("x %d sp %lx\n", x++, get_sp());
  recurse();
}

int main() {
  recurse();
  return 0;
}
