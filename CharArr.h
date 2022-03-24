#pragma once

class CharArr {
private:
	char** _CharArr;
	int _row;
	int _col;
public:
	CharArr();
	char** gen2DArr(char*, int, int);
	int getRow();
	int getCol();
	void setRow(int);
	void setCol(int);
	void setArrElement(int, int, char);
	char getArrElement(int, int);
};