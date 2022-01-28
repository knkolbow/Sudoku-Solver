#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>

class Sudoku {
private:
	// Data fields
	char** board;
	static const int SIZE;
	static const char BLANK;
	bool solved;

	// Functions
	int nextRowIndex(int, int) const;
	int nextColIndex(int, int) const;
	bool inSameRow(int, char) const;
	bool inSameCol(int, char) const;
	bool inSameGrid(int, int, char) const;
	void solve(int, int);

public:
	// Constructors
	Sudoku(); // Default constructor
	Sudoku(const Sudoku&); // Copy constructor

	// Destructor
	~Sudoku();

	// Functions
	const Sudoku& operator = (const Sudoku&);
	void loadData(std::istream&);
	void solve();
	void printSolution(std::ostream&) const;

};


#endif