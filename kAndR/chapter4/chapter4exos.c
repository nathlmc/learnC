#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#define MAXLINE 1000    // maximum input line length

int strrindex(char source[], char searchfor[]); // Exercise 4-1
double atofextended(char s[]);  // Exercise 4-2
int recursiveitoa(int n, int i, char s[]); // Exercise 4-12
void reverseHelper(char s[], int i, int j);
void reverse(char s[]);	// Exercise 4-13

int main()
{


	char string1[] = "123.45e-6";
	printf("%.10f\n", atofextended(string1));
	char string2[] = "123.45e6";
	printf("%.10f\n", atofextended(string2));

	/*
	// Exercise 4-12
	char test1[20];
	recursiveitoa(2, 0, test1);
	printf("Exercise 4-12\n%s", test1);

	recursiveitoa(-50000, 0, test1);
	printf("\n%s", test1);
	
	char test2[20];
	recursiveitoa(50000, 0, test2);
	printf("\n%s\n", test2);
	*/

	// Exercise 4-13
	char test1[] = "could";
	reverse(test1);
	printf("%s", test1);

	char test2[] = "";
	reverse(test2);
	printf("%s", test2);

	
	return 0;
}


int strrindex(char s[], char t[])   // Exercise 4-1
/*
Write the function strrindex(s,t), which returns the position of the rightmost occurerence of t in s, or -1 if there is none.
*/
{
	int i, j, k;
	for (i = strlen(s) - 1; i >= 0; i--)    {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

double atofextended(char s[])  // Exercise 4-2
/*
Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be
followed by e or E and an optionally signed exponent.
*/
{
	double val, power, exponent;
	exponent = 1.0;
	int i, sign, counter;
	counter = 0;

	for (i = 0; isspace(s[i]); i++) // skip white space
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++)   {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	if (((s[i] == 'e' || s[i] == 'E') && s[i + 1] != '\0')) {
		if (s[++i] == '-' && isdigit(s[i + 1])) {
			while (isdigit(s[++i]))
				counter = 10 * counter + (s[i] - '0');
			for (int j = 0; j < counter; j++)
				 exponent /= 10;
		}
		else if (isdigit(s[i])) {
			while (isdigit(s[++i]))
				counter = 10 * counter + (s[i] - '0');
			for (int j = 0; j < counter; j++)
				exponent *= 10;
		}
	}
	return (sign * val / power) * exponent;
}

int recursiveitoa(int n, int i, char s[]) // Exercise 4-12
/*
Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.
*/
{
	if (n < 0 && i == 0) {	// Weakness in method: requires empty array
		s[0] = '-';
		i++;
		n = -n;
	}
	
	if (n > 0) {	// If smaller than 0, no longer an int
		int a = recursiveitoa((n / 10), i+1, s);
		//printf("a is: %d\ti is: %d\tn is: %d\t", a,i,n);	
		s[a] = (n % 10) + '0';	// Use return to indicate position to subtract
		return a+1;
	}
	 
	else  {			
		s[i] = '\0';	
		if (s[0] == '-')
			return 1;
		else
			return 0;
	}        
}

void reverseHelper(char s[], int i, int j)
{
	if (i >= j)	// Base case, when i < j no longer true
		return;
	else	{
		int c = s[i];
		s[i] = s[j];
		s[j] = c;
		reverseHelper(s, ++i, --j);
	}
}

void reverse(char s[])	// Exercise 4-13
/*
Write a recursive version of the function reverse(s), which reverses the string
s in place
*/
{
	int a = strlen(s);
	if (a > 1)
		reverseHelper(s, 0, a - 1);
}