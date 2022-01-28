#include "Sudoku.h"

#include <string>

using std::endl;
using std::exception;
using std::getline;
using std::string;

const int Sudoku::SIZE = 9;

const char Sudoku::BLANK = '.';


// Constructor
Sudoku::Sudoku() : solved(false) {
	board = new char* [SIZE];
	for (int row = 0; row < SIZE; row++) {
		board[row] = new char[SIZE];
	}
}

// Assignment operator
const Sudoku& Sudoku::operator = (const Sudoku& rhs) {
	if (this != &rhs) {
		if (board) {
			for (int row = 0; row < SIZE; row++) {
				delete[] board[row];
			}
			delete[] board;
			board = NULL;
		}
		solved = rhs.solved;
		board = new char* [SIZE];
		for (int row = 0; row < SIZE; row++) {
			board[row] = new char[SIZE];
			for (int col = 0; col < SIZE; col++) {
				board[row][col] = rhs.board[row][col];
			}
		}
	}
	return *this;
}


// Copy constructor
Sudoku::Sudoku(const Sudoku& other) {
	board = NULL;
	*this = other;
}

// Destructor
Sudoku::~Sudoku() {
	for (int row = 0; row < SIZE; row++) {
		delete[] board[row];
	}
	delete[] board;
}

/* Reads in the cell values from an input file
*  @param in: istream that reads in the file
*/
void Sudoku::loadData(std::istream& in) {
	string currentLine;
	for (int row = 0; row < SIZE; row++) {
		getline(in, currentLine);
		for (int col = 0; col < SIZE; col++) {
			board[row][col] = currentLine[col];
		}
	}
}


/* Find the row index of the next cell
*  @param row: row of current cell
*  @param col: column of current cell
*  return: the row index of the next cell
*/
int Sudoku::nextRowIndex(int row, int col) const {
	if (row == SIZE - 1 && col == SIZE - 1) { return -1; }
	if (col == SIZE - 1) { return row + 1; }
	else { return row; }
}

/* Finds the column index of the next cell
*  @param row: row of current cell
*  @param col: column of current cell
*  @return: the column index of the next cell
*/
int Sudoku::nextColIndex(int row, int col) const {
	if (row == SIZE - 1 && col == SIZE - 1) { return -1; }
	if (col == SIZE - 1) { return 0; }
	else { return col + 1; }
}

/* Determines if char is in the same row as cell
*  @param row: the row to check
*  @param digit: the char to check for
*  @return: returns true if digits is in the row; otherwise returns false
*/
bool Sudoku::inSameRow(int row, char digit) const {
	for (int col = 0; col < SIZE; col++) {
		if (board[row][col] == digit) {
			return true;
		}
	}
	return false;
}

/*Determines if char is in the same row as cell
*  @param col: the column to check
*  @param digit: the char to check for
*  @return: returns true if digit is in the row; otherwise returns false
*/
bool Sudoku::inSameCol(int col, char digit) const {
	for (int row = 0; row < SIZE; row++) {
		if (board[row][col] == digit) {
			return true;
		}
	}
	return false;
}

/* Determines if the char is in the same 4x4 grid that board[row][col] is in
*  @param row: the row for board[row][col]
*  @param col: the column for board[row][col]
*  @param digit: the char to check for
*  @return: returns true if digit is in the row; otherwise returns false
*/
bool Sudoku::inSameGrid(int row, int col, char digit) const {
	int gridStartRow = row / 3 * 3, gridStartCol = col / 3 * 3;
	for (int i = gridStartRow; i < gridStartRow + 3; i++) {
		for (int j = gridStartCol; j < gridStartCol + 3; j++) {
			if (board[i][j] == digit) {
				return true;
			}
		}
	}
	return false;
}

/* Solves the sudoku puzzle and outputs all possible solutions to file
*  @param row: the row of the cell you are fill
*  @param col: the column of the cell you are filling
*  @param out: ostream that writes to output file
*/
void Sudoku::solve(int row, int col) {
	if (row == -1 && col == -1) { // Base case
		solved = true;
		return;
	}
	if (board[row][col] != BLANK) {
		solve(nextRowIndex(row, col), nextColIndex(row, col));
	}
	else {
		// we are at a blank cell
		for (char digit = '1'; digit <= '9'; digit++) {
			if (inSameRow(row, digit)) { continue; }
			if (inSameCol(col, digit)) { continue; }
			if (inSameGrid(row, col, digit)) { continue; }

			// Fill the cell w/ digit
			board[row][col] = digit;

			// Solve the puzzle from the next cell
			solve(nextRowIndex(row, col), nextColIndex(row, col));

			// if no solution found
			if (!solved) {
				board[row][col] = BLANK;
			}
		}
	}
}

// Wrapper method
void Sudoku::solve() {
	solve(0, 0);
}

/* Prints the entire board to an output file when a solution is found
*  @param out: ostream that writes to output file
*/
void Sudoku::printSolution(std::ostream& out) const {
	if (!solved) {
		throw exception("Attempt to output solution for unsolved puzzle.");
	}
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			out << board[row][col];
		}
		out << endl;
	}
}




