//////////////////////////////////////////////
//////////////////////////////////
// Main File:        check_queens
// This File:        check_queens
// Other Files:      N/A
// Semester:         CS 354 Fall 2018
//
// Author:           Chenxi Gao
// Email:            cgao63@wisc.edu
// CS Login:         cgao
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>   

char *COMMA = ",";

/* COMPLETED:
 * Retrieves from the first line of the input file,
 * the number of rows and columns for the board.
 *
 * fp: file pointer for input file
 * rows: pointer to number of rows
 * cols: pointer to number of columns
 */
void get_dimensions(FILE *fp, int *rows, int *cols) {
	char *line = NULL;
	size_t len = 0;
	if (getline(&line, &len, fp) == -1) {
		printf("Error in reading the file\n");
		exit(1);
	}

	char *token = NULL;
	token = strtok(line, COMMA);
	*rows = atoi(token);

	token = strtok(NULL, COMMA);
	*cols = atoi(token);
}


/* TODO:
 * Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other.
 * Otherwise returns 0.
 *
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns
 */
int check_queens(int **board, int rows, int cols) {
	int x, y, z;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (*(*(board + i) + j) == 1) {
				x = 0;
				for (int a = 0; a < rows; a++) {
					x += *(*(board + a) + j);
				}
				for (int a = 0; a < cols; a++) {
					x += *(*(board + i) + a);
				}
				y = i; z = j;
				for (;y != 0 && z != 0; y--, z--) {
				}
				for (;y < rows && z < cols; y++, z++) {
					x += *(*(board + y) + z);
				}
				y = i; z = j;
				for (;y != 0 && z < cols; y--, z++) {
				}
				for (;y < rows && z != 0; y++, z--) {
					x += *(*(board + y) + z);
				}
				if (x > 4) {
					return 1;
				}
			}
		}
	}
		
	return 0;
}


/* PARTIALLY COMPLETED:
 * This program prints true if the input file has any pair
 * of queens that can attack each other, and false otherwise
 *
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {

	//TODO: Check if number of command-line arguments is correct.
	if (argc != 2) {
		printf("The number of command-line arguments is should be 2\n");
		exit(1);
	}

//Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Cannot open file for reading\n");
		exit(1);
	}


	//Declare local variables.
	int rows, cols;


	//TODO: Call get_dimensions to retrieve the board dimensions.
	get_dimensions(fp, &rows, &cols);

	//TODO: Dynamically allocate a 2D array of dimensions retrieved above.
	int **m;
	m = malloc(sizeof(int *) * rows);
	if (m == NULL) {
		printf("Falled to allocate arrary on heap\n");
		exit(1);
	}
	for (int i = 0; i < rows; i++) {
		m[i] = malloc(sizeof(int)*cols);
		if (m[i] == NULL) {
			printf("Falled to allocate arrary on heap\n");
			exit(1);
		}
	}

//Read the file line by line.
//Tokenize each line wrt comma to store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < rows; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading the file\n");
			exit(1);
		}

		token = strtok(line, COMMA);
		if (token == NULL) {
			printf("Falled to tokenize the line\n");
			exit(1);
		}
		for (int j = 0; j < cols; j++) {
			//TODO: Complete the line of code below
						//to initialize your 2D array.
			/* ADD ARRAY ACCESS CODE HERE */ 
			*(*(m + i) + j) = atoi(token);
			token = strtok(NULL, COMMA);
		}
	}

	//TODO: Call the function check_queens and print the appropriate
		//output depending on the function's return value.
	if (check_queens(m, rows, cols) == 1) {
		printf("true\n");
	}
	else {
		printf("false\n");
	}

	//TODO: Free all dynamically allocated memory.
	for (int i = 0; i < rows; i++) {
		free(m[i]);
	}
	free(m);
	m = NULL;

	//Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file\n");
		exit(1);
	}
	return 0;
}
