#pragma once
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


struct node
{
	
	string numberOfFlight;
	string nameOfAirline;
	string departure;
	string destination;
	string dateOfDeparture;
	string timeOfDeparture;
	int numberOfSeats;
	int numberOfFreeSeats;
	node* left;//служебные поля
	node* right;
	int data;
	int height;
	int depth;
	node(int k, string nFl, string nA, string dep, string dest, string dateDep, string timeDep, int nSeats, int nFSeats) {
		data = k; left = right = nullptr; height = 1; depth = 1; numberOfFlight = nFl; nameOfAirline = nA; departure = dep; destination = dest;
		dateOfDeparture = dateDep; timeOfDeparture = timeDep; numberOfSeats = nSeats; numberOfFreeSeats = nFSeats;
	}
};

unsigned char height(node* tree);
int balanceFactor(node* tree);
void fixHeight(node* tree);
void fixDepth(node* tree);
node* smallRotateRight(node* tree);
node* smallRotateLeft(node* tmp);
node* balance(node* tree);
node* addVert(node* tree, int k, string nFl, string nA, string dep, string dest, string dateDep, string timeDep, int nSeats, int nFSeats);
node* findMin(node* tree);
node* removeMin(node* tree);
node* removeVert(node* tree, int k);
void ShowTree(node* tree, int indent);
void ShowElements(node* tree, bool* f);
int boyerMoore(string text, string pattern);
void findByBM(node* tree, string pattern, bool* f);
void findElem(node* tree, int data, bool* flag);
node* clearTree(node* tree);
int getNumber(string str);
bool checkUniq(node* tree, string nFl, bool f = true);
void checkUniq(node* tree, int k, bool* flag);
void countFreeSeats(node* tree, int k, bool* flag, int* count);
void returnFreeSeats(node* tree, int k, bool* flag, int* count);
