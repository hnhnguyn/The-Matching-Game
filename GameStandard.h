#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "common.h"
#include "CharArr.h"
#include "Menu.h"
using namespace std;

struct GameStandard {
	CharArr charArr;
	const static string gameBtnList[3];
	const static string menuBackList[2];
	const static string pauseList[3];
	int gameX;
	int chCnt;
	int time;
	int time_taken;
	clock_t start, end;

	GameStandard();
	int timeSet(int);
	void gameOutput(int, int);
	void selectColor(int, int, int, int, int, int);
	void inputProcess(int, int);
	bool checkIMatch(int, int, int, int);
	bool checkLMatch(int, int, int, int);
	bool checkUMatch(int, int, int, int);
	bool checkZMatch(int, int, int, int);
	bool matchCheck(int, int, int, int);
	void pauseScreen();
	void pauseInput();
};