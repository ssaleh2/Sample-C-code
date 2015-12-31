/*
Sameh Saleh
11/11/11
CS 262 
Project 3
Dr. Nordstrom
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int new_strcmp(const void *a, const void *b);
int length_cmp(const void* a, const void *b);

int main(){
	int number = 0;
	printf("How many words?");
	//get number of words
	scanf("%d", &number);
	
	//allocate memory for all the words
	char **words = malloc(number*sizeof(char *));
	
	//ensure that number of words enetered is 1 or greater
	while(number<1){
		printf("Must have at least one word\n");
		scanf("%d", &number);
	}
	int x;
	
	//allocate memory for characters in current word
	char* buffer = malloc(sizeof(char *));
	
	//get each word from user, allocate memory for the length of that word,
	//and add to the words array
	for(x=0; x<number; x++){
		scanf("%s", buffer);
		words[x] = malloc(strlen(buffer)+1);
		strcpy(words[x], buffer);
	}	
	
	//sort and print lexicographically
	qsort(words, number, (sizeof(char *)), new_strcmp);
	printf("\nLexigraphic Order: \n");
	for(x=0; x<number; x++){
		printf("%s\n", words[x]);
	}
	
	//sort and print by word length
	qsort(words, number, (sizeof(char *)), length_cmp);
	printf("\nOrder by Length: \n");
	for(x=0; x<number; x++){
		printf("%s\n", words[x]);
	}
	return 0;
}

//compare for lexicographic order
int new_strcmp(const void *a, const void *b){
	
   return strcmp(*(char **)a, *(char **)b);
}

//compare for word length order
int length_cmp(const void* a, const void *b){
	
   return strlen(*(char **)a) - strlen(*(char **)b);
}
