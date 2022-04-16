#pragma once
#include "Common.h"
#include "Menu.h"
#include "LinkedList.h"
using namespace std;

struct GameDifficult {
	LinkedList L;
	const static string gameBtnList[4];
	const static string menuBackList[2];
	const static string pauseList[3];
	int gameX;
	int chCnt;
	clock_t time;
	double time_taken;

	GameDifficult();
	void printRow(List, int, int);
	void printBoard();
	void gameOutput();
	void selectColor(int, int, int, int, Node*);
	bool checkMove();
	void shuffle();
	void inputProcess();
	bool checkIMatch(int, int, int, int);
	bool checkLMatch(int, int, int, int);
	bool checkUMatch(int, int, int, int);
	bool checkZMatch(int, int, int, int);
	bool matchCheck(Node*, Node*);
	void pauseScreen();
	void pauseInput();
};