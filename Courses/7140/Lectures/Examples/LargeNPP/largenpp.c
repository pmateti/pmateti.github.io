
/*- 
 largenpp.c

 This file is a solution, with PRE and POST conditions, to
 Programming Assignment 3 of
 CS 240 Winter 96 

 pmateti@cs.wright.edu Feb 1996
 */

/* To students of CS 240:  Study this as an example of how well a program
   ought to be documented.  I am sure you-know-what-I-mean by such things
   as LEFT is-a-LargeNumber, RIGHT is-Unchanged. */

/* To programming pundits: This file is aimed at students of Freshman
   Computing (ACM's CS1).  If you find something here that is not
   well-definable, please let me know. */

#include <stdio.h>

/* Compute the minimum of two numbers. */

#define min(a, b) ((a) < (b)? (a) : (b))

#define ND 30			/* #digits in our "large numbers" */

/* 
   A large number is stored in an array of ND digits. [i]-th element
   stores the 10-power-i digit. */

char left[ND + 1];		/* the left operand */
char right[ND + 1];		/* the right operand */
char result[ND + 1];		/* the result of +- */
char ONE[ND + 1];		/* a 000000...00001 */
char op;			/* the operation to be performed */
int base = 16;			/* radix: 10 or 16 */

char hex[] = "0123456789ABCDEF";

/* 
   Reverse the string S of length N.  E.g., "hello" will become "olleh".

   PRE: none

   POST: S[i] == old-S[n - 1 - i], for 0 <= i <= n - 1 */

void reverse(char s[], int n)
{
	int i = 0, j = n - 1;
	char c;

	while (i < j) {
		/* exchange the i-th char with the j-th */
		c = s[j];
		s[j] = s[i];
		s[i] = c;

		i++;
		j--;
	}
}

int decimalDigit(char d)
{
	return ('0' <= d && d <= '9');
}

int hexUCDigit(char d)
{
	return ('A' <= d && d <= 'F');
}

int hexLCDigit(char d)
{
	return ('a' <= d && d <= 'f');
}

/* 
   PRE: none;

   POST: Return TRUE if and only if the character D is a digit between
   0..BASE */

int baseDigit(char d)
{
	return decimalDigit(d)
	    || ((base == 16) && (hexUCDigit(d) || hexLCDigit(d)));
}

/* 
   Convert the chars of X[0..N-1] to digits.  Fill the rest (N .. ND) with 
   zeros.

   PRE: The array X has digit characters in 0 .. N-1 positions. 

   POST: (old-X[i] == HEX[X[i]], for 0 <= i <= n-1)  && (X[i] == 0, for N
   <= i <= ND) */

void convertToDigits(char x[], int n)
{
	int i, d, e;

	/* convert from digit-chars to digits */
	for (i = 0; i < n; i++) {
		d = x[i];
		if (decimalDigit(d))
			e = -'0';
		else if (hexLCDigit(d))
			e = -'a' + 10;
		else		/* must be hexUCDigit(d) */
			e = -'A' + 10;
		x[i] = d + e;
	}

	/* zero-fill the rest */
	for (i = n; i < ND + 1; i++)
		x[i] = 0;	/* 0 not '\000' */
}

/* pseudo-code: RESULT = LEFT + RIGHT;

   PRE:  LEFT is-a-LargeNumber, RIGHT is-a-LargeNumber, RESULT
   can-be-a-LargeNumber;

   POST: RESULT is-a-LargeNumber, LEFT is-Unchanged, RIGHT is-Unchanged,
   RESULT == LEFT + RIGHT; */

void addNumbers(char result[], char left[], char right[])
{
	int sum, carry = 0, i;

	for (i = 0; i < ND; i++) {

		/* add the i-th digits */
		sum = left[i] + right[i] + carry;
		carry = 0;
		if (sum >= base) {
			sum -= base;
			carry = 1;
		}
		result[i] = sum;
	}

	result[ND] = carry;
}

/* Convert the NUM into its 9-or-15-s complement. 

   PRE: NUM is-a-LargeNumber

   POST: NUM == base-minus-1-Complement of old-NUM, NUM is-a-LargeNumber */

