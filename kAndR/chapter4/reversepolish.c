#include <stdio.h>
#include <stdlib.h> // for atof()
#include <ctype.h>

#define MAXOP   100 // max size of operand or operator
#define MAXVAL	100 // maximum depth of val stack
#define NUMBER  '0' // signal that a number was found
#define BUFSIZE	100

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);
void peek(void);		// Exercise 4-4, top elem of the stack
void duplicate(void);	// Exercise 4-4, duplicate top elem of the stack
void swap(void);		// Exercise 4-4, swap top two elems
void clear(void);		// Exercise 4-4, clear stack

int sp = 0;			// next free stack position
double val[MAXVAL];	// value stack
char buf[BUFSIZE];	// buffer for ungetch
int bufp = 0;		// next free position in buf

/*
Exercise 4-4. 
Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top two elements. 
Add a command to clear the stack.
*/

// reverse Polish calculator
int main()
{
	int type, op3, op4;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF)    {
		switch (type)   {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':	// - and /, left and right ops must be distinguished so use op2 var
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero division\n");
				break;
			case '%':	// Exercise 4-3 Add modulus operator and...
				op3 = (int) pop();
				op4 = (int) pop();
				if (op3 != 0)
					push(op4 % op3);
				else
					printf("error: zero division\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			case 'p':	// peek at top element
				peek();
				break;
			case 'd':	// duplicate top element
				duplicate();
				break;
			case 's':	// swap top two elements
				swap();
				break;
			case 'c':
				clear();
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

// push: push f onto value stack
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value from stack
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getop(char s[])	// getop: get next operator or numeric operand
{
	int i, c, c2;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	i = 0;
	if (c == '-' && isdigit(c2 = getch()))	{	// Exercise 4-3. ...and provisions for negative numbers
		s[0] = c;
		s[1] = c2;
		i = 1;	// set to 1 as we later use a ++i to collect integer part
		c = c2;
	}
	else if (c == '-' && !isdigit(c2))
		ungetch(c2);				

	if (!isdigit(c) && i < 2 && c != '.')	{
		return c;	// not a number
	}
	if (isdigit(c))	// collect integer part
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	// collect fraction part
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
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


void peek(void)		// Exercise 4-4, top elem of the stack
{
	if (sp > 0)
		printf("Top of stack:%f\n", val[sp - 1]);
	else
		printf("Stack is empty\n");
}

void duplicate(void)	// Exercise 4-4, duplicate top elem of the stack
{
	if (sp > 0)	{
		val[sp] = val[sp - 1];
		sp++;
	}
	else
		printf("Stack is empty\n");
}

void swap(void)		// Exercise 4-4, swap top two elems
{
	double a;
	if (sp > 1)	{
		a = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = a;
	}
	else
		printf("Stack does not have enough elements to swap\n");
}

void clear(void)		// Exercise 4-4, clear stack
{
	while (sp > 0)	{
		val[sp] = 0.0;
		sp--;
	}
	printf("Stack cleared\n");
}