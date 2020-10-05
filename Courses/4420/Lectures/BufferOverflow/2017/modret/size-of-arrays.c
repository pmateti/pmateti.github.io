
/* size of builtin types and arrays */

#include <stdio.h>

char b[5];
int a[8] = {0, 1, 2, 3, 0, 1, 2, 3};
char c[3];
char d;

int main() {
  char x[5], y[3], z[7];
  printf("sizeof(char) %lu, sizeof(int) %lu, sizeof(long) %lu\n"
         "sizeof(a) %lu, sizeof(c) %lu\n"
         "address of a[0] %p\naddress of b[0] %p\n"
         "address of c[0] %p\naddress of d    %p\n"
         "address of x[0] %p\naddress of y[0] %p\n"
         "address of z[0] %p\n",
         sizeof(char), sizeof(int),  sizeof(long),
         sizeof(a), sizeof(c),
         &a[0], &b[0], &c[0], &d, x, y, z);
}
