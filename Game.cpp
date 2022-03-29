#include "Game.h"
const string Game::gameBtnList[3] = { "BACK TO MENU: B", "PAUSE: P" };
const string Game::menuBackList[2] = { "YES", "NO" };
const string Game::pauseList[3] = { "RESUME", "REPLAY", "BACK TO MENU" };

Game::Game(int n) {
	Common::consoleSetup();
	charArr.row = n; 
	charArr.col = n;
	charArr.arr = charArr.gen2DArr(charArr.gen1DArr(charArr.row * charArr.col), charArr.row, charArr.col);
	gameX = centerX - (n - 4);
	gameOutput(charArr.row, charArr.col);
}


void Game::selectColor(int x, int y, int background, int text, int i, int j) {
	Common::goTo(x, y);
	Common::setColor(background, text);
	cout << " " << charArr.arr[i][j] << " ";
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
				Common::setColor(BRIGHT_WHITE, BLACK);
				cout << " " << charArr.arr[i][j] << " ";
				Common::setColor(BLACK, WHITE);
			}
			else {
				cout << " " << charArr.arr[i][j] << " ";
			}
		}
	}
	inputProcess(charArr.row, charArr.col);
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
					cout << " " << charArr.arr[sltRow][sltCol] << " ";
					
				}
				sltCol--;
				x -= distX;
				selectColor(x, y, BRIGHT_WHITE, BLACK, sltRow, sltCol);
			}
			break;
		case 2: //UP
			if (sltRow != 0) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltRow, sltCol);
				}
				else {
					cout << " " << charArr.arr[sltRow][sltCol] << " ";

				}
				sltRow--;
				y -= distY;
				Common::goTo(x, y);
				selectColor(x, y, BRIGHT_WHITE, BLACK, sltRow, sltCol);
			}
			break;
		case 3: //DOWN
			if (sltRow != row - 1) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltRow, sltCol);
				}
				else {
					cout << " " << charArr.arr[sltRow][sltCol] << " ";

				}
				sltRow++;
				y += distY;
				selectColor(x, y, BRIGHT_WHITE, BLACK, sltRow, sltCol);
			}
			break;
		case 4: //RIGHT
			if (sltCol != col - 1) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltRow, sltCol);
				}
				else {
					cout << " " << charArr.arr[sltRow][sltCol] << " ";

				}
				sltCol++;
				x += distX;
				selectColor(x, y, BRIGHT_WHITE, BLACK, sltRow, sltCol);
			}
			break;
		case 5: //SPACE / ENTER
			if(charArr.arr[sltRow][sltCol] != ' ') {
				if (sltedRow == sltRow && sltedCol == sltCol) {
					Common::goTo(x, y);
					selectColor(x, y, BRIGHT_WHITE, BLACK, sltRow, sltCol);
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
							charArr.arr[sltedRow][sltedCol] = ' ';
							selectColor(sltedX, sltedY, BLACK, WHITE, sltedRow, sltedCol);
							charArr.arr[sltRow][sltCol] = ' ';
							selectColor(x, y, BRIGHT_WHITE, BLACK, sltRow, sltCol);
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
			Menu::menuDoneOutput();
		}
	} while (true);
}

