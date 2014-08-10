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



//Puzzle Solving Functions
int solveSquare (int col, int row) {
	return 0;
}

void solve () {
	int totalSquaresSolved = 0; //keeps track of the number of solved squares for the pupose of finding when the puzzle is solved
	while (totalSquaresSolved < 81 ) {
		for (int rowCounter = 0; rowCounter < HEIGHT; rowCounter++ ) {
			for (int columnCounter = 0; columnCounter < WIDTH; columnCounter++) {
				
				if (puzzle[rowCounter][columnCounter] == 0) {
					int current = solveSquare(rowCounter,columnCounter);
					//if current does not equal zero then we have solved that square and need to up the counter and record the change.
					if (current != 0) {
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
