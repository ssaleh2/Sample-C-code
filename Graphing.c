/*
Sameh Saleh
10/28/11
CS 262 
Project 2
Dr. Nordstrom
*/

#define X_SEMIRANGE 3
#define Y_SEMIRANGE 2
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes
double f(double);
void createSystem(char[Y_SEMIRANGE*20+1][X_SEMIRANGE*20 + 1]);
void addData(char[Y_SEMIRANGE*20+1][X_SEMIRANGE*20 + 1]);
void printGraph(char[Y_SEMIRANGE*20+1][X_SEMIRANGE*20 + 1]);

int main(){
	
	//declare 2D array for graph
	char graph[Y_SEMIRANGE*20+1][X_SEMIRANGE*20 + 1];
	
	//create the axes of the graph
	createSystem(graph);
	
	//add the data points for the function defined in f
	addData(graph);
	return 0;
}

double f(double x_val){
	
	//designated function returns the y value for each x value in 
	return pow(x_val,2);
}

void createSystem(char graphed[Y_SEMIRANGE*20+1][X_SEMIRANGE*20 + 1]){
	
	//where x and y equal 0
	int midx = (X_SEMIRANGE*20)/2;
	int midy = (Y_SEMIRANGE*20)/2;
	int x=0;
	int y=0;
	
	//form x and y axis with '-' and '|' respectively
	//all other points are set to one space
	for(y = 0; y<(Y_SEMIRANGE*20 + 1); y++){
		for(x = 0; x<(X_SEMIRANGE*20+1); x++){	
			if (y==midy){
				graphed[y][x]='-';
			}
			else if(x==midx){
				graphed[y][x]='|';
			}
			else{
				graphed[y][x]=' ';
			}
		}
	}
}

void addData(char graphed[Y_SEMIRANGE*20+1][X_SEMIRANGE*20 + 1]){
	
	//initialize variables for the value of the x and y in the function
	//and for the calculated coordinates based on the defined ranges at top
	int x_coor = 0;
	double y_value = 0;
	int y_coor = 0;
	double x_value = 0;
	
	//function for all x values in range
	while(x_coor!=X_SEMIRANGE*20+1){
		
		// if x<=midpoint of x range, convert from x array index to 
		//x - value
		if(x_coor<=X_SEMIRANGE*20/2){
			x_value = (double) x_coor;
			y_value=f(x_value/10-X_SEMIRANGE);
		}
		
		// if x>midpoint of x range, convert x array index to x + value
		else{
			x_value = (double) x_coor;
			y_value=f((x_value-X_SEMIRANGE*10)/10);
		}
		
		//if y value >= 0, convert the y value to the y array index and
		//add rounding factor to account for truncation
		if (y_value >= 0){
			y_coor = (int)(Y_SEMIRANGE*20/2 - y_value*10+0.499);
		}
		
		//if y value >= 0, convert the y value to the y array index and
		//subtract rounding factor to account for truncation
		else{
			y_coor = (int)(Y_SEMIRANGE*20 - 
			(10*(y_value+Y_SEMIRANGE)- 0.499));
		}
		
		//add o for data points if y array index is in the length of 
		// first dimension array
		if(y_coor>=0 && y_coor<Y_SEMIRANGE*20+1){
			graphed[y_coor][x_coor]='o';	
		}
		
		//increment the x array index
		x_coor++;
	}
	
	//print graph
	printGraph(graphed);
}

void printGraph(char graphed[Y_SEMIRANGE*20+1][X_SEMIRANGE*20 + 1]){
	int y;
	int x;
	
	//iterates through array to print
	for(y = 0; y<(Y_SEMIRANGE*20 + 1); y++){
		printf("\n");
		for(x = 0; x<(X_SEMIRANGE*20+1); x++){	
			//print either "o" if data point or leave space or grid
			//lines if not
			printf("%c", graphed[y][x]);
		}
	}
}

