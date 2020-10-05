
// bubbleSort.cpp by pmateti@wright.edu

#include <stdlib.h>		// srand, rand
#include <time.h>		// time(0)
#include <iostream>
#include <vector>
using namespace std;

template < typename T>    // ignoring template issues ...

void bubbleSort(vector < T > & v) {
  const int size = v.size();
  for(int i = 0; i < size; i++) {
    for(int j = size - 1; j > i ; j--) {
      if (v[j-1] > v[j])
        std::swap(v[j-1], v[j]);
    }
  }
}

void printArray(int a [], unsigned int size)
{
  const int size = v.size();
  cout << endl;
  for (unsigned int i = 0; i < size; i++)
    cout << a[i] << ", ";
  cout << endl;
}

void initArray(int a [], unsigned int size)
{
  const int size = v.size();
  srand(time(0));
  for (unsigned int i = 0; i < size; i++)
    a[i] = rand() % 100;
}

int main(int argc, char * argv [])
{
  unsigned int z = sizeof(a)/sizeof(int);
  unsigned int x = (argc > 1? atoi(argv[1]) : z);
  std::vector <int> a (100);
  if (x < z) z = x;
  initArray(a, z);
  printArray(a, z);

  bubbleSort (a);		// 
  printArray(a, z);
}

// -eof-
