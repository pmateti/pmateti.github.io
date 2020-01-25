
#include "wb.h"

/*
 * Find a vacant RPC server program number.
 */

#define NPROGNUMSTOTRY 1000
#define NATTEMPTS 10

static unsigned long findTransient(int version)
{
  int skt = socket(AF_INET, SOCK_STREAM, 0), nerrors = 0;
  if (skt < 0) {
    fprintf(stderr, "transient.c: socket errno=%d\n", errno);
    nerrors ++;
  }

  struct sockaddr_in ad;
  ad.sin_addr.s_addr = 0;
  ad.sin_family = AF_INET;
  ad.sin_port = 0;
  unsigned int len = sizeof(ad);
  if (bind(skt, (struct sockaddr *) &ad, len) < 0) {
    fprintf(stderr, "transient.c: bind socket errno=%d.\n", errno);
    nerrors ++;
  }
  if (getsockname(skt, (struct sockaddr *) &ad, &len) < 0) {
    fprintf(stderr, "transient.c: getsockname errno=%d.\n", errno);
    nerrors ++;
  }

  for (unsigned long prognum = 0x40000000; 
       prognum < 0x40000000 + NPROGNUMSTOTRY; prognum ++)
    if (pmap_set(prognum, version, IPPROTO_TCP, ad.sin_port))
      return prognum;

  if (skt > 0 && nerrors > 0)
    close(skt);
  return 0;
}

int getTransientProgNumber(int version)
{
  unsigned long prognum, i;
  for (i = 0; i < NATTEMPTS;) {
    prognum = findTransient(version);
    if (prognum > 0)
      return prognum;

    fprintf(stderr, "transient.c: attempt %lu\n", ++ i);
    sleep(1);			/* might work later */
  }
  return 0;
}

/* -eof- */
