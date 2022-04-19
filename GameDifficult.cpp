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
					selectColor(x, y, LIGHT_AQUA, BLACK, sltCh);
				}
				else {
					cout << " " << sltCh->dt.ch << " ";
				}
				sltCh = sltCh->chPrev;
				sltIndex--;
				x -= distX;
				selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
			}
			break;
		case 2: //UP
			if (sltRow != 0) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltCh);
				}
				else {
					cout << " " << sltCh->dt.ch << " ";
				}
				int i = 0;
				do {
					sltRow--;
					i -= distY;
					/*Common::goTo(centerX, botY);
					cout << L.Li[sltRow].tail->dt.index;*/
					if (sltRow < 0) {
						break;
					}
				} while (L.Li[sltRow].tail->dt.index < sltIndex); //|| L.Li[sltRow].head == NULL
				if (sltRow < 0) {
					sltRow = sltCh->dt.row;
					selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
				}
				else {
					sltCh = LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex);
					y += i;
					selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
				}
			}
			break;
		case 3: //DOWN
			if (sltRow != size - 1) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltCh);
				}
				else {
					cout << " " << sltCh->dt.ch << " ";
				}
				int i = 0;
				do {
					sltRow++;
					i += distY;
					/*Common::goTo(centerX, botY);
					cout << L.Li[sltRow].tail->dt.index;*/
					if (sltRow >= size) {
						break;
					}
				} while (L.Li[sltRow].tail->dt.index < sltIndex); //|| L.Li[sltRow].head == NULL
				if (sltRow >= size) {
					sltRow = sltCh->dt.row;
					selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
				}
				else {
					sltCh = LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex);
					y += i;
					selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
				}
			}
			break;
		case 4: //RIGHT
			if (sltIndex != L.Li[sltRow].tail->dt.index) {
				Common::goTo(x, y);
				if (sltCnt == 1 && x == sltedX && y == sltedY) {
					selectColor(x, y, LIGHT_AQUA, BLACK, sltCh);
				}
				else {
					cout << " " << sltCh->dt.ch << " ";
				}
				sltCh = sltCh->chNext;
				sltIndex++;
				x += distX;
				selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
			}
			break;
		case 5: //ENTER
			if (sltCh == sltedCh) {
				Common::goTo(x, y);
				selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
				sltedCh = NULL;
				sltCnt = 0;
			}
			else {
				sltCnt++;
				if (sltCnt == 1) {
					sltedX = x;
					sltedY = y;
					sltedCh = sltCh;
				}
				else if (sltCnt == 2) {
					if (matchCheck(sltedCh, sltCh)) {
						if (sltedCh->dt.row == sltRow) {
							int check = 0;
							if (sltCh == L.Li[sltRow].tail->chPrev) {
								check = 1;
							}
							else if (sltCh == L.Li[sltRow].tail) {
								check = 2;
							}
							LinkedList::removeTwice(L.Li[sltRow], sltedCh, sltCh);
							if (check != 0) {
								sltIndex -= check;
								x = sltIndex * distX;
								sltCh = L.Li[sltRow].tail;
							}
							printRow(L.Li[sltRow], sltRow, sltIndex);
						} 
						else {
							if (sltedCh == L.Li[sltedCh->dt.row].head && sltedCh == L.Li[sltedCh->dt.row].tail) {
								int sltedRow = sltedCh->dt.row;
								L.Li[sltedRow].head->dt.index = -2;
								Common::goTo(sltedX, sltedY);
								cout << "\33[2K\r";
							}
							else {
								int sltedRow = sltedCh->dt.row;
								LinkedList::removeNode(L.Li[sltedCh->dt.row], sltedCh);
								sltedCh = L.Li[sltedRow].tail;
								printRow(L.Li[sltedCh->dt.row], sltedCh->dt.row, -1);
							}
							if (sltCh == L.Li[sltCh->dt.row].head && sltCh == L.Li[sltCh->dt.row].tail) {
								L.Li[sltRow].head->dt.index = -2;
								Common::goTo(x, y);
								cout << "\33[2K\r";
								int i = 0;
								do {
									sltRow++;
									i += distY;
									if (sltRow == size) {
										break;
									}
								} while (L.Li[sltRow].head->dt.index == -2);
								if (sltRow == size) {
									sltRow = 0;
									y = 0;
									i = 0;
									while (L.Li[sltRow].head->dt.index == -2) {
										sltRow++;
										i += distY;
										if (sltRow = sltCh->dt.row) {
											break;
										}
									}
									if (sltRow != sltCh->dt.row) {
										sltCh = LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex);
										y += i;
										selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
									}
								}
								else {
									sltCh = LinkedList::findNode(L.Li[sltRow], sltRow, sltIndex);
									y += i;
									selectColor(x, y, BRIGHT_WHITE, BLACK, sltCh);
								}
							}
							else {
								int check = 0;
								if (sltCh == L.Li[sltRow].tail) {
									check = 1;
								}
								LinkedList::removeNode(L.Li[sltRow], sltCh);
								if (check == 1) {
									sltIndex--;
									x = sltIndex * distX;
									sltCh = L.Li[sltRow].tail;
								}
								printRow(L.Li[sltRow], sltRow, sltIndex);
							}
						}
						chCnt += 2;
						sltedX = -1;
						sltedY = -1;
						sltedCh = NULL;
					}
					else {
						selectColor(sltedX, sltedY, BLACK, WHITE, sltedCh);
						sltedX = -1;
						sltedY = -1;
						sltedCh = NULL;
						Common::goTo(x, y);
					}
					sltCnt = 0;
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
		if (chCnt == size * size) {
			cout << "Done";
			//time_taken += double(clock() - time / double(CLOCKS_PER_SEC)) / 1000;
			//Menu::menuDoneOutput(time_taken);
		}
	} while (input != 0);
	//GameDifficult::pauseScreen();
}

