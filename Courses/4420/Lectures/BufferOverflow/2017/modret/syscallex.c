#define _GNU_SOURCE
#include <unistd.h>
    
int main() {
  syscall(276);                 /* tee */
  return 0;
}
