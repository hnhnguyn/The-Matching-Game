#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "Common.h"
#include "Game.h"
using namespace std;

class Menu {
private:
	const static string menuList[4];
	const static string playList[4];
public:
	Menu();
	static void titleOutput();
	static void menuOutput();
	static void menuInput();
	static void menuPlayOutput();
	static void menuPlayInput();
	static void menuTutorial();
	static void menuAbout();
};