#include <stdio.h>
#define MAXLINE 1000
#define TABSTOP 4
#define TRUE    1
#define FALSE   0

int getline(char line[], int maxline);
int detab(char string[], int index);
void entab(char line[], int start, int index);

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
    startofBlank = blank = 0;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {

        if (c == '\t' || c == ' ') {
            blank = TRUE;
            startofBlank = i;
        }
        else {
            if (blank == TRUE) {
                blank = FALSE;
                entab(s, startofBlank, i);
            }
            else
                s[i] = c;
        }
        /* 
        // For 1-20
        if (c == '\t')
            i = detab(s, i) - 1; // -1 as ++i adds 1 extra
        else 
            s[i] = c;

        */
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
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
void entab(char line[], int start, int index)
{
    int nextTab, extraSpaces, i;
    nextTab = extraSpaces = 0;  // set them to the starting index
    i = start;
    while ((i + 4) < index)   // this time don't want extra tabs
        nextTab += 4;

    // num of extra spaces simply rest of space if any
    extraSpaces = index - nextTab; 

    for (i = start; (start + i) < MAXLINE - 1 && i < nextTab; i += 4)
        line[i] = '\t';
    
    start += i; // increment index by all the tabs

    for (i = start; (start + i) < MAXLINE - 1 && i < extraSpaces; ++i)
        line[i] = ' ';
}