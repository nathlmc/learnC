#define MAXOP   100 // max size of operand or operator
#define MAXVAL	100 // maximum depth of val stack
#define NUMBER  '0' // signal that a number was found
#define BUFSIZE	100
#define FUNCTION 'f'	// Exercise 4-5	
#define VARIABLE 'A'

void push(double);
double pop(void);
void peek(void);		// Exercise 4-4, top elem of the stack
void duplicate(void);	// Exercise 4-4, duplicate top elem of the stack
void swap(void);		// Exercise 4-4, swap top two elems
void clear(void);		// Exercise 4-4, clear stack
int getop(char []);
int getch(void);
void ungetch(int);
void ungets(char s[]);	// Exercise 4-7, push back entire string onto the input