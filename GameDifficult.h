#pragma once
#include "Common.h"
#include "LinkedList.h"
#include "Menu.h"
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
	void inputProcess();
	bool checkIMatchLL(Node*, Node*);
	bool checkLMatchLL(Node*, Node*);
	bool checkUMatchLL(Node*, Node*);
	bool checkZMatchLL(Node*, Node*);
	bool matchCheckLL(Node*, Node*);
};