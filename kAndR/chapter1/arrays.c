#include <stdio.h>

#define histoMax    15

// count digits, white space, others
int main()
{
    /*
    int c, i, nwhite, nother;
    int ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;
    
    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;

    printf("digits =");
    for (i = 0; i < 10; ++i)
        printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);

    */
   /*
    // Exercise 1-13
    // Interpreted as individual word length oops
    // Logic would be similar, using prev to detect whether new word or not

    int c2, i2, i3;
    int wordCounts[histoMax];
    int prev = 0;

    for (i2 = 0; i2 < histoMax; ++i2)
        wordCounts[i2] = 0;

    i2 = 0;
    while ((c2 = getchar()) != EOF)
        if (c2 != ' ' && c2 != '\n' && c2 != '\t') {
            ++wordCounts[i2];
            prev = 1;
        }
        else if(prev == 1) {
            ++i2;
            prev = 0;
        }
    int numInputs = i2; // So don't need to print if no extra words

    for (i2 = 0; i2 < numInputs; ++i2) {
        printf("Word number %d :", i2);
        for (i3 = 0; i3 < wordCounts[i2]; ++i3)
            putchar('#');
        putchar('\n');
    }
    */

    // Exercise 1-14 
    int i4, i5, c3;
    int alphabet[26], nums[10];

    for (i4 = 0; i4 < 26; ++i4)
        alphabet[i4] = 0;

    for (i4 = 0; i4 < 10; ++i4)
        nums[i4] = 0;

    while ((c3 = getchar()) != EOF) 
        if (c3 >= '0' && c3 <= '9')
            ++nums[c3-'0'];
        else if (c3 >= 'a' && c3 <= 'z')
            ++alphabet[c3-'a'];
        else if (c3 >= 'A' && c3 <= 'Z')
            ++alphabet[(c3 + 32) - 'a'];

    for (i4 = 0; i4 < 26; ++i4) {
        printf("Letter %c appears: ", i4+'a');
        for (i5 = 0; i5 < alphabet[i4]; ++i5)
            putchar('#');
        putchar('\n');
    }

    for (i4 = 0; i4 < 10; ++i4) {
        printf("Number %d appears: ", i4);
        for (i5 = 0; i5 < nums[i4]; ++i5)
            putchar('#');
        putchar('\n');
    }
}