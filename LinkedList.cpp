#include "LinkedList.h"

LinkedList::LinkedList() {};

Node* LinkedList::createNode(cData dt) {
	Node* ch = new Node;
	ch->dt = dt;
	ch->chNext = NULL;
	ch->chPrev = NULL;
	return ch;
}

List LinkedList::createList(Node* ch) {
	List L;
	L.head = ch;
	L.tail = ch;
	return L;
}

Node* LinkedList::findNode(List L, int row, int index) {
	Node* ch = L.head;
	while (ch) {
		if (ch->dt.row == row && ch->dt.index == index) {
			return ch;
		}
		ch = ch->chNext;
	}
	return NULL;
}

void LinkedList::addTail(List &L, cData data) {
	if (L.head == NULL) {
		L = createList(createNode(data));
		return;
	}
	else {
		Node* ch = createNode(data);
		L.tail->chNext = ch;
		ch->chPrev = L.tail;
		L.tail = ch;
	}
}

void LinkedList::removeTail(List &L) {
	if (L.head == NULL) {
		return;
	}
	Node* ch = L.tail->chPrev;
	ch->chNext = NULL;
	delete L.tail;
	L.tail = ch;
}

void LinkedList::removeNode(List& L, Node* ch) {
	Node* tmp = ch;
	while (tmp->chNext) {
		tmp->dt.ch = tmp->chNext->dt.ch;
		tmp = tmp->chNext;
	}
	removeTail(L);
}

void LinkedList::removeTwice(List& L, Node* pre, Node* post) {
	if (pre->dt.index > post->dt.index) {
		swap(pre, post);
	}
	Node* tmp = post;
	while (tmp->chNext) {
		tmp->dt.ch = tmp->chNext->dt.ch;
		tmp = tmp->chNext;
	}
	removeTail(L);
	tmp = pre;
	while (tmp->chNext) {
		tmp->dt.ch = tmp->chNext->dt.ch;
		tmp = tmp->chNext;
	}
	removeTail(L);
}

List* LinkedList::setList(int n) {
	List* L = new List[n];
	cData tmp = { ' ', 0, 0 };
	for (int i = 0; i < n; i++) {
		tmp.row = i;
		for (int j = 0; j < n; j++) {
			tmp.index = j;
			addTail(L[i], tmp);
		}
	}

	int sz = n * n;
	int* position = new int[sz];
	bool* check = new bool[sz];
	for (int i = 0; i < sz; i++) {
		*(check + i) = 0;
	}
	for (int i = 0; i < sz; i++) {
		int tmp;
		do {
			tmp = rand() % sz;
		} while (check[tmp]);
		position[i] = tmp;
		check[tmp] = 1;
	}

	int ch[26];
	for (int i = 0; i < 26; i++) {
		ch[i] = 0;
	}
	for (int i = 0; i < sz - 1; i += 2) {
		int tmp = rand() % 26;
		if (sz / 2 <= 26) {
			do {
				tmp = rand() % 26;
			} while (ch[tmp]);
			ch[tmp] = 1;
		}
		else {
			do {
				tmp = rand() % 26;
			} while (ch[tmp] == 2);
			ch[tmp]++;
		}
		char value = tmp + 'A';
		int row = position[i] / n;
		int index = position[i] % n;
		findNode(L[row], row, index)->dt.ch = value;
		row = position[i + 1] / n;
		index = position[i + 1] % n;
		findNode(L[row], row, index)->dt.ch = value;
	}

	delete[] check;
	delete[] position;
	return L;
}