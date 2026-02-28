#include <stdio.h>

#define IN  1   // inside a word
#define OUT 0   // outside a word

int main()
{
    // copy input to output; 1st version
    /*
    int c; // used int hold any possible char and the EOF
    
    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }

    // also possible
    while ((c = getchar()) != EOF)
        putchar(c);

    */

    // printf("%d\n", getchar() != EOF); // EOF is Ctrl + Z 
    // printf("%d", EOF); // -1

    /*
    long nc;

    nc = 0;
    while (getchar() != EOF)
        ++nc;
    printf("%ld\n", nc);

    // version 2
    double nc2 = 0;

    for (nc2 = 0; getchar() != EOF; ++nc2)
        ;
    printf("%.0f\n", nc2); // can also use %lf for double 
    // .0 suppresses decimal part

    */

    /*
    // line counting
    
    int c, nl;

    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);

    */

    /*
    // Exercise 1-8
    int c2, blanks, tabs, newline;
    blanks = tabs = newline = 0;
    while ((c2 = getchar()) != EOF) {
        if (c2 == ' ')
            ++ blanks;
        if (c2 == '\t')
            ++tabs;
        if (c2 == '\n')
            ++newline;
    }
    printf("%d blanks, %d tabs, and %d new lines", blanks, tabs, newline);

    */

    /*
    // Exercise 1-9
    int c3, prev;
    prev = 0;
    // note: later used symbolic consts. Could have used them here
    while ((c3 = getchar()) != EOF) {
        if (c3 != ' ') {
            if (prev == 0)
                putchar(c3);
            if (prev == 1) {
                putchar(' ');
                putchar(c3);
                prev = 0;
            }
        }
        if (c3 == ' ')
            prev = 1;
    }
    */

    /*
    // Exercise 1-10
    int c4, entered;
    entered = 0; 
    while ((c4 = getchar()) != EOF) {
        if (c4 == '\t') {
            printf(" \\t "); // using printf to reduce num of lines needed
            entered = 1; // added space next to special char to improve visibility
        }
        if (c4 == '\b') {
            printf(" \\b ");
            entered = 1;
        }
        if (c4 == '\\') {
            putchar('\\');
            entered = 1;
        }
        if (entered == 0)
            putchar(c4);
        entered = 0;
    }
    */

    /*
    int c5, n1, nw, nc, state;

    state = OUT;
    n1 = nw = nc = 0;
    while ((c5 = getchar()) != EOF) {
        ++nc;
        if (c5 == '\n')
            ++n1;
        if (c5 == ' ' || c5 == '\n' || c5 == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++ nw;
        }
    }
    printf("%d %d %d\n", n1, nw, nc);

    */

    // Exercise 1-12

    int state2, prev;
    state2 = OUT;
    prev = OUT;
    int c6;
    while ((c6 = getchar()) != EOF) {
        if (c6== ' ' || c6 == '\n' || c6 == '\t')
            state2 = OUT;
        else {
            state2 = IN;
            prev = IN;
            putchar(c6);
        }

        if ((state2 == OUT) && (prev == IN)) {
            prev = OUT;
            putchar('\n');
        }

    }
}