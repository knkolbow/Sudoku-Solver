#include "Sudoku.h"

#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ifstream fin("puzzle_2.txt");
	if (!fin) {
		cout << "Error: input file does not exist." << endl;
		system("pause");
		return -1;
	}
	ofstream fout("solution.txt");

	Sudoku puzzle;
	puzzle.loadData(fin);
	puzzle.solve();
	puzzle.printSolution(fout);

	fin.close();
	fout.close();

	return 0;
}