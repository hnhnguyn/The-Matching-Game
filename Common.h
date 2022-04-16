#pragma once
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string>
#include <ctime>
#include "mmsystem.h"
#include "Menu.h"
using namespace std;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15
#define size 8
#define distX 4
#define centerX 49
#define btnX 30
#define leadTitleX 20
#define distY 2
#define menuY 15
#define playY 5
#define leadTitleY 3
#define exitY 3
#define ansY 5
#define resultY 8
#define btnY 2
#define gameY 10
#define leadBoardY 9
#define botY 25

struct Common {
	const static string exitList[2];

	Common() {}
	~Common() {}
	static void selectsound();
	static void matchedsound();
	static void consoleSetup();
	static void goTo(SHORT, SHORT);
	static void setColor(int, int);
	static int getInput();
	static void showCur(bool);
	static void disableSelection();
	static void hideScrollBars();
	static void setWindowSize(SHORT, SHORT);
	static void disableResizeWindow();
	static void disableMaxButton();
	static void exitOutput(int);
	static void exitInput();
};