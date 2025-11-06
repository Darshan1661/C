#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
char buf[BUFSIZE];   // buffer for ungetch
int bufp = 0;        // next free position in buf

int getch(void);
void ungetch(int);
void ungets(char s[]);

/* get a (possibly pushed-back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* push an entire string back onto input */
void ungets(char s[])
{
	int len = strlen(s);
	while (len > 0)
		ungetch(s[--len]);   // push characters in reverse order
}

/* main: demonstration of ungets */
int main(void)
{
	char s[] = "hello, world\n";
		ungets(s);

	int c;
	while ((c = getch()) != EOF)
		putchar(c);

	return 0;
}

