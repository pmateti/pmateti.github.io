
// 3n+1 

#include <iostream>
using namespace std;
#include <stdlib.h>

int main(int argc, char * argv [])
{

  int x = atoi(argv[1]);
  int y;
  cout << x;

  /*@ x is the given input integer, x > 0 */
  while (x > 1) {
    cout << x << '\n';
    if (x % 2 == 0)
      x /= 2;
    else
      x = 3*x + 1;
  }

}
