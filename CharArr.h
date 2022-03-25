#pragma once

struct CharArr {
	char** arr;
	int row;
	int col;

	char* gen1DArr(int);
	char** gen2DArr(char*, int, int);
};