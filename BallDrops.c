//Sameh Saleh
//10/7/11
//CS 262 Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes
void drop(int drops);
void histogram(int array[], int max);
time_t time(time_t *t);
int slide();


int main()
{
	int number = 0;
	printf("How many balls to drop?"); 	
	//takes in user's input for number of balls to drop
	scanf("%d", &number);
	//if number is invalid (below 1) the user will be asked until he puts in
	//valid response
	while(number<1){
		printf("Must drop at least one ball\n");
		scanf("%d", &number);
	}
	//calls drop method
	drop(number);
	return 0;
}

void drop(int drops){
	int catch[21] = {};
	//
	int maxSlots = drops;
	int random;
	//uses time stamp as seed for random number
	srand(time(0));
	while(drops!=0){
		//start at 11th slot (middle)
		int move = 10;
		int i;
		for (i = 0; i < 10; i++){
			//ball slides either left or right
			random = slide();
			//if random number has a remainder when divided by 2
			//move left
			if (random == 1){
				move = move - 1;
			}
			//otherwise move right
			else if(random == 0){
				move = move + 1;
			}
		}
		//keep track of number of balls in current slot
		catch[move] = catch[move] + 1; 
		//work through all drops
		--drops;
	}
	histogram(catch, maxSlots);
}
int slide(){
	int new = rand();
	return new%2;
}	

void histogram(int array[], int max){
	int i;
	//print histogram from slots -10 to 10 by 2s
	for(i = -10; i<11; i++){
		int x;
		if(i%2 == 0){
			printf("%3d: ", i);
			for(x=0; x<array[i+10]; x++){
				printf("o");
			}
			printf("\n");
		}
	}
}
		
