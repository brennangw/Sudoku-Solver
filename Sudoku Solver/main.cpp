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
 * name: findBoxPos
 * purpose: Essentially the same as the other find__Pos functions bot for the "box".
 * plan:
 * 	get box coordinates
 *  send box coordinates to get all of the saure coordinates in the box
 *   access all of the squres in the box and setting boxPos like findColPos sets colPos
 */
void findBoxPos (int, int, int[]);
/*
 * name: combinePos
 * purpose: combines all of the possiblities for columns, rows and boxes. If it is not possible due to one then it is not possible is the basic logic used.
 */
void combinePos (int[], int[], int[], int[]);

/*
 * name: getBoxCors
 * purpose: Given the row and column of a square store the coordinates of the box.
 * Algorithm:
 * Divide each coordinate by 3 (truncating).
 * Examples/Semi-Proof:
 * square (3,8) => block (1,2)
 * square (0,0) => block (0,2)
 * This gives the block "coordinates". Diagram below demonstrates how the block coordinates work. Each block has 9 squares.
 * +-----+-----+-----+
 * | 0,0 | 0,1 | 0,2 |
 * +-----+-----+-----+
 * | 1,0 | 2,1 | 3,2 |
 * +-----+-----+-----+
 * | 2,0 | 2,1 | 3,2 |
 * +-----+-----+-----+
 *
 */
void getBoxCors( int, int, int[]);
/*
 * name: findSquaresInBox
 * purpose: Given coordinates of a box store the coordinates of the all the squares in the box.
 * Algorithm:
 *		Take x each coordinate add three and take that number plus the next to increments.
 *		Then do the same for each y coordinate.
 *		Then find all 9 combos.
 */
void findSquaresInBox(int[], int[][2]);
/*
 * name: getDimensionRangeSquaresInBox.
 * purpose: Finds the range of the of squares' in a box values for one axis and puts this info in an array.
 */
void getDimensionRangeSquaresInBox (int, int[]);
/*
 * name: getSquareCorsFromXYCoors
 * purpose: Given the x and y coordinates it finds all the combinations of these.
 */
void getSquareCorsFromXYCoors(int [], int[], int[][2], int);

/*
 * name: setArr
 * purpose: Sets the array to a single number to set it up for pos indication.
 */
void setArr(int[]);




//Utility Functions
void getSquareCorsFromXYCoors(int x[], int y[], int squares[][2], int l){
	int i = 0;
	for (int xi = 0; xi < l; xi++) {
		for (int yi = 0; yi < l; yi++) {
			squares[i][0] = x[xi];
			squares[i][1] = y[yi];
			i++;
		}
	}
}

void setArr (int toClear[]){
	for (int i = 0; i < 9; i++) {
		toClear[i] = 1;
	}
}

void getDimensionRangeSquaresInBox (int boxCor, int squareCors[]) {
	int squareCor = boxCor*3;
	int i = 0;
	
	while (squareCor < (boxCor*3 + 3)) {
		squareCors[i] = squareCor;
		squareCor++;
		i++;
	}
	
}

void getBoxCors( int row, int col, int boxCors[]) {
	boxCors[0] = row/3;
	boxCors[1] = col/3;
}
void findSquaresInBox(int boxCors[], int squaresInBox[][2]) {
	int xs[3];
	int ys[3];
	
	//get the x and y cordinates
	getDimensionRangeSquaresInBox(boxCors[0], xs);
	getDimensionRangeSquaresInBox(boxCors[1], ys);
	//getSquareCorsFromXYCoors (squaresInBox, xs, ys, 3);
	
	
	

}


//Puzzle Solving Functions

void findBoxPos (int row, int col, int boxPos[]) {
	setArr(boxPos);
//	int boxCors[2];
//	int squaresInBox [9][2];
//	getBoxCors( row, col, boxCors);
//	findSquaresInBox (boxCors, squaresInBox);
	
	
	
}

