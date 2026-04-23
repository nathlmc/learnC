#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>	// for strcmp()
#include "calc.h"
#define MAXOP 100

double variables[26];	// variables. Exercise 4-6. Index would be s[0] - 'A'.
double lastprinted = 0.0;	// store recently printed value
int pushback = -2;		// buffer for pushback

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