
/* example1.c */

#include <stdio.h>

void function(int a, int b, int c)
{
  char buffer1[5];
  char buffer2[10];

  printf("buffer addresses:\n %p\n %p\n", buffer1, buffer2);
}

int main()
{
  function(1, 2, 3);
  return 0;
}
