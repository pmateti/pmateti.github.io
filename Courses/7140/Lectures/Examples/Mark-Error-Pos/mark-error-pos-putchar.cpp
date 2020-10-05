//
// mark-error-pos-putchar.cpp
//
// based on an example from Niklaus Wirth

#include <cstdio>

int  pos[] = { 3, 6, 9, 19, 22 };
char txt[] = "Thes broplem is peenuds.";	// example
char out[] = "  *  *  *         *  *";		// output expected

// assume starting index is a 1 and not 0 even though this is not Pascal

#define L (sizeof(txt)/sizeof(char))
#define n (sizeof(pos)/sizeof(int))

void markErrorPosA()
{
    int k = 1;
    for (int i = 1; i <= L; i++) {
	if (i == pos[k]) {
	    putchar('*');
	    k++;
	} else
	    putchar(' ');
    }
}

void markErrorPosB()
{
    int k = 1;
    pos[n + 1] = 0;
    for (int i = 1; i <= L; i++) {
	if (i == pos[k]) {
	    putchar('*');
	    do {
		k++;
	    } while (i == pos[k]);
	} else
	    putchar(' ');
    }
}

void markErrorPosC()
{
    int i = 1;
    for (int k = 1; k <= n; k++) {
	do {
	    putchar(' ');
	    i++;
	} while (i != pos[k]);
	putchar('*');
	i++;
    }
}

void markErrorPosD()
{
    int i = 1;
    int k = 1;
    do {
	while (i < pos[k]) {
	    putchar(' ');
	    i++;
	}
	if (i == pos[k]) {
	    putchar('*');
	    i++;
	}
	k++;
    } while (k <= n);
}

void markErrorPosE()
{
    int i = 1;
    int k = 1;
    while (k <= n) {
	while (i < pos[k]) {
	    putchar(' ');
	    i++;
	}
	while (i == pos[k])
	    k++;
	putchar('*');
    }
}

int main()
{
    puts(txt);
    markErrorPosA();
    putchar('\n');
}
