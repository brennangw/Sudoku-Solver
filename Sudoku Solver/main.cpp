//
//  main.cpp
//  Sudoku Solver
//
//  Created by Brennan Goff Wallace on 8/9/14.
//  Copyright (c) 2014 Brennan Goff Wallace. All rights reserved.
//  MIT License, see LICENSE file for more information.
//


//Inclusions
#include <iostream>
#include <fstream>
#include <string>

//Namespaces
using namespace std;

//Definations
#define WIDTH 9
#define HEIGHT 9
#define BOXSIZE 9

//Globals
//To save myself from having to pass this around I decided to just make it one variable.
int puzzle [WIDTH][HEIGHT];

//Funtion Declarations

/*
 * Name: Main
 * Purpose: Starting point of the program. Notfies the user of operation start.
 */
int main(int, const char*[]);
/*
 * Name: inputPuzzle
 * Purpose: Stores the intial puzzle into the double array "puzzle".
 * Calls the solver algorithim if the puzzle is uploaded correctly.
 */
void inputPuzzle();
/*
 * Name: printPuzzle
 * Purpose: Prints the puzzle in its current sate.
 */
void printPuzzle();
/*
 * Name: solve
 * Purpose: Responsiable for solving the actual puzzle.
 */
void solve();
/*
 * Name: solveSqure
 * Purpose: find the correct answer to the square.
 */
int solveSquare(int, int);
/*
 * Name: findPossibles
 * Purpose: Find and return all the possible valuse for a square at the coordinates given.
 * Outline: 
 * get all the possible numbers
 *		get the possiblities
 *			from box
 *			from row
 *			from column
 * condense these numbers
 * is there only one number?
 *		if yes then the squre is solved
 *		if no for each group check if it is the only possible option for that number
 *			and if it is for any of them then the squre is solved
 *			box
 *			row
 *			column
 */
void findPossibles (int, int, int[]);
/*
 * name: findRowPos
 * purpose: Edits the rowPos array so that it refelcts all the possiblities in that row.
 * It foes through each sqaure in the row and then edits the corresponding element of the 
 * array to reflect this. So if the row had 1, 2, 9 then the rowPos array would have elements
 * 0, 1, 8 marked 1 while the rest equal 0.
 */
void findRowPos ( int, int, int[]);
/*
 * name: findColPos
 * purpose: Edits the colPos array so that it refelcts all the possiblities in that column.
 * It foes through each sqaure in the column and then edits the corresponding element of the
 * array to reflect this. So if the column had 1, 2, 9 then the colPos array would have elements
 * 0, 1, 8 marked 1 while the rest equal 0.
 */
void findColPos ( int, int, int[]);
/*
 * name: setArr
 * purpose: clears an int array setting all elemnets to 1.
 */
void setArr(int[]);
/*
 * name: findBoxPos
 * purpose: Find all of the possible
 */

//Utility Functions
void setArr (int toClear[]){
	for (int i = 0; i < 9; i++) {
		toClear[i] = 1;
	}
}

//Puzzle Solving Functions

void voidBoxPos (int row, int col, int boxPox[]) {
	//get box coordinates
	//send box coordinates to get all of the saure coordinates in the box
	//double loop to access all of the squres in the box and setting boxPos like findColPos sets colPos
	
	
	
}

void findColPos ( int row, int col, int colPos[]){
	setArr(colPos); //set all the array to zero
	int x = col; //the col that the the sqaure is in is also the y-coordinate if you start at zero which I am.
	for (int y = 0; y < HEIGHT; y++) {
		int num = puzzle[x][y];
		colPos[ num - 1] = -1; //negative 1 indicates that the number coressponding to the element (num 9 -> element 8, etc) is not a possiblity
	}
}

void findRowPos ( int row, int col, int rowPos[]){
	setArr(rowPos); //set all the array to zero
	int y = row; //the row that the the sqaure is in is also the y-coordinate if you start at zero which I am.
	for (int x = 0; x < WIDTH; x++) {
		int num = puzzle[x][y];
		rowPos[ num - 1] = -1;
	}
}

void findPossibles (int row, int col, int possibles[]) {
	//decalring arrays to find possiblities with
	int rowPos[9];
	int colPos[9];
	int boxPos[9];
	findRowPos(row, col, rowPos);
	findColPos(row, col, colPos);
	findBoxPos(row, col, boxPos);
	combinePos(rowPos,colPos,boxPos,possibles);
}


int solveSquare (int col, int row) {
	int possibles[] = {0,0,0,0,0,0,0,0,0};
	findPossibles(row, col, possibles);
	int singlePossiblity = onePossiblity(possibles);
	if (singlePossiblity != -1) {
		return singlePossiblity;
	} else {
		int onlyOptionNum = onlyOptionCheck(col, row, possibles);
		if (onlyOptionNum != -1) {
			return onlyOptionNum;
		} else {
			return 0;
		}
	}

	

		
}

void solve () {
	int totalSquaresSolved = 0; //keeps track of the number of solved squares for the pupose of finding when the puzzle is solved
	while (totalSquaresSolved < 81 ) {
		for (int rowCounter = 0; rowCounter < HEIGHT; rowCounter++ ) {
			for (int columnCounter = 0; columnCounter < WIDTH; columnCounter++) {
				
				if (puzzle[rowCounter][columnCounter] == 0) {
					int current = solveSquare(rowCounter,columnCounter);
					//if current does not equal zero then we have solved that square and need to up the counter and record the change.
					if (current != -1) { //DEVNOTE: I had this as current != puzzle[rowCounter][columnCounter] but this was simply faster.
						totalSquaresSolved++;
						puzzle[rowCounter][columnCounter] = current;
					}
				}

			}
		}
	}
}

//I/O functions
void printPuzzle() {
	for (int rowCounter = 0; rowCounter < HEIGHT; rowCounter++ ) {
		for (int columnCounter = 0; columnCounter < WIDTH; columnCounter++) {
			if (puzzle[rowCounter][columnCounter] == 0) {
				cout << ' ';
			} else {
				cout << puzzle[rowCounter][columnCounter];
			}
		}
		cout << endl;
	}
}

void inputPuzzle() {
	std::ifstream file("puzzle.txt");
	string line;
	
	
	if (file.is_open()) {
		cout << "puzzle.txt sucessfully opened:" << endl;
		
		int lineCounter = 0;
		while ( getline(file, line) && lineCounter < HEIGHT) {
			cout << line << endl;
			for (int columnCounter = 0; columnCounter < WIDTH; columnCounter++) {
				
				if (line[columnCounter] == ' ') { //blanks will be sotread as zero for easy comprison
					puzzle[lineCounter][columnCounter] = 0;
				} else {
					puzzle[lineCounter][columnCounter] = line[columnCounter] - '0';
					//http://stackoverflow.com/questions/628761/character-to-integer-in-c
				}
			}
			lineCounter++;
		}
		file.close();
	}
	cout << endl << "Stored Puzzle: " <<endl;
	printPuzzle();
	
}

int main(int argc, const char * argv[]) {
	
	// insert code here...
	cout << "Sudoku Puzzle Solver\n" << "This prgram will automatically close if there is not a file named puzzle.txt in the current directory\n\n";
	inputPuzzle();
	solve();
    return 0;
}

