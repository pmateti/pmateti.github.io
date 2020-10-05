//
// mark-error-pos.cpp
//
// based on an example from Niklaus Wirth, 1984 Turning Award Winner

#include <iostream>
using namespace std;

int  pos[] = { 3, 6, 9, 19, 22 };
char txt[] = "Thes broplem is peenuds.";	// example input
char out[] = "  *  *  *         *  *";  	// expected output

// assume starting index is a 1 and not 0 even though this is not Pascal

#define L (sizeof(txt)/sizeof(char))
#define n (sizeof(pos)/sizeof(int))

void markErrorPosA()
{
    int k = 1;
    for (int i = 1; i <= L; i++) {
	if (i == pos[k]) {
	  cout << '*';
	    k++;
	} else
	    cout << ' ';
    }
}

void markErrorPosB()
{
    int k = 1;
    pos[n + 1] = 0;
    for (int i = 1; i <= L; i++) {
	if (i == pos[k]) {
	    cout << '*';
	    do {
		k++;
	    } while (i == pos[k]);
	} else
	    cout << ' ';
    }
}

void markErrorPosC()
{
    int i = 1;
    for (int k = 1; k <= n; k++) {
	do {
	    cout << ' ';
	    i++;
	} while (i != pos[k]);
	cout << '*';
	i++;
    }
}

void markErrorPosD()
{
    int i = 1;
    int k = 1;
    do {
	while (i < pos[k]) {
	    cout << ' ';
	    i++;
	}
	if (i == pos[k]) {
	    cout << '*';
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
	    cout << ' ';
	    i++;
	}
	while (i == pos[k])
	    k++;
	cout << '*';
    }
}

int main()
{
    cout << (txt) << endl;  markErrorPosA(); cout << endl;
  //  cout << (txt) << endl;  markErrorPosB(); cout << endl;
  //  cout << (txt) << endl;  markErrorPosC(); cout << endl;
  //  cout << (txt) << endl;  markErrorPosD(); cout << endl;
  //  cout << (txt) << endl;  markErrorPosE(); cout << endl;
}
