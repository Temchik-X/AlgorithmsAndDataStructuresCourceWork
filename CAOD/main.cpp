#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif


#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <windows.h>

#include "list.h"
#include "hash_table.h"
#include "AVLTree.h"


using namespace std;

bool checkDateFormat(string str) {
	if (str.length() != 10) return false; // Проверяем длину строки
	if (str[2] != '.' || str[5] != '.') return false; // Проверяем разделители
	for (int i = 0; i < 10; i++) {
		if (i == 2 || i == 5) continue; // Пропускаем разделители
		if (str[i] < '0' || str[i] > '9') return false; // Проверяем, что символы - цифры
	}
	int day = stoi(str.substr(0, 2)); // Получаем число
	int month = stoi(str.substr(3, 2)); // Получаем месяц
	int year = stoi(str.substr(6, 4)); // Получаем год
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) return false; // Проверяем, что дата корректна
	if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) return false; // Проверяем, что месяц корректен
	if (day > 28 && month == 2 && ((year % 4 != 0) || (year % 100 == 0 && year % 400 != 0))) return false; // Проверяем, что февраль корректен
	return true;
}
string getDate(string text) {
	string date;
	cout << text;
	getline(cin, date);
	while (!checkDateFormat(date)) {
		cout << "Неверный формат! Введите строку в формате dd.mm.yyyy: ";
		getline(cin, date);
	}
	return date;
}
bool checkTimeFormat(string str) {
	if (str.length() != 5) return false; // Проверяем длину строки
	if (str[2] != ':') return false; // Проверяем разделитель
	for (int i = 0; i < 5; i++) {
		if (i == 2) continue; // Пропускаем разделитель
		if (str[i] < '0' || str[i] > '9') return false; // Проверяем, что символы - цифры
	}
	int hours = stoi(str.substr(0, 2)); // Получаем часы
	int minutes = stoi(str.substr(3, 2)); // Получаем минуты
	if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) return false; // Проверяем, что время корректно
	return true;
}
string getTime() {
	string time;
	cout << "Введите время отправления: ";
	getline(cin, time);
	while (!checkTimeFormat(time)) {
		cout << "Неверный формат! Введите строку в формате hh:mm: ";
		getline(cin, time);
	}
	return time;
}
bool checkPassFormat(string str) {
	if (str.length() != 11) return false; // Проверяем длину строки
	if (str[4] != '-') return false; // Проверяем разделитель
	for (int i = 0; i < 11; i++) {
		if (i == 4) continue; // Пропускаем разделитель
		if (str[i] < '0' || str[i] > '10') return false; // Проверяем, что символы - цифры
	}
	return true;
}
string getnPass() {
	string nPass;
	cout << "Введите номер паспорта: ";
	getline(cin, nPass);
	while (!checkPassFormat(nPass)) {
		cout << "Неверный формат! Введите строку в формате nnnn-nnnnnn: ";
		getline(cin, nPass);

	}
	return nPass;
}
bool checknFlightFormat(string str) {
	if (str.length() != 7) return false; // Проверяем длину строки
	if (str[3] != '-') return false; // Проверяем разделитель
	for (int i = 0; i < 7; i++) {
		if (i == 3) continue; // Пропускаем разделитель
		if (i < 3) {
			if (!isalpha(str[i])) return false; // Проверяем, что символы - буквы
		}
		else {
			if (!isdigit(str[i])) return false; // Проверяем, что символы - цифры
		}
	}
	return true;
}
string getnFlight() {
	std::string nFlight;
	cout << "Введите номер авиарейса: ";
	getline(cin, nFlight);
	while (!checknFlightFormat(nFlight)) {
		cout << "Неверный формат! Введите строку в формате aaa-nnn: ";
		getline(cin, nFlight);
	}
	return nFlight;
}
int getnSeats() {
	int nSeats = 0;
	cout << "Введите количество мест в самолете: ";
	cin >> nSeats;
	while (cin.fail() || nSeats <= 0) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Некорректное количество мест! Введите корректное количество мест в самолете: ";
		cin >> nSeats;
	}
	return nSeats;
}
int getnFreeSeats(int nSeats) {
	int nFSeats;
	cout << "Введите количество свободных мест: ";
	cin >> nFSeats;
	while (cin.fail() || nFSeats > nSeats) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Количество свободных мест слишком велико! Введите корректное количество свободных мест: ";
		cin >> nFSeats;
	}
	return nFSeats;
}
bool checknTickFormat(string str) {
	if (str.length() != 9) return false; // Проверяем длину строки
	for (int i = 0; i < 9; i++) {
		if (!isdigit(str[i])) return false; // Проверяем, что символы - цифры
	}
	return true;
}
string getnTick() {
	string nTick;
	cout << "Введите номер билета: ";
	getline(cin, nTick);
	while (!checknTickFormat(nTick)) {
		cout << "Номер авиабилета должен содержать 9 цифр! Введите корректный номер авиабилета: ";
		getline(cin, nTick);
	}
	return nTick;
}

