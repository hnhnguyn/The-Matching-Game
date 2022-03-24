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
		int tmp;
		do {
			tmp = rand() % 26;
		} while (check[tmp]);
		check[tmp] = 1;
		char value = tmp + 'A';
		ch[i] = value;
		ch[i + 1] = value;
	}
}

//sort array randomly
char* randomSortArr(char*& ch, int n) {
	int position[16];
	bool check[16];
	memset(check, 0, sizeof(check));
	for (int i = 0; i < n; i++) {
		int tmp;
		do {
			tmp = rand() % 16;
		} while (check[tmp]);
		position[i] = tmp;
		check[tmp] = 1;
	}
	static char randomArr[16];
	for (int i = 0; i < n; i++) {
		randomArr[position[i]] = ch[i];
	}
	return randomArr;
}

char* gen1DArr() {
	int n = 16;
	char* ch;

	srand(time(NULL));

	randomCharArr(ch, n);

	return randomSortArr(ch, n);
}

CharArr::CharArr() {
	_row = 4;
	_col = 4;
	_CharArr = gen2DArr(gen1DArr(), _row, _col);
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

int CharArr::getRow() {
	return _row;
}

int CharArr::getCol() {
	return _col;
}

void CharArr::setRow(int row) {
	_row = row;
}

void CharArr::setCol(int col) {
	_col = col;
}

void CharArr::setArrElement(int i, int j, char ch) {
	_CharArr[i][j] = ch;
}

char CharArr::getArrElement(int i, int j) {
	return _CharArr[i][j];
}