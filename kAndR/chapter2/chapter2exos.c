#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <math.h>

int atoi(char s[]); // atoi: convert s to integer --> char to int conversion example
int lower(int c);
int htoi(char s[]); // htoi: convert string of hex to equivalent int value
void squeeze(char s[], int c); // squeeze: delete all c from s
void strcat(char s[], char t[]); // concatenate t to end of s; s must be big enough. Std library ver rets a pointer to resing str
void altsqueeze(char s1[], char s2[]); // Exercise 2-4, alt ver of squeeze. dels each char in s1 that matches any char in s2
int any(char s1[], char s2[]);  // Exercise 2-5, returns first location in s1 where any char from s2 occurs, -1 if none
unsigned getbits(unsigned x, int p, int n); // getbits: get n bits from position p
unsigned setbits(unsigned x, int p, int n, unsigned y); // Exercise 2-6
unsigned invert(unsigned x, int p, int n); // Exercise 2-7
unsigned rightrot(unsigned x, int n); // Exercise 2-8

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
    /*
    // Exercise 2-3 Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X)
    printf("%d\n", htoi("1"));
    printf("%d\n", htoi("0x1"));
    printf("%d\n", htoi("0X1"));
    printf("%d\n", htoi("A"));
    printf("%d\n", htoi("F"));
    printf("%d\n", htoi("0x45A3e9"));
    */
    /*
    // Exercise 2-4 Write an alt ve of squeeze that deletes each character in s1 that matches any character in the string s2
    char s1[] = "Geeks are cool";
    char s2[] = "Geeks";
    altsqueeze(s1, s2);
    printf("%s\n", s1);
    */
    /*
    // Exercise 2-5 Write the function any(s1, s2), which returns the first loc in s1 where any char from s2 occurs, or -1 if none
    char s1[] = "Geeks are cool";
    char s2[] = "Geeks";
    char s3[] = "abc";
    char s4[] = "def";
    printf("%s and %s are similar at: %d (not same if -1)\n", s1, s2, any(s1, s2));
    printf("%s and %s are similar at: %d (not same if -1)\n", s3, s4, any(s3, s4));
    */
    /*
    // Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p 
    // set to the rightmost n bits of y, leaving the other bits unchanged.
    unsigned x = 0b11011000;  // 216 in decimal
    unsigned y = 0b01110001;  // 113 in decimal
    printf("result: %u\n", setbits(x, 3, 2, y));
    */
    /*
    // Exercise 2-7. Exercise 2-7. Write a function invert(x,p,n) that returns x with the 
    // n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.

    // All zeros, invert 3 bits at position 3
    // x = 00000000, should get 00001110 = 14
    printf("%u\n", invert(0b00000000, 3, 3));

    // All ones, invert 3 bits at position 3  
    // x = 11111111, should get 11110001 = 241
    printf("%u\n", invert(0b11111111, 3, 3));

    // Mixed
    // x = 11001010, invert bits at positions 3,2,1
    // should get 11000100
    printf("%u\n", invert(0b11001010, 3, 3));
    */

    // Exercise 2-8
    // Exercise 2-8. Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions.
    // Rotate by 1, rightmost bit wraps to top
    // x = 00000001, should get 10000000...0 (1 shifted to MSB)
    printf("%u\n", rightrot(0b00000001, 1));

    // Rotate by 1
    // x = 11001010, should get 01100101
    printf("%u\n", rightrot(0b11001010, 1));

    // Rotating by word size should give back original
    // x = 11001010, rotate by 32 should give 11001010
    printf("%u\n", rightrot(0b11001010, 32));

    // Rotate by 0 should give back original
    printf("%u\n", rightrot(0b11001010, 0));
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

void squeeze(char s[], int c) // squeeze: delete all c from s
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
            // equivalent to s[j] = s[i]; j++;
    s[j] = '\0';
}

void strcat(char s[], char t[]) // concatenate t to end of s; s must be big enough. Std library ver rets a pointer to resing str
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')    // find end of s
        i++;
    while ((s[i++] = t[j++]) != '\0') // copy t
        ;
}

void altsqueeze(char s1[], char s2[]) // Exercise 2-4, alt ver of squeeze. dels each char in s1 that matches any char in s2
{
    int i, j, k;
    
    for (i = j = 0; s1[i] != '\0'; i++) {
        int check = 0;
        for (k = 0; s2[k] != '\0'; k++)
            if (s1[i] == s2[k]) {
                check = 1;
                break;
            }
        if (check == 0)
            s1[j++] = s1[i];
    }
                
    s1[j] = '\0';
}

int any(char s1[], char s2[])  // Exercise 2-5, returns first location in s1 where any char from s2 occurs, -1 if none
{
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i;
    }
    return -1;
}

unsigned getbits(unsigned x, int p, int n) // getbits: get n bits from position p
{
    return (x >> (p+1-n)) & ~(~0u << n);
    // K&R uses ~0. ~0 produces a signed int with all bits set, which is a negative value, 
    // and left shifting a negative value is undefined behavior in C. We use ~0u instead, which makes it unsigned
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
// Exercise 2-6, returns x with n bits that begin at position p set to rightmost n bits of y, leaving other bits unchanged
{
    return (x & ~(~(~0u << n) << (p+1-n))) | (y & ~(~0u << n)) << (p+1-n);
    // (clear n bits in x at p) (use mask that we shift to correct position) 
    // | (rightmost n bits (kept with mask) of y shifted to p)
}

unsigned invert(unsigned x, int p, int n)
// Exercise 2-7, returns x with the n bits that begin at position p inverted, leaving others unchanged
{
    return x ^ (~(~0u <<n) << (p + 1-n));
    // mask of n ones shifted to position p, then XOR directly with x. 1s at positions you want to invert
}

unsigned rightrot(unsigned x, int n)
// Exercise 2-8, returns the value of the integer x rotated to the right by n bit positions
{
    unsigned y = getbits(x, n - 1, n);  // rightmost n bits of x, which are at positions n-1 down to 0
    return (x >> n) | (y << (sizeof(x) * 8 - n));   // shift x by n | shift y and place them at top of word
}