#include <stdio.h>
#define MAXLINE 1000 // maximum input line size
#define MINPRINTLENGTH 80

int getline(char line[], int maxline);
void copy(char to[], char from[]);
int formattedGetline(char line[], int maxLine);
int checkBlank(int length);
void reverse(char s[]);

// print longest input line
int main()
{
    int len;        // current line length
    int max;        // maximum length seen so far
    char line[MAXLINE];     // current input line
    char longest[MAXLINE];  // longest line saved here
    char reversedLine[MAXLINE];

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > max) {
            // Exercise 1-18 print all input lines that are > 80 (MINPRINTLENGTH)
            if (len > MINPRINTLENGTH) 
                printf("%s\n", line);
            max = len;
            copy(longest, line);
        }
        if (checkBlank(len)) {
            copy(reversedLine, line);
            reverse(reversedLine);                
            printf("%s\n", reversedLine);
        }
    }
    if (max > 0) {    // there was a line
        printf("%s\n", longest);
        // Exercise 1-16 Print length off arbitarily long input lines
        printf("%d\n", max);
    }
    return 0;
}

// getline: read a line into s, return length
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

// copy: copy 'from' into 'to'; assume to is big enough
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

// Exercise 1-18
int formattedGetline(char s[], int lim)
{
    int c, i;
    int track = 0;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
        if (c != ' ' && c != '\t')
            track = i;
    }
    ++track; // increment track by 1 as it currently points on last char
    // track would be smaller than i if there are trailing spaces or tabs
    if (track < i) 
        i = track; 

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int checkBlank(int length) 
{
    if (length == 1)
        return 0;
    return 1;
}

// Exercise 1-19

void reverse(char s[]) 
{
    int i,j,c;
    i = j = 0;
    // get to end of string
    for (i = 0; s[i] != '\0' ; ++i)
        ;
    // don't reinitialize i as it is at the end
    i = i - 1;
    for (i; i > j; --i) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        ++j;
    }
}