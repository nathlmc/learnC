#include <stdio.h>
#define MAXLINE 1000
#define TAB 4
#define TRUE    1
#define FALSE   0

int getline(char line[], int maxline);
int detab(char string[], int index);
int entab(char line[], int start, int index);
int parser(char line[], int start, int index);

int main()
{
    int len;        // current line length
    char line[MAXLINE];     // current input line

    while ((len = getline(line, MAXLINE)) > 0) {
        printf("%s", line);
    }

    return 0;
}


// getline: read a line into s, return length
// added detab condition
int getline(char s[], int lim)
{
    int c, i, startofBlank, blank;
    startofBlank = 0;
    blank = FALSE;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        printf("%d", i);
        if ((c == '\t' || c == ' ') && blank == FALSE) {
            printf("Enter\n");
            blank = TRUE;
            startofBlank = i;
        }
        else if ((c == '\t' || c == ' ') && blank == TRUE)
            ;
            // just keep accumulating, do nothing
        else {
            if (blank == TRUE) {
                blank = FALSE;
                i = startofBlank + entab(s, startofBlank, i); //-1 as ++i adds 1 extra
                printf("I after entab: %d\n", i);
                s[i] = c;
            }
            else {
                s[i] = c;
            }
        }
        /* 
        // For 1-20
        if (c == '\t')
            i = detab(s, i) - 1; // -1 as ++i adds 1 extra
        else 
            s[i] = c;

        */
    }

    // for the case where line is only blanks
    if (blank == TRUE) {
        blank = FALSE;
        entab(s, startofBlank, i);
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    printf("\n\n");
    for (int j = 0; s[j] != '\0' ; j++)
        printf("%d ", s[j]);

    return i;
}

// Exercise 1-20
// Detab returns new index
int detab(char line[], int index)
{
    
    int nextTab, i;
    nextTab = 0;
    // assume no knowledge of % operator
    while (nextTab <= index)
        nextTab += 4;
    for (i = index; (index + i) < MAXLINE - 1 && i < nextTab; ++i)
        line[i] = ' ';
    
    return i;
}

// Exercise 1-21
// Start is start of blank, index is current index
// returns new index after adding blanks
int entab(char line[], int start, int index)
{
    printf("Start: %d End: %d\n", start, index);
    int nextTab, extraSpaces, blanks, i;
    nextTab = extraSpaces = 0;  // set them to the starting index
    i = start;
    blanks = index - start;
    printf("Num of blanks: %d\n", blanks);

    while ((nextTab + TAB) <= blanks)   // this time don't want extra tabs
        nextTab += TAB;

    // num of extra spaces simply rest of space if any
    extraSpaces = blanks - nextTab; 

    printf("Extra spaces needed: %d extra tabs: %d\n", extraSpaces, nextTab/4);

    for (i = start; i < MAXLINE - 1 && i < start + nextTab; i += TAB) {
        printf("Tab inserted\n");
        line[i] = '\t';
    }
    start = i; // increment index by all the tabs

    for (i = start; i < MAXLINE - 1 && i < start + extraSpaces; ++i)
        line[i] = ' ';

    return (nextTab / 4 + extraSpaces);
}

// parser: given line, calculates number of spaces 
int parser(char s[], int start, int index)
{
    int i, numOfBlanks;
    numOfBlanks = 0;
    
    for (i = start; i < index; ++i)
        if (s[i] == '\t') {
            printf("tab detected\n");
            numOfBlanks += TAB;
        }
        else    // would be space otherwise
            ++numOfBlanks;
    
    printf("Returning: %d\n", numOfBlanks);
    return numOfBlanks;
}