bool GameDifficult::matchCheck(Node* preCh, Node* postCh) {
	if (preCh->dt.ch == postCh->dt.ch) {
		if (checkIMatch(preCh, postCh)) {
			Common::goTo(centerX, botY);
			cout << "I";
			return 1;
		}
		if (checkLMatch(preCh, postCh)) {
			Common::goTo(centerX, botY);
			cout << "L";
			return 1;
		}
		if (checkUMatch(preCh, postCh)) {
			Common::goTo(centerX, botY);
			cout << "U";
			return 1;
		}
		if (checkZMatch(preCh, postCh)) {
			Common::goTo(centerX, botY);
			cout << "Z";
			return 1;
		}
		return 0;
	}
	else {
		return 0;
	}
}

bool GameDifficult::checkIMatch(Node* preCh, Node* postCh) {
	if (preCh->dt.row == postCh->dt.row) {
		if (preCh->chNext == postCh || preCh->chPrev == postCh) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (preCh->dt.index == postCh->dt.index) {
		int check = 0;
		if (preCh->dt.row > postCh->dt.row) {
			swap(preCh, postCh);
			check = 1;
		}
		for (int i = preCh->dt.row + 1; i < postCh->dt.row; i++) {
			if (L.Li[i].tail->dt.index >= preCh->dt.index) {
				return 0;
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}

bool GameDifficult::checkLMatch(Node* preCh, Node* postCh) {
	int check = 0;
	if (preCh->dt.row > postCh->dt.row) {
		swap(preCh, postCh);
		check = 1;
	}
	if (preCh->dt.index < postCh->dt.index) {
		if (preCh != L.Li[preCh->dt.row].tail) {
			return 0;
		}
		for (int i = preCh->dt.row + 1; i < postCh->dt.row; i++) {
			if (L.Li[i].tail->dt.index >= postCh->dt.index) {
				return 0;
			}
		}
		return 1;
	}
	else {
		if (postCh != L.Li[postCh->dt.row].tail) {
			return 0;
		}
		for (int i = preCh->dt.row + 1; i < postCh->dt.row; i++) {
			if (L.Li[i].tail->dt.index >= preCh->dt.index) {
				return 0;
			}
		}
		return 1;
	}
}

bool GameDifficult::checkUMatch(Node* preCh, Node* postCh) {
	if (preCh == L.Li[preCh->dt.row].head && postCh == L.Li[postCh->dt.row].head) {
		return 1;
	}
	if (preCh == L.Li[preCh->dt.row].tail && postCh == L.Li[postCh->dt.row].tail) {
		return 1;
	}
	int check = 0;
	if (preCh->dt.row > postCh->dt.row) {
		swap(preCh, postCh);
		check = 1;
	}
	else if (preCh->dt.row == postCh->dt.row) {
		if (preCh->dt.row == 0 || preCh->dt.row == size - 1) {
			return 1;
		}
		if (L.Li[preCh->dt.row - 1].tail->dt.index >= min(preCh->dt.index, postCh->dt.index)) {
			return 0;
		}
		if (L.Li[preCh->dt.row + 1].tail->dt.index >= min(preCh->dt.index, postCh->dt.index)) {
			return 0;
		}
	}

	for (int i = preCh->dt.row + 1; i < postCh->dt.row; i++) {
		if (L.Li[i].tail->dt.index >= postCh->dt.index) {
			return 0;
		}
	}
	return 1;
}

bool GameDifficult::checkZMatch(Node* preCh, Node* postCh) {
	int check = 0;
	if (preCh->dt.row > postCh->dt.row) {
		swap(preCh, postCh);
		check = 1;
	}
	if (preCh->dt.row + 1 >= postCh->dt.row) {
		return 0;
	}
	for (int i = preCh->dt.row + 1; i < postCh->dt.row; i++) {
		if (L.Li[i].tail->dt.index >= min(preCh->dt.index, postCh->dt.index)) {
			return 0;
		}
	}
	return 1;
}

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