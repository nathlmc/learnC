#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[])
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