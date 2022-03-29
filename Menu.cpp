#include "Menu.h"

const string Menu::menuList[4] = { "PLAY", "TUTORIAL", "ABOUT", "EXIT" };
const string Menu::playList[4] = { "EASY", "MEDIUM", "HARD", "BACK TO MENU" };
const string Menu::doneList[3] = { "NEW GAME", "BACK TO MENU" };

Menu::Menu() {
	Common::consoleSetup();
	titleOutput();
	menuOutput();
}

void Menu::titleOutput() {

}

void Menu::menuOutput() {
	system("cls");
	for (int i = 0; i < sizeof(menuList) / sizeof(menuList[0]); i++) {
		int x = centerX;
		int y = menuY + i * distY;
		Common::goTo(x, y);
		if (y == menuY) {
			cout << "> ";
		}
		cout << menuList[i];
	}
	menuInput();
}

void Menu::menuInput() {
	int slti = 0;
	int input = -1;
	int x = centerX;
	int y = menuY + distY * slti;
	do {
		input = Common::getInput();
		switch (input) {
		case 3:
			if (slti != (sizeof(menuList) / sizeof(menuList[0]) - 1)) {
				Common::goTo(x, y);
				cout << menuList[slti] << "  ";
				slti++;
				y += distY;
				Common::goTo(x, y);
				cout << "> " << menuList[slti];
			}
			break;
		case 2:
			if (slti != 0) {
				Common::goTo(x, y);
				cout << menuList[slti] << "  ";
				slti--;
				y -= distY;
				Common::goTo(x, y);
				cout << "> " << menuList[slti];
			}
			break;
		case 5:
			if (slti == 0) {
				menuPlayOutput();
			} 
			else if (slti == 1) {
				menuTutorial();
			} 
			else if (slti == 2) {
				menuAbout();
			}
			else if (slti == 3) {
				Common::exitOutput(1);
				slti = 0;
			}
			break;
		}
	} while (input != 0);
	Common::exitOutput(1);
}

void Menu::menuPlayOutput() {
	system("cls");
	Common::goTo(centerX, playY);
	for (int i = 0; i < sizeof(playList) / sizeof(playList[0]); i++) {
		int x = centerX;
		int y = playY + i * distY;
		Common::goTo(x, y);
		if (y == playY) {
			cout << "> ";
		}			
		cout << playList[i];
	}
	menuPlayInput();
}

void Menu::menuPlayInput() {
	int slti = 0;
	int input = -1;
	int x = centerX;
	int y = playY + distY * slti;
	do {
		input = Common::getInput();
		switch (input) {
		case 3:
			if (slti != (sizeof(playList) / sizeof(playList[0]) - 1)) {
				Common::goTo(x, y);
				cout << playList[slti] << "  ";
				slti++;
				y += distY;
				Common::goTo(x, y);
				cout << "> " << playList[slti];
			}
			break;
		case 2:
			if (slti != 0) {
				Common::goTo(x, y);
				cout << playList[slti] << "  ";
				slti--;
				y -= distY;
				Common::goTo(x, y);
				cout << "> " << playList[slti];
			}
			break;
		case 5:
			if (slti == 0) {
				Game::Game(4);
			}
			else if (slti == 1) {
				Game::Game(6);
			}
			else if (slti == 2) {
				Game::Game(8);
			}
			else if (slti == 3) {
				menuOutput();
			}
			break;
		}

	} while (input != 0);
	Common::exitOutput(2);
}

void Menu::menuTutorial() {
	system("cls");
	Common::goTo(centerX, botY);
	cout << "> BACK TO MENU";
	int input = -1;
	do {
		input = Common::getInput();
		switch (input) {
		case 5:
			menuOutput();
			break;
		}
	} while (input != 0);
	Common::exitOutput(3);
}

void Menu::menuAbout() {
	system("cls");
	Common::goTo(centerX, botY);
	cout << "> BACK TO MENU";
	int input = -1;
	do {
		input = Common::getInput();
		switch (input) {
		case 5:
			menuOutput();
			break;
		}
	} while (input != 0);
	Common::exitOutput(4);
}

void Menu::menuDoneOutput() {
	system("cls");
	Common::goTo(centerX, playY);
	for (int i = 0; i < sizeof(doneList) / sizeof(doneList[0]); i++) {
		int x = centerX;
		int y = menuY + i * distY;
		Common::goTo(x, y);
		if (y == menuY) {
			cout << "> ";
		}
		cout << doneList[i];
	}
	Menu::menuDoneInput();
}

void Menu::menuDoneInput() {
	int slti = 0;
	int input = -1;
	int x = centerX;
	int y = menuY + distY * slti;
	do {
		input = Common::getInput();
		switch (input) {
		case 3:
			if (slti != (sizeof(doneList) / sizeof(doneList[0]) - 1)) {
				Common::goTo(x, y);
				cout << doneList[slti] << "  ";
				slti++;
				y += distY;
				Common::goTo(x, y);
				cout << "> " << doneList[slti];
			}
			break;
		case 2:
			if (slti != 0) {
				Common::goTo(x, y);
				cout << doneList[slti] << "  ";
				slti--;
				y -= distY;
				Common::goTo(x, y);
				cout << "> " << doneList[slti];
			}
			break;
		case 5:
			if (slti == 0) {
				menuPlayOutput();
			}
			else if (slti == 1) {
				menuOutput();
			}
			break;
		}
	} while (input != 0);
	Common::exitOutput(1);
}

