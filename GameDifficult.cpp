#include "GameDifficult.h"
const string GameDifficult::gameBtnList[4] = { "BACK TO MENU: B", "PAUSE: P", "HINT: H" };
const string GameDifficult::menuBackList[2] = { "YES", "NO" };
const string GameDifficult::pauseList[3] = { "RESUME", "REPLAY", "BACK TO MENU" };

GameDifficult::GameDifficult() {
	Common::consoleSetup();
	L.Li = LinkedList::setList(size);
	chCnt = 0;
	time_taken = 0;
	gameX = centerX - size / 2;
	gameOutput();
}

void GameDifficult::selectColor(int x, int y, int background, int text, Node* ch) {
	Common::goTo(x, y);
	Common::setColor(background, text);
	std::cout << " " << ch->dt.ch << " ";
	Common::setColor(BLACK, WHITE);
}

//bool GameDifficult::checkMove() {
//	char c;
//	for (int i = 0; i < size * size; i++) {
//		if (LinkedList::findNode(L.Li[i / size], i / size, i % size)->dt.ch != ' ') {
//			c = LinkedList::findNode(L.Li[i / size], i / size, i % size)->dt.ch;
//		}
//		else {
//			continue;
//		}
//		for (int j = i + 1; j < size * size; j++) {
//			if (LinkedList::findNode(L.Li[j / size], j / size, j % size)->dt.ch == c) {
//				if (matchCheck(i / size, i % size, j / size, j % size)) {
//					return 1;
//				}
//			}
//		}
//	}
//	return 0;
//}

//void GameDifficult::shuffle() {
//	bool* check = new bool[size * size];
//	for (int i = 0; i < size * size; i++) {
//		check[i] = 0;
//	}
//	int* position = new int[size * size];
//	for (int i = 0; i < size * size; i++) {
//		int tmp;
//		do {
//			tmp = rand() % (size * size);
//		} while (check[tmp]);
//		check[tmp] = 1;
//		position[i] = tmp;
//	}
//	char** tmpCh;
//	tmpCh = new char* [size];
//	for (int i = 0; i < size; i++) {
//		tmpCh[i] = new char[size];
//	}
//	for (int i = 0; i < size * size; i++) {
//		tmpCh[position[i] / size][position[i] % size] = LinkedList::findNode(L.Li[i / size], i / size, i % size)->dt.ch;
//	}
//	for (int i = 0; i < size * size; i++) {
//		LinkedList::findNode(L.Li[i / size], i / size, i % size)->dt.ch = tmpCh[i / size][i % size];
//	}
//
//	delete[] check;
//	delete[] position;
//	for (int i = 0; i < size; i++) {
//		delete[] tmpCh[i];
//	}
//	delete[] tmpCh;
//}

void GameDifficult::printRow(List L, int i, int index) {
	int x = 0;
	int y = distY * i;
	Node* ch = L.head;
	while (ch) {
		Common::goTo(x, y);
		if (ch->dt.index == index) {
			selectColor(x, y, BRIGHT_WHITE, BLACK, ch);
		}
		else {
			cout << " " << ch->dt.ch << " ";
		}
		x += distX;
		ch = ch->chNext;
	}
	for (int i = 0; i < size - L.tail->dt.index; i++) {
		Common::goTo(x, y);
		cout << "   ";
		x += distX;
	}
}

void GameDifficult::printBoard() {
	int x = 0;
	int y = 0;
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			printRow(L.Li[i], i, 0);
		}
		else {
			printRow(L.Li[i], i, -1);
		}
	}
}

void GameDifficult::gameOutput() {
	system("cls");
	/*while (!checkMove()) {
		shuffle();
	}*/
	printBoard();
	inputProcess();
}

