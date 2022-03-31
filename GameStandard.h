#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "common.h"
#include "CharArr.h"
#include "Menu.h"
using namespace std;

struct suggest {
	char ch;
	int preRow;
	int preCol;
	int postRow;
	int postCol;
};

struct GameStandard {
	CharArr charArr;
	const static string gameBtnList[4];
	const static string menuBackList[2];
	const static string pauseList[3];
	suggest sg;
	int gameX;
	int chCnt;
	int time;
	int time_taken;
	clock_t start, end;

	GameStandard();
	void gameOutput();
	void selectColor(int, int, int, int, int, int);
	bool checkMove();
	void shuffle();
	void inputProcess();
	bool checkIMatch(int, int, int, int);
	bool checkLMatch(int, int, int, int);
	bool checkUMatch(int, int, int, int);
	bool checkZMatch(int, int, int, int);
	bool matchCheck(int, int, int, int);
	void pauseScreen();
	void pauseInput();
};