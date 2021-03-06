#include "Common.h"

const string Common::exitList[2] = { "YES", "NO" };

void Common::consoleSetup() {
	showCur(false);
	disableSelection();
	setWindowSize(300, 300);
	disableResizeWindow();
	disableMaxButton();
	hideScrollBars();
}

void Common::goTo(SHORT posX, SHORT posY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

void Common::setColor(int backgound_color, int text_color) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;

	SetConsoleTextAttribute(hStdout, color_code);
}

int Common::getInput() {
	int input;
	input = _getch();
	switch (input) {
	case 0: case 224:
		switch (_getch()) {
		case 75:
			return 1;
		case 72:
			return 2;
		case 80:
			return 3;
		case 77:
			return 4;
		default:
			return -1;
		}
	case 27: //Esc
		return 0;
	case 13: //Enter
		return 5;
	case 66: case 98: //B
		return 6;
	case 80: case 112: //P
		return 7;
	case 72: case 104: //H
		return 8;
	case 77: case 109: //M
		return 9;
	default:
		return -1;
	}
}

void Common::showCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}

void Common::disableSelection() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

void Common::hideScrollBars() {
	ShowScrollBar(GetConsoleWindow(), SB_BOTH, 0);
}

void Common::setWindowSize(SHORT width, SHORT height) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void Common::disableResizeWindow() {
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void Common::disableMaxButton() {
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
}

void Common::exitOutput(int i) {
	if (i == 1) {
		Menu::menuOutput();
	}
	system("cls");
	Common::goTo(centerX, exitY);
	cout << "DO YOU WANT TO EXIT?";
	int x = centerX;
	int y = ansY;
	Common::goTo(x, y);
	cout << "> " << exitList[0];
	y += distY;
	Common::goTo(x, y);
	cout << exitList[1];
	exitInput();
}

void Common::exitInput() {
	int slti = 0;
	int input = -1;
	int x = centerX;
	int y = ansY;
	do {
		input = Common::getInput();
		switch (input) {
		case 3:
			if (slti == 0) {
				Common::goTo(x, y);
				cout << exitList[0] << "  ";
				y += distY;
				slti++;
				Common::goTo(x, y);
				cout << "> " << exitList[1];
			}
			break;
		case 2:
			if (slti == 1) {
				Common::goTo(x, y);
				cout << exitList[1] << "  ";
				y -= distY;
				slti--;
				Common::goTo(x, y);
				cout << "> " << exitList[0];
			}
			break;
		case 5:
			if (slti == 0) {
				input = 0;
			}
			else {
				Menu::menuOutput();
			}
			break;
		}
	} while (input != 0);
	system("cls");
	exit(0);
}