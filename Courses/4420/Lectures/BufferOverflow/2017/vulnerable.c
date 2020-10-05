/* vulnerable.c */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char buffer[512];

  printf("&buffer[0] %p\n", buffer);
  if (argc > 1)
    strcpy(buffer, argv[1]);
  return 0;
}
