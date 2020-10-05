
/* pmateti@wright.edu */
/* compile: gcc -Wall -fno-stack-protector -z execstack -o bo bo.c */

#include <stdio.h>
#include <unistd.h>

/* Buffer Overflow is possible in bo(). */

int bo() {
    char a[10];                 /* on stack a[], keep it short */
    printf("Give input:\n");    /* \n force output */
    int nbytesread = read(0, a, 80);     /* 0 stdin, into a, upto 80 bytes */
    printf("your input :%s: was %d bytes long\n", a, nbytesread);
    return nbytesread;
}

int main() {
  while (1) {
    int n = bo();               /* bo() may crash */
    printf("\nback in main(), the n == %d\n\n", n);
  }
  return 0;
}