void showPassangers(vector<Elem*> hT) {
	bool f = false;
	viewTable(hT, &f);
	if (!f) {
		cout << "Нет зарегистрированных пассажиров!" << endl;
	}
}
void showFlight(node* tree) {
	bool f = false;
	ShowElements(tree, &f);
	if (!f) {
		cout << "Нет зарегистрированных авиарейсов!" << endl;
	}
}
node* addFlight(node* tree, string nFl, string nA, string dep, string dest, string dateDep, string timeDep, int nSeats, int nFSeats) {
	bool isUniq = true;
	checkUniq(tree, getNumber(nFl), &isUniq);
	if (!isUniq) {
		cout << "Номер рейса " << nFl << " неуникален" << endl;
		return tree;
	}
	int k = getNumber(nFl);
	tree = addVert(tree, k, nFl, nA, dep, dest, dateDep, timeDep, nSeats, nFSeats);
	cout << "Добавление рейса " << nFl << " прошло успешно!" << endl;
	return tree;
}
node* inputFlight(node* tree) {
	string nFl, nA, dep, dest, dateDep, timeDep;
	int nSeats, nFSeats;
	cin.ignore();
	cout << setw(25) << "Добавление авиарейса!" << endl;
	nFl = getnFlight();
	cout << "Введите название авиакомпании: ";
	getline(cin, nA);
	cout << "Введите аэропорт отправления: ";
	getline(cin, dep);
	cout << "Введите аэропорт назначения: ";
	getline(cin, dest);
	dateDep = getDate("Введите дату отправления: ");
	timeDep = getTime();
	nSeats = getnSeats();
	nFSeats = getnFreeSeats(nSeats);
	tree = addFlight(tree, nFl, nA, dep, dest, dateDep, timeDep, nSeats, nFSeats);
	return tree;
}
vector<Elem*> addPassanger(vector<Elem*> hT, string nPass, string fName, string bD, string info) {
	if (!isUniqPassword(hT, nPass)) {
		cout << "Номер паспорта " << nPass << " неуникален" << endl;
		return hT;
	}
	hT = AddElem(hT, nPass, fName, bD, info);
	cout << "Добавление пассажира с № паспорта " << nPass << " прошло успешно!" << endl;
	return hT;
}
vector<Elem*> inputPassanger(vector<Elem*> hT) {
	string nPass, fName, bD, info;
	cin.ignore();
	cout << setw(25) << "Добавление пассажира!" << endl;
	nPass = getnPass();
	cout << "Введите ФИО: ";
	getline(cin, fName);
	bD = getDate("Введите дату рождения: ");
	cout << "Введите дату и место выдачи паспорта: ";
	getline(cin, info);
	hT = addPassanger(hT, nPass, fName, bD, info);
	return hT;
}
cycList* saleRegistration(cycList* lst, vector<Elem*> hT, node* tree, string nPass, string nFl, string nTick) {
	bool isUniq = true;
	checkUniq(tree, getNumber(nFl), &isUniq);
	if (isUniq) {
		cout << "Отсутствует рейс № " << nFl << endl;
		return lst;
	}
	if (isUniqPassword(hT, nPass)) {
		cout << "Отсутствует пассажир c № паспорта " << nPass << endl;
		return lst;
	}
	if (!isUniqAll(lst, nTick, nPass, nFl)) {
		cout << "Номер билета неуникален или этот пассажир c №паспорта " << nPass << " уже зарегистрирован на рейс " << nFl << endl;
		return lst;
	}
	int count = 0;
	countFreeSeats(tree, getNumber(nFl), &isUniq, &count);
	if (count == 0) {
		cout << "Отсутствуют свободные места на  рейс № " << nFl << endl;
		return lst;
	}
	lst = addelem(lst, nPass, nFl, nTick);
	cout << "Регистрация пассажира с № паспорта " << nPass << " на рейс №" << nFl << " прошла успешно!" << endl;
	cout << "Оставшееся количество свободных мест на рейсе № " << nFl << " равно " << count - 1 << endl;
	return lst;
}
cycList* inputRegistration(cycList* lst, vector<Elem*> hT, node* tree) {
	cout << setw(24) << "Регистрация на рейс!" << endl;
	string nPass, nFl, nTick;
	cin.ignore();
	showPassangers(hT);
	nPass = getnPass();
	showFlight(tree);
	nFl = getnFlight();
	nTick = getnTick();
	lst = saleRegistration(lst, hT, tree, nPass, nFl, nTick);
	return lst;
}
cycList* returnRegistration(cycList* lst, node* tree, string nTick) {
	if (isUniqAll(lst, nTick)) {
		cout << "Нет зарегистрированного пассажира с № билета " << nTick << endl;
		return lst;
	}
	bool flag = false;;
	int count = 0;
	string nFl = getNumberFlight(lst, nTick);
	returnFreeSeats(tree, getNumber(nFl), &flag, &count);
	lst = deletelem(lst, nTick);
	cout << "Возврат регистрации пассажира с № билета " <<  nTick << " прошел успешно!" << endl;
	cout << "Оставшееся количество свободных мест на рейсе № " << nFl << " равно " << count << endl;
	return lst;
}
node* deleteFlight(node* tree, cycList* lst, string nFl) {
	bool isUniq = true;

	checkUniq(tree, getNumber(nFl), &isUniq);
	if (isUniq) {
		cout << "Номер рейса " << nFl << " отсутствует" << endl;
		return tree;
	}
	if (isRegisterOfFlight(lst, nFl)) {
		cout << "На рейс № " << nFl << " зарегистрированы. Удаление невозможно!" << endl;
		return tree;
	}
	tree = removeVert(tree, getNumber(nFl));
	cout << "Удаление рейса " << nFl << " прошло успешно!" << endl;
	return tree;
}
vector<Elem*> deletePassanger(vector<Elem*> hT, cycList* lst, string nPass) {

	if (isUniqPassword(hT, nPass)) {
		cout << "Пассажир с  №паспорта " << nPass << " отсутствует" << endl;
		return hT;
	}
	if (isRegister(lst, nPass)) {
		cout << "Пассажир с №паспорта " << nPass << " уже зарегистрирован. Удаление невозможно!" << endl;
		return hT;
	}
	hT = deleteElem(hT, nPass);
	cout << "Удаление пассажира с №паспорта " << nPass << " прошло успешно!" << endl;
	return hT;
}
void findByNumberOfPassword(vector<Elem*> hT, cycList* lst, string nPass) {
	if (isUniqPassword(hT, nPass)) {
		cout << "Пассажир с  №паспорта " << nPass << " отсутствует" << endl;
		return;
	}
	findElemByPass(hT, nPass);
	findelemByPass(lst, nPass);
	return;
}
void findPassangersByName(vector<Elem*> hT, string fName) {
	findElemByName(hT, fName);
}
void findFlightByNumber(node* tree, cycList* lst, string nFl) {
	bool isUniq = true;
	checkUniq(tree, getNumber(nFl), &isUniq);
	if (isUniq) {
		cout << "Номер рейса " << nFl << " отсутствует" << endl;
		return;
	}
	findElem(tree, getNumber(nFl), &isUniq);
	findelemByNumber(lst, nFl);
}
void findFlightByDestination(node* tree, string text) {
	bool isFind = false;
	findByBM(tree, text, &isFind);
	if (!isFind) cout << "Не найдено авиарейсрв с таким пунктом назначения!" << endl;
}

