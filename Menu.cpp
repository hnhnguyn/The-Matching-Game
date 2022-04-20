#include "Menu.h"

string Menu::name;
double Menu::time;
const string Menu::menuList[5] = { "PLAY", "LEADERBOARD", "TUTORIAL", "ABOUT", "EXIT"};
const string Menu::playList[3] = { "STANDARD", "DIFFICULT", "BACK TO MENU" };
const string Menu::doneList[2] = { "NEW GAME", "BACK TO MENU" };

Menu::Menu() {
	Common::consoleSetup();
	titleOutput();
	menuOutput();
}

void Menu::titleOutput() {
	string title;
	ifstream in;
	in.open("title.txt");
	while (!in.eof()) {
		getline(in, title);
		cout << title << endl;
	}
	in.close();
}

void Menu::menuOutput() {
	system("cls");
	name = "";
	titleOutput();
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
				Common::selectsound();
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
				Common::selectsound();
			}
			break;
		case 5:
			if (slti == 0) {
				menuGetName();
			}
			else if (slti == 1) {
				menuLeaderboard();
			}
			else if (slti == 2) {
				menuTutorial();
			} 
			else if (slti == 3) {
				menuAbout();
			}
			else if (slti == 4) {
				Common::exitOutput(0);
				slti = 0;
			}
			break;
		}
	} while (input != 0);
	Common::exitOutput(0);
}

void Menu::menuGetName() {
	system("cls");
	Common::showCur(true);
	Common::goTo(centerX, playY);
	cout << "Enter your name: ";
	nameInput();
}

void Menu::nameInput() {
	for (int i = 0; i < 10; i++) {
		int input = _getch();
		if (input == 0 || input == 224) {
			input = _getch();
			i--;
		}
		else {
			if ((48 <= input && input <= 57) ||
				(65 <= input && input <= 90) ||
				(97 <= input && input <= 122)) {
				cout << char(input);
				name += char(input);
			}
			else if (input == 13) {
				if (i != 0) {
					Common::showCur(false);
					menuPlayOutput();
				}
				else {
					i--;
				}
			}
			else if (input == 27) {
				Common::showCur(false);
				Common::exitOutput(1);
			}
			else if (input == 8) {
				name = "";
				menuGetName();
			}
			else {
				i--;
			}
		}
	}
	Common::showCur(false);
	int input;
	do {
		input = _getch();
		if (input == 27) {
			Common::showCur(false);
			Common::exitOutput(1);
		}
		else if (input == 8) {
			name = "";
			menuGetName();
		}
	} while (input != 13);
	menuPlayOutput();
}

void Menu::menuPlayOutput() {
	system("cls");
	Common::goTo(centerX, playY);
	Common::selectsound();
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
				GameStandard::GameStandard();
			}
			else if (slti == 1) {
				GameDifficult::GameDifficult();
			}
			else if (slti == 2) {
				menuOutput();
			}
			break;
		}
	} while (input != 0);
	Common::exitOutput(1);
}

void Menu::printLeadBoard() {
	Common::goTo(centerX - 1, leadBoardY - distY);
	for (int i = 0; i < 23; i++) {
		cout << '_';
	}
	Common::goTo(centerX - 1, leadBoardY + 1);
	for (int i = 0; i < 23; i++) {
		cout << '_';
	}
	Common::goTo(centerX - 1, botY - distY - 1);
	for (int i = 0; i < 23; i++) {
		cout << '_';
	}
	for (int i = 1; i < 16; i++) {
		Common::goTo(centerX - 2, leadBoardY - distY + i);
		cout << '|';
	}
	for (int i = 1; i < 16; i++) {
		Common::goTo(centerX + distX * 3, leadBoardY - distY + i);
		cout << '|';
	}
	for (int i = 1; i < 16; i++) {
		Common::goTo(centerX + distX * 5 + 2, leadBoardY - distY + i);
		cout << '|';
	}
}

void Menu::menuLeaderboard() {
	system("cls");
	int x = leadTitleX;
	int y = leadTitleY;
	string s, name, time;
	string title;
	ifstream in;
	in.open("leaderboard.txt");
	while (!in.eof()) {
		Common::goTo(x, y);
		getline(in, title);
		cout << title << endl;
		y++;
	}
	in.close();
	x = centerX;
	y = leadBoardY;
	Common::goTo(x, y);
	cout << "NAME";
	Common::goTo(x + (distX * 4), y);
	cout << "SCORE";
	y += distY + 1;
	in.open("topPlayers.txt");
	in.ignore();
	while (!in.eof()) {
		getline(in, s);
		stringstream ss(s);
		Common::goTo(x, y);
		getline(ss, name, ' ');
		cout << name;
		x += distX * 4;
		Common::goTo(x, y);
		getline(ss, time);
		cout << setprecision(2) << fixed << stod(time);
		x = centerX;
		y++;
	}
	in.close(); 
	printLeadBoard();
	Common::goTo(centerX + distX, botY);
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
	Common::exitOutput(1);
}

void Menu::menuTutorial() {
	system("cls");
	string tuto;
	ifstream in;
	in.open("tutorial.txt");
	while (!in.eof()) {
		getline(in, tuto);
		cout << tuto << endl;
	}
	in.close();
	Common::goTo(centerX + distX, botY);
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
	Common::exitOutput(1);
}

void Menu::menuAbout() {
	system("cls");
	ifstream in;
	string line;
	in.open("about.txt");
	while (!in.eof()) {
		getline(in, line);
		cout << line << endl;
	}
	in.close();
	Common::goTo(centerX + distX, botY);
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
	Common::exitOutput(1);
}

void Menu::menuDoneOutput(double time_taken) {
	system("cls");
	time = time_taken;
	Common::goTo(centerX, resultY);
	cout << "ALL MATCHED";
	Common::goTo(centerX, resultY + distY);
	cout << "YOUR TIME: " << setprecision(2) << fixed << time <<"s";
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
	Menu::topPlayCheck();
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

struct Player {
	string _name;
	string _time;
};

void Menu::topPlayCheck() {
	Player players[11];
	ifstream in;
	int n = 0;
	in.open("topPlayers.txt");
	in.ignore();
	if (!in.eof()) {
		while (!in.eof()) {
			getline(in, players[n]._name, ' ');
			getline(in, players[n]._time);
			n++;
		}
		in.close();
		players[n]._name = name;
		stringstream s;
		s << time;
		players[n]._time = s.str();
		for (int i = n; i > 0; i--) {
			if (stod(players[i - 1]._time) > stod(players[i]._time)) {
				swap(players[i], players[i - 1]);
			}
		}
		ofstream out;
		out.open("topPlayers.txt");
		if (n >= 10) {
			n = 9;
		}
		for (int i = 0; i <= n; i++) {
			out << endl << players[i]._name << " " << players[i]._time;
		}
		out.close();
	}
	else {
		stringstream s;
		s << time;
		ofstream out;
		out.open("topPlayers.txt");
		out << endl << name << " " << s.str();
		out.close();
	}
}