void ninesComplement(char num[])
{
	int i;

	for (i = 0; i < ND; i++)
		num[i] = (base - 1) - num[i];
}

/* Convert the NUM into its 10-or-16-s complement. 

   PRE: NUM is-a-LargeNumber

   POST: NUM == base-Complement-of old-NUM, NUM is-a-LargeNumber */

void tensComplement(char num[])
{
	ninesComplement(num);
	ONE[0] = 1;
	addNumbers(num, num, ONE);
	num[ND] = 0;		/* ignore carry, even if 1 */
}

/* pseudo-code: RESULT = LEFT  - RIGHT;

   PRE:  LEFT is-a-LargeNumber, RIGHT is-a-LargeNumber, RESULT
   can-be-a-LargeNumber;

   POST: RESULT is-a-LargeNumber, LEFT is-Unchanged, RIGHT is-Unchanged,
   RESULT == LEFT - RIGHT;

 */

void subNumbers(char result[], char left[], char right[])
{
	char cright[ND + 1];	/* complemented value of right[] */
	int i;

	for (i = 0; i <= ND; i++)
		cright[i] = right[i];
	tensComplement(cright);
	addNumbers(result, left, cright);
}

/* 
   pseudo-code: PRODUCT = LEFT D, where D is a one-digit number.

   PRE:  LEFT is-a-LargeNumber, 0 <= d <= base, PRODUCT
   can-be-a-LargeNumber;

   POST: PRODUCT is-a-LargeNumber, LEFT is-Unchanged, D is-Unchanged,
   PRODUCT == LEFT * D; */

void multOneDigit(char product[], char left[], int d)
{
	int i, p, carry = 0;

	for (i = 0; i < ND; i++) {
		p = left[i] * d + carry;
		carry = 0;
		if (p >= base) {
			carry = p / base;
			p = p % base;
		}
		product[i] = p;
	}
	product[ND] = carry;
}

/* pseudo-code: NUM = NUM base-power-F; 

   PRE:  NUM is-a-LargeNumber, 0 <= F;

   POST: NUM == old-NUM * (BASE ^ F), F is-Unchanged;

 */

void shiftHighDigits(char num[], int f)
{
	int i;

	for (i = ND; i >= f; i--)
		num[i] = num[i - f];
	for (i = f - 1; i >= 0; i--)
		num[i] = 0;
}

/* pseudo-code: PRODUCT = LEFT * RIGHT;

   PRE:  LEFT is-a-LargeNumber, RIGHT is-a-LargeNumber, PRODUCT
   can-be-a-LargeNumber;

   POST: PRODUCT is-a-LargeNumber, LEFT is-Unchanged, RIGHT is-Unchanged,
   PRODUCT == LEFT * RIGHT; */

void multNumbers(char product[], char left[], char right[])
{
	char semi[ND + 1];
	int i;

	/* product = 0; */
	for (i = 0; i < ND; i++)
		product[i] = 0;

	/* product = left mult right */
	for (i = 0; i < ND; i++) {
		multOneDigit(semi, left, right[i]);
		shiftHighDigits(semi, i);
		addNumbers(product, product, semi);
	}
}

/* 
   Get a rather large number into the array X.  The number is input as a
   sequence of digits ('0' ... '9'), preceded by an optional sign (-+).
   The sequence terminates when any non-digit is read. 

   PRE:  X can-be-a-LargeNumber;

   POST: X is-a-LargeNumber, X == integer-value-Input-by-User;

 */

void getLargeNumber(char x[])
{
	int i = -1;
	char c;

	printf("number: ");

	/* read the first char of the number: -+ or digit */
	scanf("%c", &c);

	if (baseDigit(c)) {
		/* read a digit, so make it part of the number */
		x[0] = c;
		i = 0;
	}
	/* read the number */
	do {
		i = min(i + 1, ND);	/* robustness */
		scanf("%c", &x[i]);
	}
	while (baseDigit(x[i]));

	reverse(x, i);
	convertToDigits(x, i);

	/* if a negative number, 10s complement it */
	if (c == '-')
		tensComplement(x);
}