vector<Elem*> clearPassangers(vector<Elem*> hT, cycList* lst) {
	bool noDel = false;
	bool isDel = false;
	for (auto it = hT.begin(); it != hT.end(); ++it) {
		if (*it == nullptr) continue;
		if (isRegister(lst, (*it)->numberOfPassword)) {
			noDel = true;
			continue;
		}
		isDel = true;
		*it = clearElem(*it);
	}
	if (!isDel && noDel) {
		cout << "Не были удалены данные о пассажирах, так как они зарегистрированы на рейс!" << endl;
	}
	else if (noDel) {
		cout << "Не были удалены некоторые данные о пассажирах, так как они зарегистрированы на рейс!" << endl;
	}
	else if (!isDel && !noDel) {
		cout << "Нет данных о пассажирах для удаления!" << endl;
	}
	else {
		cout << "Успешно удалены все данные о пассажирах!" << endl;
	}
	return(hT);
}
//vector<Elem*> clearPassangers(vector<Elem*> hT, cycList* lst) {
//	bool noDel = false;
//	bool isDel = false;
//	for (auto it = hT.begin(); it != hT.end(); ++it) {
//		if (*it == nullptr) continue;
//		if (isRegister(lst, (*it)->numberOfPassword)) {
//			noDel = true;
//			break;
//		}
//		isDel = true;
//	}
//	if (noDel) {
//		cout << "Не были удалены данные о пассажирах, так как некоторые зарегистрированы на рейс!" << endl;
//	}
//	else {
//		hT = clearElems(hT);
//		cout << "Успешно удалены все данные о пассажирах!" << endl;
//	}
//	return(hT);
//}

