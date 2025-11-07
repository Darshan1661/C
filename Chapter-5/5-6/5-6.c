#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

/* getline_p: read a line into s, return length */
int getline_p(char *s, int lim)
{
	char *start = s;
	int c;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - start;
}

/* reverse_p: reverse string s in place */
void reverse_p(char *s)
{
	char *t = s;
	char temp;

	while (*t)
		t++;
	t--;  /* point to last valid char */

	while (s < t) {
		temp = *s;
		*s++ = *t;
		*t-- = temp;
	}
}

/* atoi_p: convert string s to integer */
int atoi_p(const char *s)
{
	int n = 0, sign = 1;
	while (isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
		sign = (*s++ == '-') ? -1 : 1;
	while (isdigit(*s))
		n = 10 * n + (*s++ - '0');
	return sign * n;
}

/* Test */
int main(void)
{
	char line[MAXLINE];

	printf("Enter a line: ");
	int len = getline_p(line, MAXLINE);
	printf("You entered (%d chars): %s", len, line);

	reverse_p(line);
	printf("Reversed: %s\n", line);

	printf("atoi_p(\"-12345\") = %d\n", atoi_p("-12345"));
	return 0;
}