bool Game::matchCheck(int preRow, int preCol, int postRow, int postCol) {
	if (charArr.arr[preRow][preCol] == charArr.arr[postRow][postCol]) {
		if (preRow == postRow || preCol == postCol) {
			if (checkIMatch(preRow, preCol, postRow, postCol)) {
				return 1;
			}
		}
		if (checkLMatch(preRow, preCol, postRow, postCol)) {
			return 1;
		}
		if (checkUMatch(preRow, preCol, postRow, postCol)) {
			return 1;
		}
		if (checkZMatch(preRow, preCol, postRow, postCol)) {
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
	if (preRow > postRow) {
		swap(preRow, postRow);
		swap(preCol, postCol);
	}
	if (preCol == postCol) {
		for (int i = preRow + 1; i < postRow; i++) {
			if (charArr.arr[i][preCol] != ' ') {
				check = 0;
			}
		}
	}
	if (preRow == postRow) {
		if (preCol < postCol) {
			for (int i = preCol + 1; i < postCol; i++) {
				if (charArr.arr[preRow][i] != ' ') {
					check = 0;
				}
			}
		}
		else {
			for (int i = postCol +1; i < preCol; i++) {
				if (charArr.arr[preRow][i] != ' ') {
					check = 0;
				}
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
	if (checkIMatch(preRow, preCol, preRow, postCol) && charArr.arr[preRow][postCol] == ' ' && checkIMatch(preRow, postCol, postRow, postCol)) {
		return 1;
	}
	if (checkIMatch(preRow, preCol, postRow, preCol) && charArr.arr[postRow][preCol] == ' ' && checkIMatch(postRow, preCol, postRow, postCol)) {
		return 1;
	}
	return 0;
}

bool Game::checkUMatch(int preRow, int preCol, int postRow, int postCol) {
	if (preCol == postCol) {
		if (preCol == 0 || preCol == charArr.col - 1) {
			return 1;
		}
	}
	if (preRow == postRow) {
		if (preRow == 0 || preRow == charArr.row - 1) {
			return 1;
		}
	} else if (preRow > postRow) {
		swap(preRow, postRow);
		swap(preCol, postCol);
	}
	int check = 0;
	for (int i = preRow; i > 0; i--) {
		check++;
		if (checkIMatch(preRow, preCol, i - 1, preCol) && charArr.arr[i - 1][preCol] == ' ' && checkLMatch(i - 1, preCol, postRow, postCol)) {
			return 1;
		}
		if (i == 1) {
			if (checkIMatch(preRow, preCol, i - 1, preCol) && charArr.arr[i - 1][preCol] == ' ' && checkIMatch(i - 1, postCol, postRow, postCol) && charArr.arr[i - 1][postCol] == ' ') {
				return 1;
			}
		}
	}
	if (check == 0) {
		if (checkIMatch(postRow, postCol, 0, postCol) && charArr.arr[0][postCol] == ' ') {
			return 1;
		}
	}
	check = 0;
	for (int i = postRow; i < charArr.row - 1; i++) {
		check++;
		if (checkIMatch(preRow, preCol, i + 1, preCol) && charArr.arr[i + 1][preCol] == ' ' && checkLMatch(i + 1, preCol, postRow, postCol)) {
			return 1;
		}
		if (i == charArr.row - 2) {
			if (checkIMatch(preRow, preCol, i + 1, preCol) && charArr.arr[i + 1][preCol] == ' ' && checkIMatch(i + 1, postCol, postRow, postCol) && charArr.arr[i + 1][postCol] == ' ') {
				return 1;
			}
		}
	}
	if (check == 0) {
		if (checkIMatch(preRow, preCol, charArr.row - 1, preCol) && charArr.arr[charArr.row - 1][preCol] == ' ') {
			return 1;
		}
	}
	check = 0;
	if (preCol <= postCol) {
		for (int i = 0; i < preCol; i++) {
			check++;
			if (i == 0) {
				if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkIMatch(postRow, postCol, postRow, i) && charArr.arr[postRow][i] == ' ') {
					return 1;
				}
			}
			if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkLMatch(preRow, i, postRow, postCol)) {
				return 1;
			}
		}
		if (check == 0) {
			if (checkIMatch(postRow, 0, postRow, postCol) && charArr.arr[postRow][0] == ' ') {
				return 1;
			}
		}
		check = 0;
		for (int i = postCol + 1; i < charArr.col; i++) {
			check++;
			if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkLMatch(preRow, i, postRow, postCol)) {
				return 1;
			}
			if (i == charArr.col - 1) {
				if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkIMatch(postRow, postCol, postRow, i) && charArr.arr[postRow][i] == ' ') {
					return 1;
				}
			}
		}
		if (check == 0) {
			if (checkIMatch(preRow, preCol, preRow, charArr.col - 1) && charArr.arr[preRow][charArr.col - 1] == ' ') {
				return 1;
			}
		}
	}
	else {
		for (int i = 0; i < postCol; i++) {
			check++;
			if (i == 0) {
				if (checkIMatch(postRow, postCol, postRow, i) && charArr.arr[postRow][i] == ' ' && checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ') {
					return 1;
				}
			}
			if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkLMatch(preRow, i, postRow, postCol)) {
				return 1;
			}
		}
		if (check == 0) {
			if (checkIMatch(preRow, 0, preRow, preCol) && charArr.arr[preRow][0] == ' ') {
				return 1;
			}
		}
		check = 0;
		for (int i = preCol + 1; i < charArr.col; i++) {
			check++;
			if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkLMatch(preRow, i, postRow, postCol)) {
				return 1;
			}
			if (i == charArr.col - 1) {
				if (checkIMatch(postRow, postCol, postRow, i) && charArr.arr[postRow][i] == ' ' && checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ') {
					return 1;
				}
			}
		}
		if (check == 0) {
			if (checkIMatch(postRow, postCol, postRow, charArr.col - 1) && charArr.arr[postRow][charArr.col - 1] == ' ') {
				return 1;
			}
		}
	}
	return 0;
}

bool Game::checkZMatch(int preRow, int preCol, int postRow, int postCol) {
	if (preRow > postRow) {
		swap(preRow, postRow);
		swap(preCol, postCol);
	}
	for (int i = preRow + 1; i < postRow; i++) {
		if (checkIMatch(preRow, preCol, i, preCol) && charArr.arr[i][preCol] == ' ' && checkLMatch(i, preCol, postRow, postCol)) {
			return 1;
		}
	}
	if (preCol < postCol) {
		for (int i = preCol + 1; i < postCol; i++) {
			if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkLMatch(preRow, i, postRow, postCol)) {
				return 1;
			}
		}
	}
	else {
		for (int i = postCol + 1; i < preCol; i++) {
			if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkLMatch(preRow, i, postRow, postCol)) {
				return 1;
			}
		}
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
				Game::gameOutput(charArr.row, charArr.col);
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
				gameOutput(charArr.row, charArr.col);
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

