#include "Game.h"
const string Game::gameBtnList[3] = { "BACK TO MENU: B", "PAUSE: P", "MUSIC: M" };
const string Game::menuBackList[2] = { "YES", "NO" };
const string Game::pauseList[3] = { "RESUME", "REPLAY", "BACK TO MENU" };

Game::Game() {
	Common::consoleSetup();
	gameOutput(_Arr.getRow(), _Arr.getCol());
}

void Game::selectColor(int x, int y, int background, int text, int i, int j) {
	Common::goTo(x, y);
	Common::setColor(background, text);
	cout << _Arr.getArrElement(i, j);
	Common::setColor(BLACK, WHITE);
}

void Game::gameOutput(int row, int col) {
	system("cls");
	for (int i = 0; i < sizeof(gameBtnList) / sizeof(gameBtnList[0]); i++) {
		int x = btnX;
		int y = btnY + distY * i;
		Common::goTo(x, y);
		cout << gameBtnList[i];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int x = gameX + distX * j;
			int y = gameY + distY * i;
			Common::goTo(x, y);
			if (x == gameX && y == gameY) {
				Common::setColor(GRAY, BRIGHT_WHITE);
				cout << _Arr.getArrElement(i, j);
				Common::setColor(BLACK, WHITE);
			}
			else {
				cout << _Arr.getArrElement(i, j);
			}
		}
	}
	inputProcess(_Arr.getRow(), _Arr.getCol());
}

void Game::inputProcess(int row, int col) {
	int sltRow = 0, sltCol = 0;
	int input = -1;
	int x = gameX + distX * sltRow;
	int y = gameY + distY * sltCol;
	int sltedX = -1, sltedY = -1, sltedRow = -1, sltedCol = -1, sltCnt = 0;
	int chCnt = 0;
	do {
		input = Common::getInput();
		switch (input) {
		case 1: //LEFT
			if (sltCol != 0) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltRow, sltCol);
				}
				else {
					cout << _Arr.getArrElement(sltRow, sltCol);
					
				}
				sltCol--;
				x -= distX;
				selectColor(x, y, GRAY, BRIGHT_WHITE, sltRow, sltCol);
			}
			break;
		case 2: //UP
			if (sltRow != 0) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltRow, sltCol);
				}
				else {
					cout << _Arr.getArrElement(sltRow, sltCol);

				}
				sltRow--;
				y -= distY;
				Common::goTo(x, y);
				selectColor(x, y, GRAY, BRIGHT_WHITE, sltRow, sltCol);
			}
			break;
		case 3: //DOWN
			if (sltRow != row - 1) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltRow, sltCol);
				}
				else {
					cout << _Arr.getArrElement(sltRow, sltCol);

				}
				sltRow++;
				y += distY;
				selectColor(x, y, GRAY, BRIGHT_WHITE, sltRow, sltCol);
			}
			break;
		case 4: //RIGHT
			if (sltCol != col - 1) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltRow, sltCol);
				}
				else {
					cout << _Arr.getArrElement(sltRow, sltCol);

				}
				sltCol++;
				x += distX;
				selectColor(x, y, GRAY, BRIGHT_WHITE, sltRow, sltCol);
			}
			break;
		case 5: //SPACE / ENTER
			if(_Arr.getArrElement(sltRow, sltCol) != ' ') {
				if (sltedRow == sltRow && sltedCol == sltCol) {
					Common::goTo(x, y);
					selectColor(x, y, GRAY, BRIGHT_WHITE, sltRow, sltCol);
					sltedRow = -1;
					sltedCol = -1;
					sltCnt = 0;
				}
				else {
					sltCnt++;
					if (sltCnt == 1) {
						sltedX = x;
						sltedY = y;
						sltedRow = sltRow;
						sltedCol = sltCol;
					}
					else if (sltCnt == 2) {
						if (Game::matchCheck(sltedRow, sltedCol, sltRow, sltCol)) {
							_Arr.setArrElement(sltedRow, sltedCol, ' ');
							selectColor(sltedX, sltedY, BLACK, WHITE, sltedRow, sltedCol);
							_Arr.setArrElement(sltRow, sltCol, ' ');
							selectColor(x, y, GRAY, BRIGHT_WHITE, sltRow, sltCol);
							chCnt += 2;
						}
						else {
							selectColor(sltedX, sltedY, BLACK, WHITE, sltedRow, sltedCol);
							sltedX = -1;
							sltedY = -1;
							Common::goTo(x, y);
						}
						sltCnt = 0;
					}
				}
			}
			break;
		case 6: //B
			menuBackScreen();
			break;
		case 7: //P
			pauseScreen();
			break;

		}
		if (chCnt == row * col) {
			selectColor(x, y, BLACK, WHITE, sltRow, sltCol);
			Common::goTo(gameX + distX * col, gameY + distY * row);
			cout << "CONGRATS" << endl;
		}
	} while (true);
}

