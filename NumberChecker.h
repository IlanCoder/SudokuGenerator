#pragma once
const int N = 9;

class NumberChecker {
public:
	NumberChecker();
	~NumberChecker();

	bool SafeNum(int grid[N][N], int row, int col, int num);

private:

	bool SafeRow(int grid[N][N], int row, int num);
	bool SafeCol(int grid[N][N], int col, int num);
	bool SafeBox(int grid[N][N], int startRow, int startCol, int num);
};

