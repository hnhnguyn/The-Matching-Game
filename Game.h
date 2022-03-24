#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "common.h"
#include "CharArr.h"
#include "Menu.h"
using namespace std;

class Game {
private:
	CharArr _Arr;
	const static string gameBtnList[3];
	const static string menuBackList[2];
	const static string pauseList[3];
public:
	Game();
	void gameOutput(int, int);
	void selectColor(int, int, int, int, int, int);
	void inputProcess(int, int);
	bool checkIMatch(int, int, int, int);
	bool checkLMatch(int, int, int, int);
	bool checkUMatch(int, int, int, int);
	bool checkZMatch(int, int, int, int);
	bool matchCheck(int, int, int, int);
	void menuBackScreen();
	void menuBackInput();
	void pauseScreen();
	void pauseInput();
};