void findColPos ( int row, int col, int colPos[]){
	setArr(colPos); //set all the array to zero
	for (int y = 0; y < HEIGHT; y++) {
		int num = puzzle[y][col];
		colPos[ num - 1] = -1; //negative 1 indicates that the number coressponding to the element (num 9 -> element 8, etc) is not a possiblity
	}
}

void findRowPos ( int row, int col, int rowPos[]){
	setArr(rowPos); //set all the array to one
	cout << "row is: " << row << "  col is: " << col <<endl;
	for (int x = 0; x < WIDTH; x++) {
		int num = puzzle[row][x];
			cout << "num is " << num << endl;
		rowPos[ num - 1] = -1; //represents not possible
	}
}

void markNotPos (int toRead[], int toMark[], int l){
	for (int i = 0; i < l; i++) {
		if (toRead[i] == -1) {
			toMark[i] = -1;
		}
	}
}

void combinePos(int rowPos[], int colPos[], int boxPos[], int totPos[]) {
	markNotPos (rowPos, totPos, 9);
	markNotPos (colPos, totPos, 9);
	markNotPos (boxPos, totPos, 9);
}

void findPossibles (int row, int col, int possibles[]) {
	//decalring arrays to find possiblities with
	int rowPos[9];
	int colPos[9];
	int boxPos[9];
	findRowPos(row, col, rowPos);
	cout << "after findRowPos rowPos is:" <<endl;
	for (int rowP :rowPos) {
		cout << rowP << endl;
	}
	findColPos(row, col, colPos);
	cout << "after findcolPos colPos is:" <<endl;
	for (int colP :colPos) {
		cout << colP << endl;
	}
	findBoxPos(row, col, boxPos);
	combinePos(rowPos,colPos,boxPos,possibles);
}

int onePossiblity (int toCheck[], int l) {
	int soloPos = -1;
	for (int i = 0; i < l; i++) {
		if (toCheck[i] == 0 && soloPos == -1) {
			soloPos = i + 1;
		} else if (toCheck[i] == 0 && soloPos != -1 ) {
			return -1;
		}
	}
	return soloPos;
}


int solveSquare (int row, int col) {
	int possibles[] = {0,0,0,0,0,0,0,0,0};
	findPossibles(row, col, possibles);
	cout << "possibles array from solve square is found to be: " << endl;
	for (int pos : possibles) {
		cout << pos << endl;
	}
	int singlePossiblity = onePossiblity(possibles, 9);
	if (singlePossiblity != -1) {
		return singlePossiblity;
	} else {
		return -1;
//		int onlyOptionNum = onlyOptionCheck(col, row, possibles);
//		if (onlyOptionNum != -1) {
//			return onlyOptionNum;
//		} else {
//			return 0;
//		}
	}
}
  
void solve () {
	int totalSquaresSolved = 0; //keeps track of the number of solved squares for the pupose of finding when the puzzle is solved
	while (totalSquaresSolved < 81 ) {
		totalSquaresSolved = 0;
		for (int rowCounter = 0; rowCounter < HEIGHT; rowCounter++ ) {
			for (int columnCounter = 0; columnCounter < WIDTH; columnCounter++) {
				cout << "looking at: " << rowCounter << "," << columnCounter << " which is currently: " << puzzle[rowCounter][columnCounter] << endl;
				if (puzzle[rowCounter][columnCounter] == 0) {
					cout << "solving this square" << endl;
					int current = solveSquare(rowCounter,columnCounter);
					cout << "answer is : " << current << endl;
					//if current does not equal zero then we have solved that square and need to up the counter and record the change.
					if (current != -1) { //DEVNOTE: I had this as current != puzzle[rowCounter][columnCounter] but this was simply faster.
						//totalSquaresSolved++;
						puzzle[rowCounter][columnCounter] = current;
					}
				} else {
					totalSquaresSolved++;
				}

			}
		}
	}
	
	printPuzzle();
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
	
	cout << "Sudoku Puzzle Solver\n" << "This prgram will automatically close if there is not a file named puzzle.txt in the current directory\n\n";
	inputPuzzle();
	solve();
    return 0;
}