void GameDifficult::inputProcess() {
	int sltRow = 0;
	int sltIndex = 0;
	int sltedRow = -1;
	int sltedIndex = -1;
	Node* sltCh = LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex);
	Node* sltedCh = NULL;
	int input = -1;
	int x = 0;
	int y = 0;
	int sltedX = -1, sltedY = -1, sltCnt = 0;
	do {
		input = Common::getInput();
		switch (input) {
		case 1: //LEFT
			if (sltIndex != 0) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex));
				}
				else {
					cout << " " << sltCh->dt.ch << " ";
				}
				sltCh = sltCh->chPrev;
				sltIndex--;
				x -= distX;
				selectColor(x, y, BRIGHT_WHITE, BLACK, LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex));
			}
			break;
		case 2: //UP
			if (sltRow != 0) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex));
				}
				else {
					cout << " " << sltCh->dt.ch << " ";
				}
				while (sltRow != 0) {
					sltRow--;
					if (L.Li[sltRow].head) {
						sltCh = LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex);
						y -= distY;
						selectColor(x, y, BRIGHT_WHITE, BLACK, LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex));
						break;
					}
				}
			}
			break;
		case 3: //DOWN
			if (sltRow != size - 1) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex));
				}
				else {
					cout << " " << sltCh->dt.ch << " ";
				}
				while (sltRow != size - 1) {
					sltRow++;
					if (L.Li[sltRow].head) {
						sltCh = LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex);
						y += distY;
						selectColor(x, y, BRIGHT_WHITE, BLACK, LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex));
						break;
					}
				}
			}
			break;
		case 4: //RIGHT
			if (sltIndex != L.Li->tail->dt.index) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex));
				}
				else {
					cout << " " << sltCh->dt.ch << " ";
				}
				sltCh = sltCh->chNext;
				sltIndex++;
				x += distX;
				selectColor(x, y, BRIGHT_WHITE, BLACK, LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex));
			}

			break;
		case 5: //ENTER
			if (sltCh) {
				if (sltedRow == sltRow && sltedIndex == sltIndex) {
					Common::goTo(x, y);
					selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
					sltedRow = -1;
					sltedIndex = -1;
					sltCnt = 0;
				}
				else {
					sltCnt++;
					if (sltCnt == 1) {
						sltedX = x;
						sltedY = y;
						sltedRow = sltRow;
						sltedIndex = sltIndex;
						sltedCh = LinkedList::findNode(L.Li[sltedRow], sltedRow, sltedIndex);
					}
					else if (sltCnt == 2) {
						if (GameDifficult::matchCheck(sltCh, sltedCh)) {
							if (sltedRow == sltRow) {
								LinkedList::removeTwice(L.Li[sltedRow], sltedCh, sltCh);
								printRow(L.Li[sltRow], sltRow, sltIndex);
							}
							else {
								LinkedList::removeNode(L.Li[sltedRow], sltedCh);
								printRow(L.Li[sltedRow], sltedRow, -1);
								LinkedList::removeNode(L.Li[sltRow], sltCh);
								printRow(L.Li[sltRow], sltRow, sltIndex);
							}
							chCnt += 2;
							Common::matchedsound();
						}
						else {
							selectColor(sltedX, sltedY, BLACK, WHITE, sltedCh);
							sltedX = -1;
							sltedY = -1;
							Common::goTo(x, y);
						}
						/*if (hint == 1) {
							hint = 0;
							Common::goTo(0, 0);
							cout << " " << endl;
							cout << "    " << endl;
							cout << "    " << endl;
						}*/
						sltCnt = 0;
					}
				}
			}
			break;
		case 6: //B
			Menu::menuOutput();
			break;
		case 7: //P
			//time_taken += double(clock() - time / double(CLOCKS_PER_SEC)) / 1000;
			//pauseScreen();
			break;
		//case 8: //H
				//hint++;
				//Common::goTo(0, 0);
				//cout << sg.ch << endl;
				//cout << sg.preRow << ", " << sg.preCol << endl;
				//cout << sg.postRow << ", " << sg.postCol << endl;
				//break;
		}
		//if (chCnt == size * size) {
		//	time_taken += double(clock() - time / double(CLOCKS_PER_SEC)) / 1000;
		//	Menu::menuDoneOutput(time_taken);
		//}
	} while (input != 0);
	//GameDifficult::pauseScreen();
}

