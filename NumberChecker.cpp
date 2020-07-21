#include "pch.h"
#include "NumberChecker.h"


NumberChecker::NumberChecker() {
}

NumberChecker::~NumberChecker() {
}

bool NumberChecker::SafeNum(int grid[N][N], int row, int col, int num) {
	return SafeBox(grid, row - row % 3, col - col % 3, num) 
		&& SafeRow(grid, row, num) 
		&& SafeCol(grid, col, num);
}

bool NumberChecker::SafeRow(int grid[N][N], int row, int num) {
	for (int c = 0; c < N; c++) {
		if (grid[row][c] == num)
			return false;
	}
	return true;
}

bool NumberChecker::SafeCol(int grid[N][N], int col, int num) {
	for (int r = 0; r < N; r++) {
		if (grid[r][col] == num)
			return false;
	}
	return true;
}

bool NumberChecker::SafeBox(int grid[N][N], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (grid[startRow + row][startCol + col] == num)
				return false;
		}
	}
	return true;
}
