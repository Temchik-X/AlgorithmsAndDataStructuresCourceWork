#pragma once
#include "hash_table.h"

using namespace std;


Elem* init(string nPass, string fName, string bD, string info) 
{
	Elem* lst = new Elem;
	// выделение памяти под корень списка
	lst->numberOfPassword = nPass;
	lst->bDay = bD;
	lst->fullName = fName;
	lst->Info = info;
	lst->next = nullptr; // указатель на следующий узел
	return(lst);
}
Elem* AddElem(Elem* lst, string nPass, string fName, string bD, string info) {
	if (lst == nullptr) {
		lst = init(nPass, fName, bD, info);
		return lst;
	}
	Elem* p = lst;
	while (p->next != nullptr) {
		p = p->next;
	}
	Elem* temp = new Elem;
	p->next = temp;
	temp->numberOfPassword = nPass;
	temp->bDay = bD;
	temp->fullName = fName;
	temp->Info = info;
	temp->next = nullptr;
	return lst;

}
vector<Elem*> AddElem(vector<Elem*> hT, string nPass, string fName, string bD, string info) {
	unsigned int index;
	index = index = ((nPass[0] * nPass[0] + nPass[1] * nPass[1] + nPass[2] * nPass[2] + nPass[3] * nPass[3] + nPass[5] * nPass[5] + nPass[6] * nPass[6] + nPass[7] * nPass[7] + nPass[8] * nPass[8] + nPass[9] * nPass[9] + nPass[10] * nPass[10]) % n);
	hT[index] = AddElem(hT[index], nPass, fName, bD, info);
	return hT;

}
void viewTable(vector<Elem*> hT, bool* f) {
	Elem* p;
	for (int i = 0; i < n; i++) {
		p = hT[i];
		while (p != nullptr) {
			if (!*f) {
				cout << "Пассажиры" << endl << setw(16) << "Номер паспорта" << setw(23) << "ФИО" << setw(16) << "Дата рождения" << setw(43) << "Дата и место выдачи" << endl;
				*f = true;
			}
			cout << setw(16) << p->numberOfPassword << setw(23) << p->fullName << setw(16) << p->bDay << setw(43) << p->Info << endl;
			p = p->next;
		}
	}
}
void findElemByPass(Elem* lst, string nPass, bool* isFind) {
	if (lst == nullptr) return;
	if (lst->numberOfPassword == nPass) {
		*isFind = true;
		cout << setw(28) << "Результаты поиска" << endl;
		cout << setw(7) << "ФИО: "  << lst->fullName << endl;
		cout << setw(18) << "Номер паспорта: "  << lst->numberOfPassword << endl;
		cout << setw(17) << "Дата рождения: "  << lst->bDay << endl;
		cout << setw(23) << "Дата и место выдачи: "  << lst->Info << endl;
		return;
	}
	Elem* p = lst;
	while (p->next != nullptr && p->numberOfPassword != nPass) p = p->next; //под вопросом, может быть исключение
	if (p == nullptr) return;
	if (p->numberOfPassword == nPass) {
		*isFind = true;
		cout << setw(28) << "Результаты поиска" << endl;
		cout << setw(7) << "ФИО: " << p->fullName << endl;
		cout << setw(18) << "Номер паспорта: " << p->numberOfPassword << endl;
		cout << setw(17) << "Дата рождения: " << p->bDay << endl;
		cout << setw(23) << "Дата и место выдачи: " << p->Info << endl;
	}
	return;
}
void findElemByPass(vector<Elem*> hT, string nPass) {
	unsigned int index;
	bool isFind = false;
	index = index = ((nPass[0] * nPass[0] + nPass[1] * nPass[1] + nPass[2] * nPass[2] + nPass[3] * nPass[3] + nPass[5] * nPass[5] + nPass[6] * nPass[6] + nPass[7] * nPass[7] + nPass[8] * nPass[8] + nPass[9] * nPass[9] + nPass[10] * nPass[10]) % n);
	findElemByPass(hT[index], nPass, &isFind);
}
void findElemByName(vector<Elem*> hT, string fName) {
	bool isFind = false;
	for (auto it = hT.begin(); it != hT.end(); ++it) {
		if (*it == nullptr) continue;
		Elem* p = *it;
		do {
			if (p->fullName != fName) { p = p->next; continue; }
			if (!isFind) cout << setw(15) << "ФИО" << setw(25) << "Номер паспорта" << endl;
			isFind = true;
			cout << setw(20) << p->fullName << setw(20) << p->numberOfPassword << endl;
			p = p->next;
		} while (p != nullptr);
	}
}
Elem* deleteElem(Elem* lst, string nPass, bool* isDel) {
	if (lst == nullptr) return lst;
	if (lst->numberOfPassword == nPass) {
		Elem* p = lst->next;
		free(lst);
		*isDel = true;
		return(p);
	}
	Elem* p = lst;
	while (p->next != nullptr && p->next->numberOfPassword != nPass) p = p->next; //под вопросом, может быть исключение
	if (p->next == nullptr) return(lst);
	Elem* temp = p->next->next;
	free(p->next);
	*isDel = true;
	p->next = temp;
	return(lst);
}
vector<Elem*> deleteElem(vector<Elem*> hT, string nPass) {
	unsigned int index;
	bool isDel = false;
	index = index = ((nPass[0] * nPass[0] + nPass[1] * nPass[1] + nPass[2] * nPass[2] + nPass[3] * nPass[3] + nPass[5] * nPass[5] + nPass[6] * nPass[6] + nPass[7] * nPass[7] + nPass[8] * nPass[8] + nPass[9] * nPass[9] + nPass[10] * nPass[10]) % 100);
	hT[index] = deleteElem(hT[index], nPass, &isDel);
	return(hT);
}
Elem* clearElem(Elem* pr) {
	Elem* p = pr;
	if (p != nullptr) {
		p = p->next;
		clearElem(p);
		delete pr;
	}
	return nullptr;
}
vector<Elem*> clearElems(vector<Elem*> hT) {
	for (auto it = hT.begin(); it != hT.end(); ++it) {
		if (*it == nullptr) continue;
		*it = clearElem(*it);
	}
	return hT;
}
bool isUniqPassword(vector<Elem*> hT, string nPass) {
	unsigned int index;
	bool isFind = false;
	index = index = ((nPass[0] * nPass[0] + nPass[1] * nPass[1] + nPass[2] * nPass[2] + nPass[3] * nPass[3] + nPass[5] * nPass[5] + nPass[6] * nPass[6] + nPass[7] * nPass[7] + nPass[8] * nPass[8] + nPass[9] * nPass[9] + nPass[10] * nPass[10]) % n);
	if (hT[index] == nullptr) return true;
	if (hT[index]->numberOfPassword == nPass) {
		return false;
	}
	Elem* p = hT[index];
	while (p->next != nullptr && p->next->numberOfPassword != nPass) p = p->next; //под вопросом, может быть исключение
	if (p->next == nullptr) return true;
	return false;
}