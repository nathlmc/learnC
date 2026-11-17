#include <stdio.h>
#include <ctype.h>
#define BUFSIZE	100

void swap(int *px, int *py);	// interchange *px and *py
int getch(void);
void ungetch(int c);
int getint(int *pn);	// getint: get next integer from input into *pn

int buf[BUFSIZE];	// buffer for ungetch. Exercise 4-9: char buf[BUFSIZE] -> int buf [BUFSIZE]
int bufp = 0;		// next free position in buf

int main()
{
	/*
	int x = 1, y = 2, z[10];
	int *ip;    // ip is a pointer to int

	ip = &x;    // ip now points to x
	y = *ip;    // y is now 1
	*ip = 0;	// x is now 0
	ip = &z[0];	// ip now points to z[0]
	*/

	int n, status;
	while ((status = getint(&n)) != EOF)
		if (status > 0)
			printf("got %d\n", n);
		else
			getch();


	return 0;
}

void swap(int *px, int *py)	// interchange *px and *py
{
	int temp;
	
	temp = *px;
	*px = *py;
	*py = temp;
}

int getch(void)	// get a (possibly pushed back) character
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)	// push character back on input
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

// Getch and ungetch from Chapter 4

int getint(int *pn)	// getint: get next integer from input into *pn
{
	int c, sign;

	while (isspace(c = getch()))	// skip white space
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')	{
		ungetch(c);	// it's not a number
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')	{
		int c2 = c;
		c = getch();		
		if (!isdigit(c) && c != EOF)	{
			ungetch(c);
			ungetch(c2);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}