bool GameDifficult::matchCheck(Node* preCh, Node* postCh) {
	if (preCh->dt.ch == postCh->dt.ch) {
		/*if (preRow == postRow || preCol == postCol) {
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
		}*/
		return 1;
	}
	else {
		return 0;
	}
}

//bool GameDifficult::checkIMatch(int preRow, int preCol, int postRow, int postCol) {
//	int check = 1;
//	if (preRow > postRow) {
//		swap(preRow, postRow);
//		swap(preCol, postCol);
//	}
//	if (preCol == postCol) {
//		for (int i = preRow + 1; i < postRow; i++) {
//			if (charArr.arr[i][preCol] != ' ') {
//				check = 0;
//				break;
//			}
//		}
//	}
//	if (preRow == postRow) {
//		if (preCol < postCol) {
//			for (int i = preCol + 1; i < postCol; i++) {
//				if (charArr.arr[preRow][i] != ' ') {
//					check = 0;
//					break;
//				}
//			}
//		}
//		else {
//			for (int i = postCol + 1; i < preCol; i++) {
//				if (charArr.arr[preRow][i] != ' ') {
//					check = 0;
//					break;
//				}
//			}
//		}
//	}
//	return check;
//}

//bool GameDifficult::checkLMatch(int preRow, int preCol, int postRow, int postCol) {
//	if (preRow > postRow) {
//		swap(preRow, postRow);
//		swap(preCol, postCol);
//	}
//	if (checkIMatch(preRow, preCol, preRow, postCol) && charArr.arr[preRow][postCol] == ' ' && checkIMatch(preRow, postCol, postRow, postCol)) {
//		return 1;
//	}
//	if (checkIMatch(preRow, preCol, postRow, preCol) && charArr.arr[postRow][preCol] == ' ' && checkIMatch(postRow, preCol, postRow, postCol)) {
//		return 1;
//	}
//	return 0;
//}
//
//bool GameDifficult::checkUMatch(int preRow, int preCol, int postRow, int postCol) {
//	if (preCol == postCol) {
//		if (preCol == 0 || preCol == size - 1) {
//			return 1;
//		}
//	}
//	if (preRow == postRow) {
//		if (preRow == 0 || preRow == size - 1) {
//			return 1;
//		}
//	}
//	else if (preRow > postRow) {
//		swap(preRow, postRow);
//		swap(preCol, postCol);
//	}
//	int check = 0;
//	for (int i = preRow - 1; i >= 0; i--) {
//		check++;
//		if (charArr.arr[i][preCol] != ' ') {
//			break;
//		}
//		else if (checkLMatch(i, preCol, postRow, postCol)) {
//			return 1;
//		}
//	}
//	if (check == 0) {
//		if (checkIMatch(postRow, postCol, 0, postCol) && charArr.arr[0][postCol] == ' ') {
//			return 1;
//		}
//	}
//	check = 0;
//	for (int i = postRow + 1; i < size; i++) {
//		check++;
//		if (charArr.arr[i][postCol] != ' ') {
//			break;
//		}
//		else if (checkLMatch(preRow, preCol, i, postCol)) {
//			return 1;
//		}
//	}
//	if (check == 0) {
//		if (checkIMatch(preRow, preCol, size - 1, preCol) && charArr.arr[size - 1][preCol] == ' ') {
//			return 1;
//		}
//	}
//	check = 0;
//	if (preCol <= postCol) {
//		for (int i = preCol - 1; i >= 0; i--) {
//			check++;
//			if (charArr.arr[preRow][i] != ' ') {
//				break;
//			}
//			else if (checkLMatch(preRow, i, postRow, postCol)) {
//				return 1;
//			}
//		}
//		if (check == 0) {
//			if (checkIMatch(postRow, 0, postRow, postCol) && charArr.arr[postRow][0] == ' ') {
//				return 1;
//			}
//		}
//		check = 0;
//		for (int i = postCol + 1; i < size; i++) {
//			check++;
//			if (charArr.arr[postRow][i] != ' ') {
//				break;
//			}
//			else if (checkLMatch(preRow, preCol, postRow, i)) {
//				return 1;
//			}
//		}
//		if (check == 0) {
//			if (checkIMatch(preRow, preCol, preRow, size - 1) && charArr.arr[preRow][size - 1] == ' ') {
//				return 1;
//			}
//		}
//	}
//	else {
//		for (int i = postCol - 1; i >= 0; i--) {
//			check++;
//			if (charArr.arr[postRow][i] != ' ') {
//				break;
//			}
//			else if (checkLMatch(preRow, preCol, postRow, i)) {
//				return 1;
//			}
//		}
//		if (check == 0) {
//			if (checkIMatch(preRow, 0, preRow, preCol) && charArr.arr[preRow][0] == ' ') {
//				return 1;
//			}
//		}
//		check = 0;
//		for (int i = preCol + 1; i < size; i++) {
//			check++;
//			if (charArr.arr[preRow][i] != ' ') {
//				break;
//			}
//			if (checkLMatch(preRow, i, postRow, postCol)) {
//				return 1;
//			}
//		}
//		if (check == 0) {
//			if (checkIMatch(postRow, postCol, postRow, size - 1) && charArr.arr[postRow][size - 1] == ' ') {
//				return 1;
//			}
//		}
//	}
//	return 0;
//}
//
//bool GameDifficult::checkZMatch(int preRow, int preCol, int postRow, int postCol) {
//	if (preRow > postRow) {
//		swap(preRow, postRow);
//		swap(preCol, postCol);
//	}
//	for (int i = preRow + 1; i < postRow; i++) {
//		if (charArr.arr[i][preCol] != ' ') {
//			break;
//		}
//		else if (checkLMatch(i, preCol, postRow, postCol)) {
//			return 1;
//		}
//	}
//	if (preCol < postCol) {
//		for (int i = preCol + 1; i < postCol; i++) {
//			if (charArr.arr[preRow][i] != ' ') {
//				break;
//			}
//			else if (checkLMatch(preRow, i, postRow, postCol)) {
//				return 1;
//			}
//		}
//	}
//	else {
//		for (int i = postCol + 1; i < preCol; i++) {
//			if (charArr.arr[preRow][i] != ' ') {
//				break;
//			}
//			else if (checkLMatch(preRow, i, postRow, postCol)) {
//				return 1;
//			}
//		}
//	}
//	return 0;
//}
//
//void GameDifficult::pauseScreen() {
//	system("cls");
//	for (int i = 0; i < sizeof(pauseList) / sizeof(pauseList[0]); i++) {
//		int x = centerX;
//		int y = menuY + i * distY;
//		Common::goTo(x, y);
//		if (y == menuY) {
//			cout << "> ";
//		}
//		cout << pauseList[i];
//	}
//	pauseInput();
//}

//void GameDifficult::pauseInput() {
//	int slti = 0;
//	int input = -1;
//	int x = centerX;
//	int y = menuY + distY * slti;
//	do {
//		input = Common::getInput();
//		switch (input) {
//		case 3:
//			if (slti != (sizeof(pauseList) / sizeof(pauseList[0]) - 1)) {
//				Common::goTo(x, y);
//				cout << pauseList[slti] << "  ";
//				slti++;
//				y += distY;
//				Common::goTo(x, y);
//				cout << "> " << pauseList[slti];
//			}
//			break;
//		case 2:
//			if (slti != 0) {
//				Common::goTo(x, y);
//				cout << pauseList[slti] << "  ";
//				slti--;
//				y -= distY;
//				Common::goTo(x, y);
//				cout << "> " << pauseList[slti];
//			}
//			break;
//		case 5:
//			if (slti == 0) {
//				gameOutput();
//			}
//			else if (slti == 1) {
//				Menu::menuPlayOutput();
//			}
//			else if (slti == 2) {
//				input = 0;
//			}
//			break;
//	} while (input != 0);
//	Menu::Menu();
//}