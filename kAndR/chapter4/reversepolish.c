#include <stdio.h>
#include <stdlib.h> // for atof()
#include <ctype.h>
#include <math.h>
#include <string.h>	// for strcmp()

#define MAXOP   100 // max size of operand or operator
#define MAXVAL	100 // maximum depth of val stack
#define NUMBER  '0' // signal that a number was found
#define BUFSIZE	100
#define FUNCTION 'f'	// Exercise 4-5	
#define VARIABLE 'A'

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);
void peek(void);		// Exercise 4-4, top elem of the stack
void duplicate(void);	// Exercise 4-4, duplicate top elem of the stack
void swap(void);		// Exercise 4-4, swap top two elems
void clear(void);		// Exercise 4-4, clear stack
void ungets(char s[]);	// Exercise 4-7, push back entire string onto the input
int getchtwo(void);		// Exercise 4-8
void ungetchtwo(int);	// Exercise 4-8

int sp = 0;			// next free stack position
double val[MAXVAL];	// value stack
int buf[BUFSIZE];	// buffer for ungetch. Exercise 4-9: char buf[BUFSIZE] -> int buf [BUFSIZE]
int bufp = 0;		// next free position in buf
double variables[26];	// variables. Exercise 4-6. Index would be s[0] - 'A'.
double lastprinted = 0.0;	// store recently printed value
int pushback = -2;		// buffer for pushback

/*
Exercise 4-4. 
Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top two elements. 
Add a command to clear the stack.
*/

/*
Exercise 4-5.
Add access to library functions like sin, exp, and pow. See <math.h> in Appendix B, Section 4.
*/

/*
Exercise 4-6.
Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.)
Add a variable for the most recently printed value.

--> We treat variables as between A - Z. If there's an invalid input, say 3 =a 4 =b a b +, =a and =b are 
ignored, a b treated as invalid commands. So would parse as 3 4 +.
*/

/*
Exercise 4-7.
Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf
and bufp, or should it just use ungetch?

Just use ungetch. Technically could do same thing I did with stack (which I technically shouldn't have done)
but better to abstract implementation.
*/

/*
Exercise 4-8.
Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.
-> Keeping getch and ungetch. Adding getchtwo and ungetchtwo.
*/

/*
Exercise 4-9.
Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to be if 
an EOF is pushed back, then implement your design.

char could be signed depending on machine --> EOF can be out of range. So change from char to either signed char
or int.
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
			case FUNCTION:
				if (strcmp(s, "sin") == 0)
					push(sin(pop()));
				else if (strcmp(s, "exp") == 0)
					push(exp(pop()));
				else if (strcmp(s, "pow") == 0)	{	// Domain error occurs if x = 0 and y <= 0, or if x < 0 and y is not an integer
					op2 = pop();
					push(pow(pop(), op2));
				}
				else if (strcmp(s, "ans") == 0)	// Exercise 4-6. Last printed value
					push(lastprinted);
				break;
			case VARIABLE:	// Exercise 4-6. If user inputted a variable
				push(variables[s[0] - 'A']);
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
			case '=':	// Exercise 4-6 We take this to mean variable assignment
				variables[s[1] - 'A'] = pop();
				break;
			case '\n':
				lastprinted = pop();
				printf("\t%.8g\n", lastprinted);
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
		if (c == '\n')
			return '\n';
		if (c == EOF)
			return EOF;
		c2 = getch();
		if (!isalpha(c2))	{
			if (c >= 'A' && c <= 'Z')	{	// Exercise 4-6
				s[0] = c;
				s[1] = '\0';
				ungetch(c2);
				return VARIABLE;
			}
			ungetch(c2);
			return c;	// not a number, one char op
		}
		else if (c == '=' && (c2 >= 'A' && c2 <= 'Z'))	{	// variable assignment case
			s[0] = c;
			s[1] = c2;
			s[2] = '\0';
			return '=';
		}
		else	{	// Exercise 4-5
			s[i] = tolower(c);
			s[++i] = tolower(c2);
			while (isalpha(c2 = getch()))
				s[++i] = tolower(c2);
			ungetch(c2);	// push back extra character
			s[++i] = '\0';
			return FUNCTION;
		}
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

void ungets(char s[])	// Exercise 4-7, ungets
{
	int i = strlen(s) - 1;	// Exclude null terminator
	while (i >= 0)
		ungetch(s[i--]);
}

int getchtwo(void)	// Exercise 4-8, get a (possibly pushed back) character
{	// Note: use int since EOF is -1. 
	if (pushback != -2)	{
		int new = pushback;
		pushback = -2;	// reset to no pushed backs
		return new;
	}
	else
		return getchar();
}

void ungetchtwo(int c)	// Exercise 4-8, push character back
{
	if (pushback == -2)	// there is space
		pushback = c;
	else	{
		printf("Ungetch: There is already a character pushed back");
	}
}