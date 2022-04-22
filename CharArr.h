#pragma once

struct CharArr {
	char** arr;

	static void randomCharArr(char*&, int);
	static void randomSortArr(char*&, int);
	static char** gen2DArr(int, int, int);
	static void deleteArr(char**, int);
};