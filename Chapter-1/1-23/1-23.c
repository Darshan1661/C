#include<stdio.h>
#include<string.h>
#define MAX 10000

int main(void){
	char code[MAX], c;
	int i = 0, in_comment = 0, in_string = 0;
	
	while ((c = getchar()) != EOF)
		code[i++] = c;
	code[i] = '\0';
	
	for(i = 0; code[i] != '\0'; i++){
		if(!in_comment && code[i] == '"' && code[i+1] != '\\')
			in_string = !in_string;
		if(!in_string){
			if(!in_comment && code[i] == '/' && code[i+1] != '*'){
				in_comment = 1;
				i++;
				continue;
			}
			else if(!in_comment && code[i] == '*' && code[i+1] == '/'){
				in_comment = 0;
				i++;
			}
			else if(!in_comment && code[i] == '/' && code[i+1] == '/'){
				while(code[i] != '\n' && code[i] != '\0')
					i++;
			}
		}
		if(!in_comment)
			putchar(code[i]);
	}
	return 0;
}
					       

