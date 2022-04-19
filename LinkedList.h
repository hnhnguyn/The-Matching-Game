#pragma once
#include <iostream>
using namespace std;

struct cData {
	char ch = ' ';
	int row = 0;
	int index = 0;
};

struct Node {
	cData dt;
	Node* chNext = NULL;
	Node* chPrev = NULL;
};

struct List {
	Node* head = NULL;
	Node* tail = NULL;
};

struct LinkedList {
	List* Li;

	LinkedList();
	static Node* createNode(cData);
	static Node* findNode(List, int, int);
	static List createList(Node*);
	static void addTail(List &, cData);
	static void removeTail(List&);
	static void removeNode(List&, Node*);
	static void removeTwice(List&, Node*, Node*);
	static List* setList(int);
};