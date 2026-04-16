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
#define MAXLINE	100	//Exercise 4-10. Max line length

int getop(char s[], char t[]);
void push(double);
double pop(void);
void peek(void);		// Exercise 4-4, top elem of the stack
void duplicate(void);	// Exercise 4-4, duplicate top elem of the stack
void swap(void);		// Exercise 4-4, swap top two elems
void clear(void);		// Exercise 4-4, clear stack
int getline(char s[], int lim);
int nextchar(char s[]);		// Similar to getch

int position = 0;	// Exercise 4-10, keeps track of position in line 
char s[MAXLINE];	// Exercise 4-10, line.
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

/*
Exercise 4-10.
An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. 
Revise the calculator to use this approach.
*/

// reverse Polish calculator
int main()
{
	int type, op3, op4;
	double op2;
	s[position] = '\0';	// Initialize
	char t[MAXOP];
	
	while ((type = getop(s, t)) != EOF)    {
		switch (type)   {
			case NUMBER:
				push(atof(t));	// TODO
				break;
			case FUNCTION:
				if (strcmp(t, "sin") == 0)
					push(sin(pop()));
				else if (strcmp(t, "exp") == 0)
					push(exp(pop()));
				else if (strcmp(t, "pow") == 0)	{	// Domain error occurs if x = 0 and y <= 0, or if x < 0 and y is not an integer
					op2 = pop();
					push(pow(pop(), op2));
				}
				else if (strcmp(t, "ans") == 0)	// Exercise 4-6. Last printed value
					push(lastprinted);
				break;
			case VARIABLE:	// Exercise 4-6. If user inputted a variable
				push(variables[t[0] - 'A']);
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
				variables[t[1] - 'A'] = pop();
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
				printf("error: unknown command %s\n", t);
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

int getop(char s[], char t[])	// getop: get next operator or numeric operand
{
	int i, c, c2;

	if (s[position] == '\0')	{	// get new line, reset position if previous line fully read
		position = 0;
		getline(s, MAXLINE);
	}

	if (s[position] == '\0')	// Reached EOF
		return EOF;

	while ((t[0] = c = (nextchar(s))) == ' ' || c == '\t')
		;

	i = 0;	// Reset i so array t is reset
	t[1] = '\0';

	if (c == '-' && isdigit(c2 = nextchar(s)))	{	// Exercise 4-3. ...and provisions for negative numbers
		t[0] = c;
		t[1] = c2;
		i = 1;	// set to 1 as we later use a ++i to collect integer part
		c = c2;
	}
	else if (c == '-' && !isdigit(c2))
		position--;				

	if (!isdigit(c) && i < 2 && c != '.')	{
		if (c == '\n')	
			return '\n';
		if (c == EOF)
			return EOF;
		c2 = nextchar(s);
		if (!isalpha(c2))	{
			if (c >= 'A' && c <= 'Z')	{	// Exercise 4-6
				t[0] = c;
				t[1] = '\0';
				position--;
				return VARIABLE;
			}
			position--;
			return c;	// not a number, one char op
		}
		else if (c == '=' && (c2 >= 'A' && c2 <= 'Z'))	{	// variable assignment case
			t[0] = c;
			t[1] = c2;
			t[2] = '\0';
			return '=';
		}
		else	{	// Exercise 4-5
			t[i] = tolower(c);
			t[++i] = tolower(c2);
			while (isalpha(c2 = nextchar(s)))
				t[++i] = tolower(c2);
			position--;	// push back extra character
			t[++i] = '\0';
			return FUNCTION;
		}
	}
	if (isdigit(c))	// collect integer part
		while (isdigit(t[++i] = c = nextchar(s)))
			;
	if (c == '.')	// collect fraction part
		while (isdigit(t[++i] = c = nextchar(s)))
			;
	t[i] = '\0';
	if (c != EOF)
		position--;
	return NUMBER;
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


// getline: get line into s, return length from chapter4.c
int getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int nextchar(char s[])		// Similar to getch
{
	if (s[position] != '\0')
		return s[position++];
	else
		return '\0';
}