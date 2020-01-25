/*
 The famous Bubble Sort in plain C, with example assertions 
 send comments to pmateti@wright.edu
 % gcc -o bubble-sort -std=c99 bubble-sort.c
*/

#include <stdio.h>
#include <assert.h>
#include <time.h>               /* for srand() */
#include <stdlib.h>

int a[10], aold[10], n = 15;  /* a[0 .. n-1]; aold to be used only in asserts */

/* Array a starting from index x upto y (including y) is sorted.  Aux
   predicate.  For use in assertions only. 0 is False, 1 is True */

int sorted(int a[], int x, int y)
{
  for (int i = x; i < y ; i++) {
    if (a[i] > a[i+1])
      return 0;
  }
  return 1;
}

/* The two arrays a[] and b[] have the same elements. n is the number of their
   elements. Aux predicate */

int theSame(int a[], int b[], int n)
{
  /* for you to do */
  return 1;
}

void bubbleSort(int a[], int n)
{
  assert(n > 0);                /* pre */
  for (int j = 0; j < n; j++) {
    for (int i = n - 2; i >= j; i --) {
      if (a[i] > a[i+1]) {
        int t = a[i];
        a[i] = a[i+1];
        a[i+1] = t;
      }
      assert(a[i] <= a[i+1]);
    }
    assert(sorted(a, 0, j) && 0 <= j && j < n);
  }
  assert(sorted(a, 0, n-1) && theSame(aold, a, n)); /* post */
}

void printArray(char * msg)
{
  printf("%s", msg);
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int main()
{
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 100;        /* so we can "see" easily */
    aold[i] = a[i];
  }
  printArray("generated array: ");
  bubbleSort(a, n);
  printArray("array sorted   : ");
}

/* -eof- */
