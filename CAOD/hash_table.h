#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const int n = 100;

struct Elem {
	string numberOfPassword;
	string Info;
	string bDay;
	string fullName;
	Elem* next;
	Elem() { next = nullptr; }
};
Elem* init(string nPass, string fName, string bD, string info);

Elem* AddElem(Elem* lst, string nPass, string fName, string bD, string info);
vector<Elem*> AddElem(vector<Elem*> hT, string nPass, string fName, string bD, string info);
void viewTable(vector<Elem*> hT, bool* f);
void findElemByPass(Elem* lst, string nPass, bool* isFind);
void findElemByPass(vector<Elem*> hT, string nPass);
void findElemByName(vector<Elem*> hT, string fName);
Elem* deleteElem(Elem* lst, string nPass, bool* isDel);
vector<Elem*> deleteElem(vector<Elem*> hT, string nPass);
Elem* clearElem(Elem* pr);
vector<Elem*> clearElems(vector<Elem*> hT);
bool isUniqPassword(vector<Elem*> hT, string nPass);