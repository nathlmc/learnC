#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/*
Exercise 4-11. Modify getop so that it doesn't need to use ungetch. Hint: use an internal static variable.
*/

int getop(char s[])
{
    int i, c, c2;
	static int extraChar = -1;	// Exercise 4-11

	if (extraChar != -1)	{
		c = extraChar;
		extraChar = -1;
	} 
	else 
    	c = getch();
	
	while ((s[0] = c) == ' ' || c == '\t')
    	c = getch();
	s[1] = '\0';
	i = 0;
	if (c == '-' && isdigit(c2 = getch()))	{	// Exercise 4-3. ...and provisions for negative numbers
		s[0] = c;
		s[1] = c2;
		i = 1;	// set to 1 as we later use a ++i to collect integer part
		c = c2;
	}
	else if (c == '-' && !isdigit(c2))
		extraChar = c2;				

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
				extraChar = c2;
				return VARIABLE;
			}
			extraChar = c2;
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
			extraChar = c2;	// push back extra character
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
		extraChar = c;
	return NUMBER;
}