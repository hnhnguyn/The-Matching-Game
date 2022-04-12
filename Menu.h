#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "Common.h"
#include "GameStandard.h"
using namespace std;

struct Menu {
	const static string menuList[5];
	const static string playList[3];
	const static string doneList[2];
	static string name;
	static double time;

	Menu();
	static void titleOutput();
	static void menuOutput();
	static void menuInput();
	static void menuGetName();
	static void nameInput();
	static void menuPlayOutput();
	static void menuPlayInput();
	static void printLeadBoard();
	static void menuLeaderboard();
	static void menuTutorial();
	static void menuAbout();
	static void menuDoneOutput(double);
	static void menuDoneInput();
	static void topPlayCheck();
};