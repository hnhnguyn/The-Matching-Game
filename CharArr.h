#pragma once

struct CharArr {
	char** arr;
	int row;
	int col;

	static void randomCharArr(char*&, int);
	static char* randomSortArr(char*&, int);
	static char* gen1DArr(int);
	static char** gen2DArr(char*, int, int);
};