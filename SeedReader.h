#include <string>
#include <vector>
#include "NumberChecker.h"
#pragma once
using namespace std;

class SeedReader {
public:
	SeedReader();
	SeedReader(int _grid[N][N]);
	~SeedReader();

	void ReadSeed(string seed);
	void CreateNoSeedSudoku();
	int** GetGrid();

private:
	int seedRow[N];
	int grid[N][N];
	int insertedRows[3];
	NumberChecker numCheck;
	int clues;

	void ClearGrid();
	void ShuffleRow(int row[]);
	void InsertRowInGrid(int row[], int gridRow);
	void ShiftRow(int shifts);
	void CheckDifficulty(int dif);
	
	bool FillSudoku();
	bool ClearClues(vector<int> &filledClues);
	int TryUniqueFill(int sol);
	bool GridComplete();
};

