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
    return 0;
}