#include <stdio.h>
#include <string.h>
#include <limits.h>

int binsearch(int x, int v[], int n); // binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
int altbinsearch(int x, int v[], int n);    // Exercise 3-1
void escape(char s[], char t[]);	// Exercise 3-2
void reverseescape(char s[], char t[]);	// Exercise 3-2
int atoi(char s[]);	// atoi: convert s to integer; version 2 (see chap 2)
void shellsort(int v[], int n);	// shellsort: sort v[0]...v[n-1] into increasing order
void reverse(char s[]);	// reverse string s in place
void expand(char s1[], char s2[]);	// Exercise 3-3
void itoa(int n, char s[]);	// itoa: convert n to characters in s
void itoatwo(int n, char s[]); // Exercise 3-4
void itob(int n, char s[], int b);	// Exercise 3-5
void itoathree(int n, char s[], int width);	// Exercise 3-6

int main()
{
	/*
	int c, i, nwhite, nother, ndigit[10];

	nwhite = nother = 0;
	for (i = 0; i < 10; i++)
		ndigit[i] = 0;

	while ((c = getchar()) != EOF)	{
		switch(c)	{
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				// Fall through allows several cases to be attached to a single action
				ndigit[c-'0']++;
				break;
			case ' ':
			case '\n':
			case '\t':
				nwhite++;
				break;
			default:
				nother++;
				break;	// Good form, defensive programming. Logically unnecessary
		}
	}
	printf("digits =");
	for (i = 0; i < 10; i++)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n", nwhite, nother);
	*/

	/*
	// Exercise 3-1
	int example[] = {1,2,3,4,5,6};
	printf("%d is located at index %d\n", 4, altbinsearch(4, example, 6));
	*/

	/*
	// Exercise 3-2
	char string1[] = "hello\nhow are you?";
	char string2[30];
	escape(string2, string1);
	for (int i = 0; string2[i] != '\0'; i++)
    	printf("%d ", string2[i]);
	printf("\n");
	
	reverseescape(string2, string2);

	for (int i = 0; string1[i] != '\0'; i++)
    	printf("%d ", string1[i]);
	printf("\n");
	for (int i = 0; string2[i] != '\0'; i++)
    	printf("%d ", string2[i]);
	printf("\n");
	*/
	/*
	// Exercise 3-3

	// Normal string with no expansion
	char string1[] = "a-b-c";
	char string2[100];
	expand(string1, string2);

	printf("%s\n", string2);

	// Simple expansion
	char string3[] = "A-z";
	expand(string3, string2);
	printf("%s\n", string2);

	// Expansion 
	char string4[] = "a-z0-9";
	expand(string4, string2);
	printf("%s\n", string2);

	// Prefix/suffix expand examples
	char string5[] = "-a";
	expand(string5, string2);
	printf("%s\n", string2);

	char string6[] = "a-";
	expand(string6, string2);
	printf("%s\n", string2);

	char string7[] = "-a-z";
	expand(string7, string2);
	printf("%s\n", string2);
	*/
	/*
	// Exercise 3-4
	int a = INT_MIN;
	char string1[20];
	itoatwo(a, string1);
	printf("%s", string1);
	*/
	/*
	// Exercise 3-5
	// Check first if same result as itoatwo
	int a = INT_MIN;
	char string1[20];
	itob(a, string1, 10);
	printf("%s\n", string1);
	itob(a, string1, 16);
	printf("%s\n", string1);
	itob(a, string1, 8);
	printf("%s\n", string1);
	itob(a, string1, 2);
	printf("%s\n", string1);


	a = -378;	// Random number 
	itob(a, string1, 16);
	printf("%s\n", string1);
	itob(a, string1, 8);
	printf("%s\n", string1);
	itob(a, string1, 2);
	printf("%s\n", string1);
	*/

	// Exercise 3-6
	int a = 150;
	char string1[20];
	itoathree(a, string1, 20);
	printf("%s\n", string1);
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low + high)/2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    // found match
            return mid;
    }
    return -1;  // no match        
}

int altbinsearch(int x, int v[], int n)
// Exercise 3-1 Our binary search makes two tests inside the loop, when one would suffice
// (at the price of more tests outside). Write a version with only one test inside the loop
// and measure the difference in run-time
{
	int low, high, mid;
	low = 0;
	high = n-1;
	while (low < high)	{
		mid = (low + high)/2;
		if (x > v[mid])
			low = mid + 1;
		else
			high = mid;
	}
	if (x == v[low])
		return mid;
	return -1;
}

void escape(char s[], char t[])
/*
Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies string t to s. Use a switch. Write
a function for the other direction as well, converting escape sequences into the real characters.
*/
{
	int i, j;
	i = j = 0;
	while (t[i] != '\0')	{
		switch(t[i])	{
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j] = t[i];
				j++;
				break;
		}
		i++;
	}
	s[j] = '\0';
}

