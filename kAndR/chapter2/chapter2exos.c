#include <stdio.h>
#include <limits.h>
#include <float.h>

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

    return 0;
}