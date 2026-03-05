#include <stdio.h>

int power(int m, int n);
int fahrToCelsius(int fahr);
int power2(int base, int n);

// test power function
int main()
{
    /*
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2,i), power(-3,i));
    */

    return 0;
}

// power: raise base to n-th power; n >= 0
int power(int base, int n)
{
    int i, p;

    p = 1;
    for (i = 1; i <= n; ++i)
        p = p * base;
    return p;
}

// Exercise 1-15 fahrToCelsius: converts fahrenheit argument to celsius
int fahrToCelsius(int fahr)
{
    return 5 * (fahr-32) / 9;
}

// Function arguments are passed by value. Here n would be a copy
// Different for arrays however. Arrays' first addr would be passed directly
int power2(int base, int n)
{
    int p;

    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}