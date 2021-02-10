#include "ADTs/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


static const char open[] = "{[(<";
static const char closed[] = "}])>";



int pairMatched(char char1, char char2){ 
	//function takes two characters
	if((char1 == '(') && (char2 == ')'))
		return 1;
	if((char1 == '{') && (char2 == '}'))
		return 1;
	if((char1 == '[') && (char2 == ']'))
		return 1;
	if((char1 == '<') && (char2 == '>'))
		return 1;
	return 0;
}


int isBalanced(const Stack *st, char *expression){ //going to take buf
	
	int i = 0;
	int length = strlen(expression);
	for(i=0; i<length; i++){
		if(strchr(open,expression[i])!= NULL){
			st->push(st, (void *)(long)expression[i]);
		}
		else if(strchr(closed,expression[i])!= NULL){
			long element;
			if(st->isEmpty(st)){ 
				return 0;
			}
			else{		
			st->pop(st,(void **)&element);
			if(!pairMatched(element, expression[i])){
				return 0;
			}
			
			}
		}
	}

	if(st->isEmpty(st)){
		return 1; //stack is balanced
	}
	else{
		return 0; //stack is not balanced
	}
}

int main(int argc, char *argv[]){
	FILE *fd = NULL;
	char buf[BUFSIZ];

	if(argc != 2){
		fprintf(stderr, "Program takes a single command-line argument");
		return EXIT_FAILURE;
	}
	
	if((fd = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Cannot open file");
		return EXIT_FAILURE;
	}

	else{

	fgets(buf, BUFSIZ, fd);
	while(fgets(buf, BUFSIZ, fd) != NULL){
		const Stack *st = Stack_create(0L);
		//check to see if stack was created correctly
		if(st == NULL){
			fprintf(stderr, "Cannot create stack");
			return EXIT_FAILURE;
		}
		//each line in file is series of characters we need to check for order
		//call function on each line

		//skip number on first line of file

		int answer;
		answer = isBalanced(st,buf);
		if(answer){ //if answer non-zero
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}

		st->destroy(st); //destroy the stack
		//printing takes place in the isBalanced function I created
	
	}
	fclose(fd); //close file
	return EXIT_SUCCESS;
}
}

