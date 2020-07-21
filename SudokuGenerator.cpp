#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "SeedReader.h"

using namespace std;

//seed is "Rows***Shift*Difficulty*
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

int main() {
	char c;
	cout << "what difficulty do you want (1=Easy, 2=Meduim, 3=Hard)" << endl;
	cin >> c;
	if (c <= 48)
		c = 49;
	else if (c >= 52)
		c = 51;
	cout << "you chose difficulty: " << c - 48 << endl;
	genSeed[4] = c;
	
	SeedReader seedReader = SeedReader();
	seedReader.ReadSeed(genSeed);
	int **grid = seedReader.GetGrid();
	PrintGrid(grid);

	return 0;
}

