#include "pch.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <time.h>
#include "SeedReader.h"

using namespace std;

//seed is "Rows*** Shift* Difficulty*
// 1 = 37-46, 2 = 30-36, 3 = 25-29,
string genSeed = "12341";

void PrintGrid(int** grid) {
	cout << " ______ ______ ______" << endl;
	for (int row = 0; row < 9; row++) {
		cout << "|";
		for (int col = 0; col < 9; col++) {
			cout << grid[row][col] << " ";
			if (col % 3 == 2) cout << "|";
		}
		cout << endl;
		if (row % 3 == 2)cout << " ______ ______ ______" << endl;
	}
}

void SaveSudoku(ofstream &savefile, int** grid) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			savefile << grid[row][col];
		}
		savefile.put('\n');
	}
}

int main() {
	char input;
	cout << "what difficulty do you want (1=Easy, 2=Meduim, 3=Hard)" << endl;
	cin >> input;
	if (input <= 48)
		input = 49;
	else if (input >= 52)
		input = 51;
	cout << "you chose difficulty: " << input - 48 << endl;
	genSeed[4] = input;
	
	SeedReader seedReader = SeedReader();
	seedReader.ReadSeed(genSeed);
	int **grid = seedReader.GetGrid();
	PrintGrid(grid);
	ifstream savefile;
	ofstream writefile;
	
	cout << "do you wish to save? (Y/N)" << endl;
	cin >> input;
	if (input != 'N' && input != 'n') {
		savefile.open("sudoku.txt");
		if (!savefile.is_open()) {
			writefile.open("sudoku.txt");
			savefile.open("sudoku.txt");
		}
		if (savefile.peek() != ifstream::traits_type::eof()) {
			cout << "savefile already has a sudoku, do you wish to overwrite? (Y/N)" << endl;
			cin >> input;
			if (input == 'Y' || input == 'y') {
				savefile.clear();
			}
		}
		if (!writefile.is_open()) {
			writefile.open("sudoku.txt");
		}
		SaveSudoku(writefile, grid);
		savefile.close();
		writefile.close();
	}
	cout << "do you wish to create another sudoku? (Y/N)" << endl;
	cin >> input;
	if (input == 'Y' || input == 'y') {
		system("CLS");
		return main();
	}
	return 0;
}

