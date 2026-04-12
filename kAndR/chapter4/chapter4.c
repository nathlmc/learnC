#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#define MAXLINE 1000    // maximum input line length

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);
double atof(char s[]);  // atof: convert string s to double
int atoi(char s[]);  // atoi: convert string s to integer using atof

char pattern[] = "ould";    // pattern to search for

// find all lines matching pattern
int main()
{
    /*
    char line[MAXLINE];
    int found = 0;

    while (getline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0)   {
            printf("%s", line);
            found++;
        }
    return found;
    */

    /*
    double sum; // K&R also delcares atof(char s[]) on this line but we already declared it at the start
    // !! if we do not declare, assumed to return int and no assumptions on arguments !!
    // If function takes args, declare them, if none, use void return type
    char line[MAXLINE];
    // int getline(char line[], int max);  // Again, this line is unnecessary for reason above. K&R does this way though
    
    sum = 0;
    while (getline(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));

    */

    return 0;
}

// getline: get line into s, return length
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

// strindex: return index of t in s, -1 if none
int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++)  {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

double atof(char s[])  // atof: convert string s to double
{
    double val, power;
    int i, sign;

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
    return sign * val / power;
}

int atoi(char s[])  // atoi: convert string s to integer using atof
{
    // double atof(char s[]); // Not necessary for reasons above. K&R does this way though
    // Writing atoi in terms of atof
    return (int) atof(s);
    // Technically, (int) not needed as return converts to type of function. Cast states explicitly
    // it's intended, suppresses any warning
}
