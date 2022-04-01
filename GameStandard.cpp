#include "GameStandard.h"
const string GameStandard::gameBtnList[4] = { "BACK TO MENU: B", "PAUSE: P", "HINT: H"};
const string GameStandard::menuBackList[2] = { "YES", "NO" };
const string GameStandard::pauseList[3] = { "RESUME", "REPLAY", "BACK TO MENU" };

GameStandard::GameStandard() {
	Common::consoleSetup();
	charArr.arr = charArr.gen2DArr(size, size, size * size);
	chCnt = 0;
	time_taken = 0;
	gameX = centerX - size / 2;
	gameOutput();
}

void GameStandard::selectColor(int x, int y, int background, int text, int i, int j) {
	Common::goTo(x, y);
	Common::setColor(background, text);
	cout << " " << charArr.arr[i][j] << " ";
	Common::setColor(BLACK, WHITE);
}

bool GameStandard::checkMove() {
	char c;
	for (int i = 0; i < size * size; i++) {
		if (charArr.arr[i / size][i % size] != ' ') {
			c = charArr.arr[i / size][i % size];
		}
		else {
			continue;
		}
		for (int j = i + 1; j < size * size; j++) {
			if (charArr.arr[j / size][j % size] == c) {
				if (matchCheck(i / size, i % size, j / size, j % size)) {
					sg.ch = c;
					sg.preRow = i / size;
					sg.preCol = i % size;
					sg.postRow = j / size;
					sg.postCol = j % size;
					return 1;
				}
			}
		}
	}
	return 0;
}

void GameStandard::shuffle() {
	bool* check = new bool[size * size];
	for (int i = 0; i < size * size; i++) {
		check[i] = 0;
	}
	int* position = new int[size * size];
	for (int i = 0; i < size * size; i++) {
		int tmp;
		do {
			tmp = rand() % (size * size);
		} while (check[tmp]);
		check[tmp] = 1;
		position[i] = tmp;
	}
	char** tmpCh;
	tmpCh = new char* [size];
	for (int i = 0; i < size; i++) {
		tmpCh[i] = new char [size];
	}
	for (int i = 0; i < size * size; i++) {
		tmpCh[position[i] / size][position[i] % size] = charArr.arr[i / size][i % size];
	}
	for (int i = 0; i < size * size; i++) {
		charArr.arr[i / size][i % size] = tmpCh[i / size][i % size];
	}

	delete[] check;
	delete[] position;
	for (int i = 0; i < size; i++) {
		delete[] tmpCh[i];
	}
	delete[] tmpCh;
}

void GameStandard::gameOutput() {
	system("cls");
	while (!checkMove()) {
		shuffle();
	}
	for (int i = 0; i < sizeof(gameBtnList) / sizeof(gameBtnList[0]); i++) {
		int x = btnX;
		int y = btnY + distY * i;
		Common::goTo(x, y);
		cout << gameBtnList[i];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
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
	inputProcess();
}

void GameStandard::inputProcess() {
	int sltRow = 0, sltCol = 0;
	int input = -1;
	int x = gameX + distX * sltRow;
	int y = gameY + distY * sltCol;
	int sltedX = -1, sltedY = -1, sltedRow = -1, sltedCol = -1, sltCnt = 0;
	int hint = 0;
	time = clock();
	do {
		if (!checkMove()) {
			time_taken += (clock() - time) / CLOCKS_PER_SEC;
			gameOutput();
		}
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
			if (sltRow != size - 1) {
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
			if (sltCol != size - 1) {
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
		case 5: //ENTER
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
						if (GameStandard::matchCheck(sltedRow, sltedCol, sltRow, sltCol)) {
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
						if (hint == 1) {
							hint = 0;
							Common::goTo(0, 0);
							cout << " " << endl;
							cout << "    " << endl;
							cout << "    " << endl;
						}
						sltCnt = 0;
					}
				}
			}
			break;
		case 6: //B
			Menu::menuOutput();
			break;
		case 7: //P
			time_taken += (clock() - time) / (CLOCKS_PER_SEC);
			pauseScreen();
			break;
		case 8: //H
			hint++;
			Common::goTo(0, 0);
			cout << sg.ch << endl;
			cout << sg.preRow << ", " << sg.preCol << endl;
			cout << sg.postRow << ", " << sg.postCol << endl;
			break;
		}
		if (chCnt == size * size) {
			time_taken += (clock() - time) / (CLOCKS_PER_SEC);
			Menu::menuDoneOutput(time_taken);
		}
	} while (input != 0);
	GameStandard::pauseScreen();
}

bool GameStandard::matchCheck(int preRow, int preCol, int postRow, int postCol) {
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

bool GameStandard::checkIMatch(int preRow, int preCol, int postRow, int postCol) {
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

bool GameStandard::checkLMatch(int preRow, int preCol, int postRow, int postCol) {
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

bool GameStandard::checkUMatch(int preRow, int preCol, int postRow, int postCol) {
	if (preCol == postCol) {
		if (preCol == 0 || preCol == size - 1) {
			return 1;
		}
	}
	if (preRow == postRow) {
		if (preRow == 0 || preRow == size - 1) {
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
	for (int i = postRow; i < size - 1; i++) {
		check++;
		if (checkIMatch(preRow, preCol, i + 1, preCol) && charArr.arr[i + 1][preCol] == ' ' && checkLMatch(i + 1, preCol, postRow, postCol)) {
			return 1;
		}
		if (i == size - 2) {
			if (checkIMatch(preRow, preCol, i + 1, preCol) && charArr.arr[i + 1][preCol] == ' ' && checkIMatch(i + 1, postCol, postRow, postCol) && charArr.arr[i + 1][postCol] == ' ') {
				return 1;
			}
		}
	}
	if (check == 0) {
		if (checkIMatch(preRow, preCol, size - 1, preCol) && charArr.arr[size - 1][preCol] == ' ') {
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
		for (int i = postCol + 1; i < size; i++) {
			check++;
			if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkLMatch(preRow, i, postRow, postCol)) {
				return 1;
			}
			if (i == size - 1) {
				if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkIMatch(postRow, postCol, postRow, i) && charArr.arr[postRow][i] == ' ') {
					return 1;
				}
			}
		}
		if (check == 0) {
			if (checkIMatch(preRow, preCol, preRow, size - 1) && charArr.arr[preRow][size - 1] == ' ') {
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
		for (int i = preCol + 1; i < size; i++) {
			check++;
			if (checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ' && checkLMatch(preRow, i, postRow, postCol)) {
				return 1;
			}
			if (i == size - 1) {
				if (checkIMatch(postRow, postCol, postRow, i) && charArr.arr[postRow][i] == ' ' && checkIMatch(preRow, preCol, preRow, i) && charArr.arr[preRow][i] == ' ') {
					return 1;
				}
			}
		}
		if (check == 0) {
			if (checkIMatch(postRow, postCol, postRow, size - 1) && charArr.arr[postRow][size - 1] == ' ') {
				return 1;
			}
		}
	}
	return 0;
}

bool GameStandard::checkZMatch(int preRow, int preCol, int postRow, int postCol) {
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

void GameStandard::pauseScreen() {
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

void GameStandard::pauseInput() {
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
				gameOutput();
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

