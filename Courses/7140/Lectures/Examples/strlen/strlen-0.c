
#include <stddef.h>
#include <stdio.h>

size_t strlen (const char str[]) 
{
  const char *p;
	
  if (str == NULL)
    return 0;
	
  p = str;
  while (*p != '\0') 
    p++;
	
  return p - str;
}

int main()
{
  printf("%lu\n", strlen("hello-there!\n"));
}
