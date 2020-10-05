
/* Library Calls v. SysCalls */

#include <unistd.h>
#include <sys/time.h>           /* timeval */
#include <sys/syscall.h>        /* SYS_* */
#include <stdio.h>

int main()
{
  struct timeval tv1, tv2;

  gettimeofday(& tv1, NULL);    /* libc */
  syscall(SYS_gettimeofday, & tv2, NULL);
  printf("tv-sec+tv_usec from tv1 %ld+%ld from tv2 %ld+%ld\n",
         tv1.tv_sec, tv1.tv_usec, tv2.tv_sec, tv2.tv_usec);
}