void findEl4Delete(node* tree, cycList* lst, vector<int>* res, bool* isDel, bool* noDel) {
	if (tree) {
		findEl4Delete(tree->left, lst, res, isDel, noDel);
		findEl4Delete(tree->right, lst, res, isDel, noDel);
		if (!isRegisterOfFlight(lst, tree->numberOfFlight)) {
			*isDel = true;
			res->push_back(getNumber(tree->numberOfFlight));
			return;
		}
		*noDel = true;
	}
	return;
}
node* clearFlights(node* tree, cycList* lst) {
	bool noDel = false;
	bool isDel = false;
	vector<int> num4delete;
	findEl4Delete(tree, lst, &num4delete, &isDel, &noDel);
	for (auto it = num4delete.begin(); it != num4delete.end(); ++it) tree = removeVert(tree, *it);

	if (!isDel && noDel) {
		cout << "Не были удалены данные об авиарейсах, так как на них зарегистрированы пассажиры!" << endl;
	}
	else if (noDel) {
		cout << "Не были удалены некоторые данные об авиарейсах, так как на них зарегистрированы пассажиры!" << endl;
	}
	else if (!isDel && !noDel) {
		cout << "Нет данных об авиарейсах для удаления!" << endl;
	}
	else {
		cout << "Успешно удалены все данные об авиарейсах!" << endl;
	}
	return tree;
}
//node* clearAvl(node* tree, cycList* lst, bool* noDel, bool* isDel) {
//	if (tree) {
//		clearAvl(tree->left, lst, noDel, isDel);
//		clearAvl(tree->right, lst, noDel, isDel);
//		if (isRegisterOfFlight(lst, tree->numberOfFlight)) {
//			*noDel = true;
//			return tree;
//		}
//		
//		
//	}
//	return tree;
//}
//node* clearFlights(node* tree, cycList* lst) {
//	bool noDel = false;
//	bool isDel = false;
//	tree = clearAvl(tree, lst, &noDel, &isDel);
//	if (noDel) {
//		cout << "Не удалось удалить данные о рейсах, так как на некоторые зарегистрированны пассажиры!" << endl;
//	}
//	else {
//		tree = clearTree(tree);
//		cout << "Успешно удалены все данные о рейсах!" << endl;
//	}
//	return tree;
//}
void showRegisterPassangers(cycList* lst) {
	listprint(lst);
}
void clearAll(cycList* lst, vector<Elem*>* hT, node* tree) {
	clearTree(tree);
	clearElems(*hT);
	clearList(lst);
	hT->clear();
	hT->shrink_to_fit();
}



