i#include "ADTs/stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void printStack(const Stack *st, FILE *fp){

	//check if stack is empty, then return to exit

	//DUPLICATE STACK 
	if(st->isEmpty(st)){
		fprintf(fp,"Empty\n");
		return;
		}
	const Stack *duplicate = st->create(st);
	if(duplicate == NULL){
		fprintf(fp, "Cannot create duplicate stack");
		return;
	}

	//main logic here for push,pop,print
	long element;
	bool first = true;

	while(st->pop(st,(void **)&element)){
		fprintf(fp, "%s%ld", first ? "" : " ", element);
		first = false;
		duplicate->push(duplicate,(void *)element);
	}

	//each line of output must be terminated by a newline character.
	fprintf(fp, "\n");
	
	while(duplicate->pop(duplicate,(void **)&element)){
		st->push(st,(void *)element);
			}
		
//make sure to destroy duplicate stack
duplicate->destroy(duplicate);
}


int main(int argc, char *argv[]){
	FILE *fd = NULL;
	//use fgets here
	char buf[BUFSIZ];

	const Stack *st = Stack_create(0L);
	//check to see if stack was created correctly
	if(st == NULL){
		fprintf(stderr, "Cannot create stack");
		return EXIT_FAILURE;
	}
	if(argc != 2){
		fprintf(stderr, "Program takes a single command-line argument");
		return EXIT_FAILURE;
	}

	if((fd = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Cannot open file");
		return EXIT_FAILURE;
	}

	else{
	while(fgets(buf, BUFSIZ, fd) != NULL){
		if(strstr(buf,"print") != NULL){
			printStack(st,stdout);
				}

		if(strstr(buf, "push") != NULL){
			//get element
			//push onto stack
			long element;
			char *instr;
			instr = malloc(sizeof(char*));

			sscanf(buf, "%s %ld",instr,&element);
			st->push(st, (void *)element);
			free(instr);
		}
		if(strstr(buf, "pop") != NULL){
			long element;
			if(st->isEmpty(st)){
				fprintf(stdout,"StackError\n");
			}
			else{
			st->pop(st,(void **)&element);
			fprintf(stdout,"%ld\n",element);
			}
		}
	}
	st->destroy(st); //destroy stack
	fclose(fd);
	return EXIT_SUCCESS; 
	}
}
