#pragma once

struct CharArr {
	char** arr;
	int row;
	int col;

	static void randomCharArr(char*&, int);
	static void randomSortArr(char*&, int);
	static char** gen2DArr(int, int, int);
};