bool Game::matchCheck(int preRow, int preCol, int postRow, int postCol) {
	if (_Arr.getArrElement(preRow, preCol) == _Arr.getArrElement(postRow, postCol)) {
		if (preRow == postRow) {
			if (preRow == 0 || preRow == _Arr.getRow() - 1 || checkIMatch(preRow, preCol, postRow, postCol)) {
				return 1;
			}
		}
		if (preCol == postCol) {
			if (preCol == 0 || preCol == _Arr.getCol() - 1 || checkIMatch(preRow, preCol, postRow, postCol)) {
				return 1;
			}
		}
		if (checkLMatch(preRow, preCol, postRow, postCol)) {
			return 1;
		}
		return 0;
	}
	else {
		return 0;
	}
}

bool Game::checkIMatch(int preRow, int preCol, int postRow, int postCol) {
	int check = 1;
	if (preRow == postRow) {
		int row = preRow;
		if (preCol > postCol) {
			swap(preCol, postCol);
		}
		for (int j = preCol + 1; j < postCol; j++) {
			if (_Arr.getArrElement(row, j) != ' ') {
				check = 0;
			}
		}
	}
	else if (preCol == postCol) {
		int col = preCol;
		if (preRow > postRow) {
			swap(preRow, postRow);
		}
		for (int i = preRow + 1; i < postRow; i++) {
			if (_Arr.getArrElement(i, col) != ' ') {
				check = 0;
			}
		}
	}
	return check;
}

bool Game::checkLMatch(int preRow, int preCol, int postRow, int postCol) {
	if (preRow > postRow) {
		swap(preRow, postRow);
		swap(preCol, postCol);
	}
	if (checkIMatch(preRow, preCol, preRow, postCol) && _Arr.getArrElement(preRow, postCol) == ' ' && checkIMatch(preRow, postCol, postRow, postCol)) {
		return 1;
	}
	if (checkIMatch(preRow, preCol, postRow, preCol) && _Arr.getArrElement(postRow, preCol) == ' ' && checkIMatch(postRow, preCol, postRow, postCol)) {
		return 1;
	}
	return 0;
}

void Game::menuBackScreen() {
	system("cls");
	Common::goTo(centerX, exitY);
	cout << "DO YOU WANT TO GO BACK TO MENU?";
	int x = centerX;
	int y = ansY;
	Common::goTo(x, y);
	cout << "> " << menuBackList[0];
	y += distY;
	Common::goTo(x, y);
	cout << menuBackList[1];
	menuBackInput();
}

void Game::menuBackInput() {
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
				cout << menuBackList[0] << "  ";
				y += distY;
				slti++;
				Common::goTo(x, y);
				cout << "> " << menuBackList[1];
			}
			break;
		case 2:
			if (slti == 1) {
				Common::goTo(x, y);
				cout << menuBackList[1] << "  ";
				y -= distY;
				slti--;
				Common::goTo(x, y);
				cout << "> " << menuBackList[0];
			}
			break;
		case 5:
			if (slti == 0) {
				input = 0;
			}
			else {
				Game::gameOutput(_Arr.getRow(), _Arr.getCol());
			}
			break;
		}
	} while (input != 0);
	Menu::Menu();
}

void Game::pauseScreen() {
	system("cls");
	for (int i = 0; i < sizeof(pauseList) / sizeof(pauseList[0]); i++) {
		int x = centerX;
		int y = menuY + i * distY;
		Common::goTo(x, y);
		if (y == menuY) {
			cout << "> ";
		}
		cout << pauseList[i];
	}
	pauseInput();
}

void Game::pauseInput() {
	int slti = 0;
	int input = -1;
	int x = centerX;
	int y = menuY + distY * slti;
	do {
		input = Common::getInput();
		switch (input) {
		case 3:
			if (slti != (sizeof(pauseList) / sizeof(pauseList[0]) - 1)) {
				Common::goTo(x, y);
				cout << pauseList[slti] << "  ";
				slti++;
				y += distY;
				Common::goTo(x, y);
				cout << "> " << pauseList[slti];
			}
			break;
		case 2:
			if (slti != 0) {
				Common::goTo(x, y);
				cout << pauseList[slti] << "  ";
				slti--;
				y -= distY;
				Common::goTo(x, y);
				cout << "> " << pauseList[slti];
			}
			break;
		case 5:
			if (slti == 0) {
				gameOutput(_Arr.getRow(), _Arr.getCol());
			}
			else if (slti == 1) {
				Menu::menuPlayOutput();
			}
			else if (slti == 2) {
				input = 0;
			}
			break;
		}
	} while (input != 0);
	Menu::Menu();
}

