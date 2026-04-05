#include <stdio.h>

int binsearch(int x, int v[], int n); // binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
int altbinsearch(int x, int v[], int n);    // Exercise 3-1
void escape(char s[], char t[]);	// Exercise 3-2
void reverseescape(char s[], char t[]);	// Exercise 3-2

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

	// Exercise 3-1
	int example[] = {1,2,3,4,5,6};
	printf("%d is located at index %d\n", 4, altbinsearch(4, example, 6));

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