#include "pch.h"
#include <time.h>
#include <iostream>
#include "SeedReader.h"

SeedReader::SeedReader() {
	ClearGrid();
	srand(time(NULL));
}

SeedReader::SeedReader(int _grid[N][N]) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			grid[row][col] = _grid[row][col];
		}
		seedRow[row] = row + 1;
	}
	srand(time(NULL));
}

SeedReader::~SeedReader() {
	numCheck.~NumberChecker();
}

void SeedReader::ReadSeed(string seed) {
	ClearGrid();
	int shift = seed[3] - 48;
	ShuffleRow(seedRow);
	CheckDifficulty(seed[4] - 48);
	for (int i = 0; i < 3; i++) {
		insertedRows[i] = seed[i] - 49 + (3 * i);	
		InsertRowInGrid(seedRow, insertedRows[i]);
		ShiftRow(shift);
	}
	if (!FillSudoku()) {
		cout << "No sudoku grid could be made" << endl;
		exit(0);
	}
	//clues = 79;
	vector<int> filledClues;
	for (int i = 0; i < 81; i++) {
		filledClues.insert(filledClues.begin() + i, i);
	}
	if (!ClearClues(filledClues))
		cout << "Could not create grid" << endl;
	cout << "Sudoku created" << endl;
}

void SeedReader::CreateNoSeedSudoku() {
	ClearGrid();
	if (!FillSudoku()) {
		cout << "No sudoku grid could be made" << endl;
		exit(0);
	}
	CheckDifficulty(rand() % 4 + 1);
}

int** SeedReader::GetGrid() {
	int** returnGrid = new int*[N];
	for (int row = 0; row < N; row++) {
		returnGrid[row] = new int[N];
		for (int col = 0; col < N; col++) {
			returnGrid[row][col] = grid[row][col];
		}
	}
	return returnGrid;
}

void SeedReader::ClearGrid() {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			grid[row][col] = 0;
		}
		seedRow[row] = row + 1;
	}
}

void SeedReader::ShuffleRow(int row[]) {
	int times = 90;
	int tempNum;
	int shuffledNum1;
	int shuffledNum2;
	for (int i = 0; i < times; i++) {
		shuffledNum1 = rand() % N;
		shuffledNum2 = rand() % N;
		while (shuffledNum2 == shuffledNum1) {
			shuffledNum2 = rand() % N;
		}
		tempNum = row[shuffledNum1];
		row[shuffledNum1] = row[shuffledNum2];
		row[shuffledNum2] = tempNum;
	}
}

void SeedReader::InsertRowInGrid(int row[], int gridRow) {
	for (int i = 0; i < N; i++) {
		grid[gridRow][i] = row[i];
	}
}

void SeedReader::ShiftRow(int shifts) {
	int tempArr[N];
	for (int i = 0; i < N; i++) {
		if (i + shifts >= N) {
			shifts -= N;	
		}
		tempArr[i + shifts] = seedRow[i];
	}
	for (int i = 0; i < N; i++) {
		seedRow[i] = tempArr[i];
	}
}

void SeedReader::CheckDifficulty(int dif) {
	// 1 = 37-46, 2 = 30-36, 3 = 25-29, 
	if (dif >= 5) { dif = 4; }
	else if (dif <= 0) { dif = 1; }
	switch (dif) {
	case 1:
		clues = rand() % 10 + 37;
		break;
	case 2:
		clues = rand() % 7 + 30;
		break;
	case 3:
		clues = rand() % 5 + 25;
		break;
	}
}

bool SeedReader::FillSudoku() {
	vector<int> inputNum;
	int chosenNum;
	for (int i = 0; i < N; i++) {
		inputNum.insert(inputNum.begin() + i, i + 1);
	}
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			if (grid[row][col] == 0) {
				while (inputNum.size() > 0) {
					chosenNum = rand() % inputNum.size();
					if (numCheck.SafeNum(grid, row, col, inputNum[chosenNum])) {
						grid[row][col] = inputNum[chosenNum];
						if (FillSudoku())
							return true;
						grid[row][col] = 0;
					}
					inputNum.erase(inputNum.begin() + chosenNum);
				}
				return false;
			}
		}
	}
	return true;
}

bool SeedReader::ClearClues(vector<int> &filledClues) {
	vector<int> clueTries;
	for (int i = 0; i < filledClues.size(); i++) {
		clueTries.insert(clueTries.begin() + i, i);
	}
	int randNum = rand() % filledClues.size();
	int gridPos = filledClues[randNum];
	int row = gridPos / 9;
	int col = gridPos - row * 9;
	int originalGridNum = grid[row][col];
	grid[row][col] = 0;
	int sol = 0;

	while (TryUniqueFill(sol) != 1) {

		grid[row][col] = originalGridNum;
		clueTries.erase(clueTries.begin() + randNum);
		if (clueTries.size() == 0)
			return false;
		randNum = rand() % clueTries.size();
		gridPos = filledClues[clueTries[randNum]];
		row = gridPos / 9;
		col = gridPos - row * 9;
		originalGridNum = grid[row][col];
		grid[row][col] = 0;

	}

	filledClues.erase(filledClues.begin() + clueTries[randNum]);
	if (filledClues.size() == clues) 
		return true;
	/*if (ClearClues(filledClues))
		return true;*/
	while(!ClearClues(filledClues)) {
		filledClues.insert(filledClues.begin() + clueTries[randNum], gridPos);
		grid[row][col] = originalGridNum;
		clueTries.erase(clueTries.begin() + randNum);
		if (clueTries.size() == 0)
			return false;
		randNum = rand() % clueTries.size();
		gridPos = filledClues[clueTries[randNum]];
		row = gridPos / 9;
		col = gridPos - row * 9;
		originalGridNum = grid[row][col];
		grid[row][col] = 0;
		while (TryUniqueFill(sol) != 1) {
			grid[row][col] = originalGridNum;
			clueTries.erase(clueTries.begin() + randNum);
			if (clueTries.size() == 0)
				return false;
			randNum = rand() % clueTries.size();
			gridPos = filledClues[clueTries[randNum]];
			row = gridPos / 9;
			col = gridPos - row * 9;
			originalGridNum = grid[row][col];
			grid[row][col] = 0;
		}

		filledClues.erase(filledClues.begin() + clueTries[randNum]);
		if (filledClues.size() == clues)
			return true;
	}
	return true;
}

int SeedReader::TryUniqueFill(int solutions) {
	vector<int> inputNum;
	int chosenNum;
	for (int i = 0; i < N; i++) {
		inputNum.insert(inputNum.begin() + i, i + 1);
	}
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			if (grid[row][col] == 0) {
				while (inputNum.size() > 0) {
					chosenNum = rand() % inputNum.size();
					if (numCheck.SafeNum(grid, row, col, inputNum[chosenNum])) {
						grid[row][col] = inputNum[chosenNum];
						if (GridComplete()) {
							solutions++;
							if (solutions >= 2) {
								grid[row][col] = 0;
								return 2;
							}
						}	
						solutions = TryUniqueFill(solutions);
						if (solutions >= 2) {
							grid[row][col] = 0;
							return 2;
						}
					}
					inputNum.erase(inputNum.begin() + chosenNum);
				}
				grid[row][col] = 0;
				return solutions;
			}
		}
	}
	return solutions;
}

bool SeedReader::GridComplete() {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			if (grid[row][col] == 0) {
				return false;
			}
		}
	}
	return true;
}