void reverseescape(char s[], char t[])
// Exercise 3-2 part 2; assumes only \n and \t
{
	int i, j;
	i = j = 0;
	while (t[i] != '\0')	{
		switch(t[i])	{
			case '\\':
				if (t[i+1] == 'n')
					s[j] = '\n';
				else
					s[j] = '\t';
				i++;
				break;
			default:
				s[j] = t[i];
				break;
		}
		i++;
		j++;
	}
	s[j] = '\0';
}

int atoi(char s[])	// atoi: convert s to integer; version 2 (see chap 2)
{
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++)	// skip white space
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')	// skip sign
		i++;
	for (n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');
	return sign * n;
}

void shellsort(int v[], int n)	// shellsort: sort v[0]...v[n-1] into increasing order
{
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0 && v[j] > v[j+gap]; j -= gap)	{
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}

void reverse(char s[])	// reverse string s in place
{
	int c, i, j;
	// Use of comma operator
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		// Alternatively: c = s[i], s[i] = s[j], s[j] = c;
	}
}

void expand(char s1[], char s2[])
/*
Exercise 3-3. Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into the
equivalent complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle
cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
*/
{
	int loopstart, loopend, i, j;
	loopend = 0;	
	for (i = 0, j = 0; s1[i] != '\0'; i++, j++)	{
		if (s1[i] == '-')
			loopend = s1[i + 1] != '\0'? s1[i + 1] : 'z' + 1;	// find the end if it exists
		if (loopend)	{
			loopstart = i - 1 >= 0 ?  (s1[i - 1] + 1) : '0'; // set start to character before -, check if in range of array
			for (; loopstart < loopend; loopstart++, j++)
				s2[j] = loopstart;
			loopend = 0;	// reset loopend to 0
			--j;	// counteract the extra j++
		}
		else
			s2[j] = s1[i];
	}
	s2[j] = '\0';
}

void itoa(int n, char s[]) // itoa: convert n to characters in s
{
	int i, sign;

	if ((sign = n) < 0)	// record sign
		n = -n;
	i = 0;
	do
	{	// generate digits in reverse order
		s[i++] = n % 10 + '0';	// get next digit
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void itoatwo(int n, char s[])
// Exercise 3-4
/*
Exercise 3-4. In a two's complement number representation, our version of itoa does not handle the largest negative number, 
that is, the value of n equal to -2(^(wordsize-1)). Explain why not. Modify it to print that value correctly, regardless of 
the machine on which it runs.
ANSWER: Since it is two's complement, the INT_MIN will hvae the property abs(INT_MIN) = abs(INT_MAX) + 1. So n = -n of itoa
would have an overflow. We modify by dealing with the special case.
*/
{
	int i, sign;
	i = 0;
	if ((sign = n) < 0)	{	// record sign
		if ((n == INT_MIN))	{	//
			s[i++] = - (n % 10) + '0';
			n /= 10;
		}
		n = -n;
	}
	do
	{	// generate digits in reverse order
		s[i++] = n % 10 + '0';	// get next digit
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void itob(int n, char s[], int b)
// Exercise 3-5. 
/*
Write the function itob(n,s,b) that converts the integer n into a base b character representation in the
string s. In particular, itob(n,s,16) formats n as a hexadecimal integer in s.
*/
{
	int i, sign, digit;
	// TODO: Implement for b in (10;16) -> (A;F)
	i = 0;
	

	if ((sign = n) < 0)	{	// record sign
		if ((n == INT_MIN))	{
			digit = n % b;
			if (digit < 10 || b <= 10)	{
				s[i++] = -(digit) + '0';
			}
			else	{
				s[i++] = -(digit) - 10 + 'a';
			}
			n /= b;
		}
		n = -n;
	}
	
	do
	{	// generate digits in reverse order
		digit = n % b;
		s[i++] = digit < 10 ? digit + '0' : digit - 10 + 'a';	// get next digit
	} while ((n /= b) > 0);
	
	// End by checking cases with special notation:
	switch (b)	{
		case 16:
			s[i++] = 'x';
			s[i++] = '0';
			break;
		case 8:
			s[i++] = '0';
			break;
		case 2:
			s[i++] = 'b';
			s[i++] = '0';
			break;
	}

	if (sign < 0)
		s[i++] = '-';


	s[i] = '\0';
	reverse(s);
	
}

void itoathree(int n, char s[], int width)
// Exercise 3-6
/*
Write a version of itoa that accepts three arguments instead of two. The third argument
is a minimum field width; the converted number must be padded with blanks on the left if
necessary to make it wide enough.
*/
{
	int i, sign;
	i = 0;
	if ((sign = n) < 0)	{	// record sign
		if ((n == INT_MIN))	{	//
			s[i++] = - (n % 10) + '0';
			n /= 10;
		}
		n = -n;
	}
	do
	{	// generate digits in reverse order
		s[i++] = n % 10 + '0';	// get next digit
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	// Technically, we could use itoatwo and then done int i = strlen(s);
	while (i < width)
		s[i++] = ' '; 

	s[i] = '\0';

	reverse(s);
}