#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <math.h>

int atoi(char s[]); // atoi: convert s to integer --> char to int conversion example
int lower(int c);
int htoi(char s[]); // htoi: convert string of hex to equivalent int value

int main()
{
    // Exercise 2-1 Determine ranges of char, short, int, and long vars (signed and unsigned.) from headers and direct
    // computation Det ranges of variious floating-point types
    printf("Range of char: %d to %d\t and unsigned char 0 to %d\n", SCHAR_MIN, SCHAR_MAX, UCHAR_MAX);
    // Rest follows similar pattern. See K&R page 257

    int sizeOfChar = sizeof(char) * 8;
    int n = 1;
    for (int i = 0; i < sizeOfChar; ++i) // Can simplify with shifting (not learned yet)
        n *= 2;
    printf("Range of char: %d to %d\t and unsigned char 0 to %d\n", -(n / 2), n / 2 - 1, n - 1);

    enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JULY,AUG, SEP, OCT, NOV, DEC};
    enum months january = 99; // allowed despite not being a valid value for the enumeration, enums are just integers under the hood

    // Exercise 2-2 Write a loop equivalent to the for loop above without using && or ||
    /*
    int c, i, lim;
    char s[10];
    lim = 10;
    // for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c!= EOF; ++i) Original
    //     s[i] = c;

    int loopCheck = 1;
    while (loopCheck) {
        c = getchar();
        if (c == '\n')
            loopCheck = 0;
        else if (c == EOF)
            loopCheck = 0;
        else if (i >= lim - 1)
            loopCheck = 0;
        if (loopCheck) {
            s[i] = c;
            ++i;
        }
    }
    */

    // Exercise 2-3 Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X)
    printf("%d\n", htoi("1"));
    printf("%d\n", htoi("0x1"));
    printf("%d\n", htoi("0X1"));
    printf("%d\n", htoi("A"));
    printf("%d\n", htoi("F"));
    printf("%d\n", htoi("0x45A3e9"));

    return 0;
}

int atoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

unsigned long int next = 1;

// rand: return pseudo-random integer on 0..32767
int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

// srand: set seed for rand()
void srand(unsigned int seed)
{
    next = seed;
}

int htoi(char s[]) // Exercise 2-3 Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X)
{
    /*
    // Version 1. Worse. O(n^2) plus extra ops
    int i, n;

    i = 0;
    while (s[i] != '\0') // find length of s
        ++i;

    printf("Length of string: %d\n", i);
    i-= 1;
    n = 0;
    for (int j = 0; s[j] != '\0'; ++j)  {
        if (s[j] >= '0' && s[j] <= '9')
            n += pow(16, i) * (s[j] - '0');
        else if (s[j] >= 'A' && s[j] <= 'F') 
            n += pow(16, i) * (s[j] - 'A' + 10);
        else if (s[j] >= 'a' && s[j] <= 'f')
            n += pow(16, i) * (s[j] - 'a' + 10);
        --i;
    }
    */ 

    int i, n;
    i = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        i = 2;
    
    n = 0;

    for (; s[i] != '\0'; ++i)   {
        if (s[i] >= '0' && s[i] <= '9')
            n = 16 * n + (s[i] - '0');
        else if (s[i] >= 'A' && s[i] <= 'F') 
            n = 16 * n + (s[i] - 'A' + 10);
        else if (s[i] >= 'a' && s[i] <= 'f')
            n = 16 * n + (s[i] - 'a' + 10);
    }

    return n;
}