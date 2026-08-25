#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#define MAXLINE 1000    // maximum input line length

int strrindex(char source[], char searchfor[]); // Exercise 4-1
double atofextended(char s[]);  // Exercise 4-2
void recursiveitoa(int n, int i, char s[]); // Exercise 4-12

int main()
{


    char string1[] = "123.45e-6";
    printf("%.10f\n", atofextended(string1));
    char string2[] = "123.45e6";
    printf("%.10f\n", atofextended(string2));

    
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

void recursiveitoa(int n, int i, char s[]) // Exercise 4-12
/*
Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.
*/
{
    int static i = 0;   // Static. Only initialized once. Downside would be
                        // that future calls to recursiveitoa would not work            
    int sign, a;

    if ((sign = n) < 0) // record sign since working in reverse
        n = -n;
    
    if (n / 10) {
        if ((a = (n/= 10))) {
            recursiveitoa(a, s);
            
        }
            
    }
        recursiveitoa(n /= 10, s);
    
     
    if (!(n / 10))
        s[n] = n % 10 + '0';

}