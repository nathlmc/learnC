#include <stdio.h>

// copy input to output; 1st version

int main()
{
    int c; // used int hold any possible char and the EOF
    
    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }

    /* also possible
    while ((c = getchar()) != EOF)
        putchar(c);

    */

    printf("%d\n", getchar() != EOF); // EOF is Ctrl + Z 
    printf("%d", EOF); // -1
}