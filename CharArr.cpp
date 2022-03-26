#include <iostream>
#include <ctime>
#include "CharArr.h"

//create random array including couples of characters
void randomCharArr(char*& ch, int n) {
	ch = new char[n];
	int* check = new int[26];
	for (int i = 0; i < 26; i++) {
		check[i] = 0;
	}
	for (int i = 0; i < n - 1; i+=2) {
		int tmp = rand() % 26;
		if (n / 2 <= 26) {
			do {
				tmp = rand() % 26;
			} while (check[tmp]);
			check[tmp] = 1;
		}
		char value = tmp + 'A';
		ch[i] = value;
		ch[i + 1] = value;
	}
}

//sort array randomly
char* randomSortArr(char*& ch, int n) {
	int position[100];
	bool check[100];
	memset(check, 0, sizeof(check));
	for (int i = 0; i < n; i++) {
		int tmp;
		do {
			tmp = rand() % n;
		} while (check[tmp]);
		position[i] = tmp;
		check[tmp] = 1;
	}
	static char randomArr[100];
	for (int i = 0; i < n; i++) {
		randomArr[position[i]] = ch[i];
	}
	return randomArr;
}

char* CharArr::gen1DArr(int n) {
	char* ch = new char[n];

	srand(time(NULL));

	randomCharArr(ch, n);

	return randomSortArr(ch, n);
}

char** CharArr::gen2DArr(char* ch, int row, int col) {
	char** gen2DArr;
	gen2DArr = new char* [row];
	for (int i = 0; i < row; i++) {
		gen2DArr[i] = new char[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			gen2DArr[i][j] = ch[i * col + j];
		}
	}

	return gen2DArr;
}