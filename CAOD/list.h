#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct cycList
{
	string numberOfPassword;
	string numberOfFlight;
	string numberOfTicket;
	int field;//служебные поля
	cycList* next;
	cycList* prev;
};

struct sortli {
	int count = 0;
	string numberOfPassword;
	string numberOfFlight;
	string numberOfTicket;
	int field;
};

cycList* init(string nPass, string nFl, string nTick);
cycList* addelem(cycList* lst, string nPass, string nFl, string nTick);
cycList* deletelemptr(cycList* lst);
cycList* deletelem(cycList* lst, string nTick);
void listprint(cycList* lst);
void listprintr(cycList* lst);
int findMax(cycList* lst);
cycList* sortlist(cycList* lst);
bool isUniqAll(cycList* lst, string nTick, string nFl = "", string nPass = "");
string getNumberFlight(cycList* lst, string nTick);
bool isRegisterOfFlight(cycList* lst, string nFl);
bool isRegister(cycList* lst, string nPass);
void findelemByPass(cycList* lst, string nPass);
void findelemByNumber(cycList* lst, string nFl);
void clearList(cycList* lst);
