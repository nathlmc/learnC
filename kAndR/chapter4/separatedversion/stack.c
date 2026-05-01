#include <stdio.h>
#include "calc.h"
#define MAXVAL  100

static int sp = 0;
static double val[MAXVAL];

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