/* 
   Get the operation OP to be performed on the left operand LEFT, and the
   right operand RIGHT.   

   PRE: none;

   POST: OP == char-value-Input-by-User;

 */

void getOperation()
{
	printf("operation [one of +-*]: ");
	scanf("%c", &op);
}

/* 

   PRE: none;

   POST: "operation " OP " is not done yet!\n" is-appended-to-Ouput */

void notDoneYet()
{
	printf("operation '%c' is not done yet!\n", op);
}

/* 
   pseudo-code: RESULT = LEFT OP RIGHT; 

   PRE:  LEFT is-a-LargeNumber, RIGHT is-a-LargeNumber, RESULT
   can-be-a-LargeNumber;

   POST: RESULT is-a-LargeNumber, LEFT is-Unchanged, RIGHT is-Unchanged,
   RESULT == LEFT OP RIGHT if OP is-in {'+', '-', '*'}, RESULT
   is-Unchanged if OP is-not-in {'+', '-', '*'}; */

void doIt()
{
	switch (op) {
	case '+':
		addNumbers(result, left, right);
		break;

	case '-':
		subNumbers(result, left, right);
		break;

	case '*':
		multNumbers(result, left, right);
		break;

	default:
		notDoneYet();
		break;
	}
}

/* Determine if NUM is negative.  If so, return '-'.  Otherwise, return
   '+'. 

   PRE:  NUM is-a-LargeNumber;

   POST: RETURN '-' if NUM < 0, RETURN '+' if NUM >= 0;

 */

char negative(char num[])
{
	char sign;
	int msd = num[ND - 1];	/* the most significant digit */

	if (msd < base/2)
		sign = '+';
	else
		sign = '-';
	return sign;
}

/* Print the string MSG, and then the ND digits of NUM. 

   PRE: NUM is-a-LargeNumber, MSG is-a-String;

   POST: char-representation-of NUM "\n" is-appended-to-Ouput, NUM
   is-Changed;

 */

void printNumber(char msg[], char num[])
{
	int i, leadingZeroes;
	char sign, c;

	printf("%s: ", msg);

	/* print the sign + or - of the num[] */
	sign = negative(num);
	if (sign == '-')
		tensComplement(num);
	printf("%c", sign);

	leadingZeroes = 1;
	for (i = ND - 1; i >= 0; i--) {
		if (4 == i % 5)
			printf(" ");

		/* the digit char to be printed */
		c = hex[num[i]];

		/* suppress leading zeroes */
		if (c == '0' && i > 0) {
			if (leadingZeroes)
				c = ' ';
		} else
			leadingZeroes = 0;

		printf("%c", c);
	}
	printf("\n");
}

/* 

   PRE:  LEFT is-a-LargeNumber, RIGHT is-a-LargeNumber, RESULT
   is-a-LargeNumber;

   POST: "\n" "left  " char-representation-of LEFT "\n" "right "
   char-representation-of RIGHT "\n" "op    " OP "\n" "result"
   char-representation-of RESULT "\n" is-appended-to-Ouput

 */

void printAnswer()
{
	printf("\n");
	printNumber("left  ", left);
	printf     ("op    : %c\n", op);
	printNumber("right ", right);
	printNumber("result", result);
}

/* 

   PRE: LEFT can-be-a-LargeNumber, RIGHT can-be-a-LargeNumber, RESULT
   can-be-a-LargeNumber;

   POST: "\n" "left  " char-representation-of LEFT "\n" "right "
   char-representation-of RIGHT "\n" "op    " OP "\n" "result"
   char-representation-of RESULT "\n" is-appended-to-Ouput

 */

int main()
{

	printf("base [D for decimal, or X for hex]:");
	base = (getchar() == 'X'? 16 : 10);
	printf("Ok, base set to %d\n", base);

	printf("Now, give the two operands, followed by the op-code [+-*/]\n");

	getLargeNumber(left);
	getLargeNumber(right);
	getOperation();

	doIt();

	printAnswer();

	return 0;
}

/* -eof- */