int main(){
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<Elem*> hTablePassangers(n);
	node* avlTreeFlights = nullptr;
	string numberPassword, numberFlight, numberTicket, fullName, text;
	cycList* listRegistration = nullptr;
	int click;
	bool stop = false;

	{avlTreeFlights = addFlight(avlTreeFlights, "DFG-021", "Russia", "Ставрополь", "Санкт-Петербург", "12.02.23", "16:50", 100, 30);
	avlTreeFlights = addFlight(avlTreeFlights, "BGH-122", "Aeroflot", "Москва", "Новосибирск", "09.04.23", "12:20", 100, 10);
	avlTreeFlights = addFlight(avlTreeFlights, "OIR-121", "Победа", "Калининград", "Санкт-Петербург", "04.03.23", "07:40", 100, 10);
	avlTreeFlights = addFlight(avlTreeFlights, "CVR-120", "SmartAvia", "Стамбул", "Москва", "16.03.23", "10:35", 100, 1);
	avlTreeFlights = addFlight(avlTreeFlights, "MVB-125", "NordWings", "Санкт-Петербург", "Сочи", "21.03.23", "11:55", 100, 10);
	hTablePassangers = addPassanger(hTablePassangers, "1111-111222", "Редькин А. В.", "02.07.2002", "05.03.2016 ОУВД по г.СПБ");
	hTablePassangers = addPassanger(hTablePassangers, "1111-111322", "Ковальчук А. Г.", "15.03.2002", "23.10.2016 ОУВД по г.Москва");
	hTablePassangers = addPassanger(hTablePassangers, "1111-222111", "Киржаков А. М.", "26.09.2000", "20.04.2013 ОУВД по г.Москва");
	hTablePassangers = addPassanger(hTablePassangers, "1111-121222", "Закиров С. А.", "23.03.1998", "02.01.2012 ОУВД по г.СПБ");
	hTablePassangers = addPassanger(hTablePassangers, "2211-121222", "Васильева А. Г.", "10.10.1990", "21.05.2010 ОУВД по г.Москва");
	listRegistration = saleRegistration(listRegistration, hTablePassangers, avlTreeFlights, "1111-111222", "DFG-021", "000000001");
	listRegistration = saleRegistration(listRegistration, hTablePassangers, avlTreeFlights, "1111-111222", "OIR-121", "000000091");
	listRegistration = saleRegistration(listRegistration, hTablePassangers, avlTreeFlights, "1111-111222", "OIR-121", "000000112");
	listRegistration = saleRegistration(listRegistration, hTablePassangers, avlTreeFlights, "1111-222111", "AAA-121", "000000112");
	system("cls"); }

	cout << setw(80) << "Информационная система продажа авиабилетов. `Made by Артемий Хорошилов`" << endl;

	while (!stop) {
		cout << endl << setw(28) << "Меню управления системой" << endl;{
		cout << "1. Добавление авиарейса" << endl;
		cout << "2. Добавление пассажира" << endl;
		cout << "3. Регистрация продажи пассажиру авиабилета" << endl;
		cout << "4. Удаление данных о пассажире" << endl;
		cout << "5. Удаление сведений об авиарейсе" << endl;
		cout << "6. Регистрация возврата пассажиром авиабилета" << endl;
		cout << "7. Просмотр всех зарегистрированных пассажиров" << endl;
		cout << "8. Просмотр всех авиарейсов" << endl;
		cout << "9. Просмотр зарегистрированных на авиарейсы пассажиров" << endl;
		cout << "10. Поиск пассажира по «номеру паспорта»" << endl;
		cout << "11. Поиск пассажира по его ФИО" << endl;
		cout << "12. Поиск авиарейса по «номеру авиарейса»" << endl;
		cout << "13. Поиск авиарейса по фрагментам названия аэропорта прибытия" << endl;
		cout << "14. Очистка данных о пассажирах" << endl;
		cout << "15. Очистка данных об авиарейсах" << endl;
		cout << "0. Выход из системы" << endl; }
		cout << "Введите номер пункта меню: ";
		cin >> click;
		switch (click) {
		case 1:
			avlTreeFlights = inputFlight(avlTreeFlights);
			system("pause");
			//system("cls");
			break;
		case 2:
			hTablePassangers = inputPassanger(hTablePassangers);
			system("pause");
			//system("cls");
			break;
		case 3:
			listRegistration = inputRegistration(listRegistration, hTablePassangers, avlTreeFlights);
			system("pause");
			//system("cls");
			break;
		case 4:
			cout << setw(31) << "Удаление данных о пассажире" << endl;
			cin.ignore();
			showPassangers(hTablePassangers);
			numberPassword = getnPass();
			hTablePassangers = deletePassanger(hTablePassangers, listRegistration, numberPassword);
			showPassangers(hTablePassangers);
			system("pause");
			//system("cls");
			break;
		case 5:
			cout << setw(34) << "Удаление сведений об авиарейсе" << endl;
			cin.ignore();
			showFlight(avlTreeFlights);
			numberFlight = getnFlight();
			avlTreeFlights = deleteFlight(avlTreeFlights, listRegistration, numberFlight);
			showFlight(avlTreeFlights);
			system("pause");
			//system("cls");
			break;
		case 6:
			cout << setw(46) << "Регистрация возврата пассажиром авиабилета" << endl;
			cin.ignore();
			showRegisterPassangers(listRegistration);
			numberTicket = getnTick();
			listRegistration = returnRegistration(listRegistration, avlTreeFlights, numberTicket);
			showRegisterPassangers(listRegistration);
			system("pause");
			//system("cls");
			break;
		case 7:
			cout << setw(47) << "Просмотр всех зарегистрированных пассажиров" << endl;
			showPassangers(hTablePassangers);
			system("pause");
			//system("cls");
			break;
		case 8:
			cout << setw(28) << "Просмотр всех авиарейсов" << endl;
			showFlight(avlTreeFlights);
			system("pause");
			//system("cls");
			break;
		case 9:
			cout << setw(55) << "Просмотр зарегистрированных на авиарейсы пассажиров" << endl;
			showRegisterPassangers(listRegistration);
			system("pause");
			//system("cls");
			break;
		case 10:
			cout << setw(40) << "Поиск пассажира по «номеру паспорта»" << endl;
			cin.ignore();
			numberPassword = getnPass();
			findByNumberOfPassword(hTablePassangers, listRegistration, numberPassword);
			system("pause");
			//system("cls");
			break;
		case 11:
			cout << setw(30) << "Поиск пассажира по его ФИО" << endl;
			cin.ignore();
			cout << "Введите ФИО пассажира для поиска: ";
			getline(cin, fullName);
			findPassangersByName(hTablePassangers, fullName);
			system("pause");
			//system("cls");
			break;
		case 12:
			cout << setw(41) << "Поиск авиарейса по «номеру авиарейса»" << endl;
			cin.ignore();
			numberFlight = getnFlight();
			findFlightByNumber(avlTreeFlights, listRegistration, numberFlight);
			system("pause");
			//system("cls");
			break;
		case 13:
			cout << setw(61) << "Поиск авиарейса по фрагментам названия аэропорта прибытия" << endl;
			cin.ignore();
			cout << "Введите название аэропорта назначения: ";
			getline(cin, text);
			findFlightByDestination(avlTreeFlights, text);
			system("pause");
			//system("cls");
			break;
		case 14:
			cout << setw(31) << "Очистка данных о пассажирах" << endl;
			hTablePassangers = clearPassangers(hTablePassangers, listRegistration);
			system("pause");
			//system("cls");
			break;
		case 15:
			cout << setw(32) << "Очистка данных об авиарейсах" << endl;
			avlTreeFlights = clearFlights(avlTreeFlights, listRegistration);
			system("pause");
			//system("cls");
			break;
		case 0:
			cout << setw(34) << "Произведен выход из программы!" << endl;
			clearAll(listRegistration, &hTablePassangers, avlTreeFlights);
			stop = true;
			break;
		default:
			cout << "Введен некоректный номер!" << endl;
			system("pause");
			system("cls");
			//system("cls")
			break;
		}
	}

	/*_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();*/
	system("pause");



}
