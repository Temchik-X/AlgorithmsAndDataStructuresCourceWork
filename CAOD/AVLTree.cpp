#pragma once
#include "AVLTree.h"

unsigned char height(node* tree)
{
	if (tree)
		return tree->height;
	else
		return 0;
}
int balanceFactor(node* tree)
{
	return height(tree->right) - height(tree->left);
}
void fixHeight(node* tree)
{
	int heightLeft = height(tree->left);
	int heughtRight = height(tree->right);
	tree->height = (heightLeft > heughtRight ? heightLeft : heughtRight) + 1;
}
void fixDepth(node* tree) {

	if (!tree) return;
	if (tree->left)
		tree->left->depth = tree->depth + 1;
	if (tree->right)
		tree->right->depth = tree->depth + 1;
	fixDepth(tree->left);
	fixDepth(tree->right);
}
node* smallRotateRight(node* tree)
{
	node* tmp = tree->left;
	tree->left = tmp->right;
	tmp->right = tree;
	fixHeight(tree);
	fixHeight(tmp);
	return tmp;
}
node* smallRotateLeft(node* tmp)
{
	node* tree = tmp->right;
	tmp->right = tree->left;
	tree->left = tmp;
	fixHeight(tmp);
	fixHeight(tree);
	return tree;
}
node* balance(node* tree)
{
	fixHeight(tree);
	if (balanceFactor(tree) == 2)
	{
		if (balanceFactor(tree->right) < 0)
			tree->right = smallRotateRight(tree->right);
		node* tmp = smallRotateLeft(tree);
		return tmp;
	}
	if (balanceFactor(tree) == -2)
	{
		if (balanceFactor(tree->left) > 0)
			tree->left = smallRotateLeft(tree->left);
		node* tmp = smallRotateRight(tree);
		return tmp;
	}
	return tree;
}
node* addVert(node* tree, int k, string nFl, string nA, string dep, string dest, string dateDep, string timeDep, int nSeats, int nFSeats)
{
	if (!tree) return new node(k, nFl, nA, dep, dest, dateDep, timeDep, nSeats, nFSeats);
	if (k < tree->data)
		tree->left = addVert(tree->left, k, nFl, nA, dep, dest, dateDep, timeDep, nSeats, nFSeats);
	else if (k > tree->data)
		tree->right = addVert(tree->right, k, nFl, nA, dep, dest, dateDep, timeDep, nSeats, nFSeats);
	else {
		cout << "The vertex is already in the tree" << endl;
		return tree;
	}
	return balance(tree);
}
node* findMin(node* tree)
{
	return tree->left ? findMin(tree->left) : tree;
}
node* removeMin(node* tree)
{
	if (tree->left == 0)
		return tree->right;
	tree->left = removeMin(tree->left);
	return balance(tree);
}
node* removeVert(node* tree, int k)
{
	if (!tree) return 0;
	if (k < tree->data)
		tree->left = removeVert(tree->left, k);
	else if (k > tree->data)
		tree->right = removeVert(tree->right, k);
	else
	{
		node* q = tree->left;
		node* r = tree->right;
		delete tree;
		if (!r) return q;
		node* min = findMin(r);
		min->right = removeMin(r);
		min->left = q;
		return balance(min);
	}
	return balance(tree);
}
void ShowTree(node* tree, int indent) {
	if (tree) {
		ShowTree(tree->right, indent + 1);
		for (int i = 1; i <= indent; i++) cout << "   ";
		cout << tree->numberOfFlight << endl;
		ShowTree(tree->left, indent + 1);
	}
}
void ShowElements(node* tree, bool* f) {
	if (tree) {
		ShowElements(tree->left, f);
		ShowElements(tree->right, f);
		if (!*f) {
			cout << setw(14) << "Номер рейса" << setw(21) << "Имя авиакомпании" << setw(20) << "Пункт вылета" << setw(20) << "Пункт назначения" << setw(29) << "Количество свободных мест" << endl;
			*f = true;
		}
		cout << setw(14) << tree->numberOfFlight;
		cout << setw(21) << tree->nameOfAirline;
		cout << setw(20) << tree->departure;
		cout << setw(20) << tree->destination;
		cout << setw(29) << tree->numberOfFreeSeats << endl;
	}
}
int boyerMoore(string text, string pattern) {
	int n = text.length();
	int m = pattern.length();
	if (m == 0) return 0;
	if (n < m) return -1;
	vector<int> jump(65536);
	// таблица смещений, которая определяет, на какое расстояние можно сдвинуть искомую подстроку вправо, если не совпал текущий символ.
	for (int i = 0; i < 65536; i++) jump[i] = m;
	for (int i = 0; i < m - 1; i++) jump[(unsigned short)pattern[i]] = m - i - 1; // вычисляем смещение 
	int i = m - 1;
	int j = m - 1;
	while (i < n) {
		if (text[i] == pattern[j]) {
			if (j == 0) return i; // если все символы искомой подстроки найдены, возвращаем индекс первого символа найденной подстроки
			i--;
			j--;
		}
		else {
			i += jump[(unsigned short)text[i]]; // сдвигаем индекс начала сравнения на максимально возможное смещение
			j = m - 1;
			if (i > n - 1) break;
		}
	}
	return -1;
}
void findByBM(node* tree, string pattern, bool* f) {
	if (tree) {
		findByBM(tree->left, pattern, f);
		findByBM(tree->right, pattern, f);
		int index = boyerMoore(tree->destination, pattern);
		if (index == -1) return;
		if (!*f) cout << setw(18) << "Номер рейса" << setw(25) << "Пункт назначения" << setw(20) << "Дата вылета"  << setw(20) << "Время вылета"  << endl;
		*f = true;
		cout << setw(18) << tree->numberOfFlight;
		cout << setw(25) << tree->destination;
		cout << setw(20) << tree->dateOfDeparture;
		cout << setw(20) << tree->timeOfDeparture << endl;
	}
}
void findElem(node* tree, int k, bool* flag) {
	if (*flag)
		return;
	if (!tree) {
		return;
	}
	if (tree->data == k) {
		*flag = true;
		cout << setw(28) << "Результаты поиска" << endl;
		cout << setw(15) << "Номер рейса: "   << tree->numberOfFlight << endl;
		cout << setw(20) << "Имя авиакомпании: "   << tree->nameOfAirline << endl;
		cout << setw(21) << "Пункт отправления: "  << tree->departure << endl;
		cout << setw(20) << "Пункт назначения: "  << tree->destination << endl;
		cout << setw(15) << "Дата вылета: "  << tree->dateOfDeparture << endl;
		cout << setw(16) << "Время вылета: "  << tree->timeOfDeparture << endl;
		cout << setw(25) << "Общее количество мест: "  << tree->numberOfSeats << endl;
		cout << setw(29) << "Количество свободных мест: "  << tree->numberOfFreeSeats << endl;
		return;
	}
	else if (tree->data < k) {
		findElem(tree->right, k, flag);
	}
	else {
		findElem(tree->left, k, flag);
	}
}
int getNumber(string str){
	return stoi(str.substr(4, 6)) + str[0] + str[1]*str[1] + str[2]* str[2]* str[2];
}
node* clearTree(node* tree) {
	if (tree) {
		clearTree(tree->left);
		clearTree(tree->right);
		delete tree;
	}
	return nullptr;
}
void checkUniq(node* tree, int k, bool* flag) {
	if (!*flag)
		return;
	if (!tree) {
		return;
	}
	if (tree->data == k) {
		*flag = false;
		return;
	}
	else if (tree->data < k) {
		checkUniq(tree->right, k, flag);
	}
	else {
		checkUniq(tree->left, k, flag);
	}
}
bool checkUniq(node* tree, string nFl, bool f) {
	if (tree) {
		f = checkUniq(tree->left, nFl, f);
		f = checkUniq(tree->right, nFl, f);
		if (getNumber(nFl) == getNumber(tree->numberOfFlight) && nFl == tree->numberOfFlight) return (f && false);
		return f;
	}
	return f;
}
void countFreeSeats(node* tree, int k, bool* flag, int* count) {
	if (*flag)
		return;
	if (!tree) {
		return;
	}
	if (tree->data == k) {
		*flag = true;
		if (tree->numberOfFreeSeats == 0) return;
		*count = tree->numberOfFreeSeats;
		tree->numberOfFreeSeats -= 1;
		return;
	}
	else if (tree->data < k) {
		countFreeSeats(tree->right, k, flag, count);
	}
	else {
		countFreeSeats(tree->left, k, flag, count);
	}
}
void returnFreeSeats(node* tree, int k, bool* flag, int* count) {
	if (*flag)
		return;
	if (!tree) {
		return;
	}
	if (tree->data == k) {
		*flag = true;
		tree->numberOfFreeSeats += 1;
		*count = tree->numberOfFreeSeats;
		return;
	}
	else if (tree->data < k) {
		returnFreeSeats(tree->right, k, flag, count);
	}
	else {
		returnFreeSeats(tree->left, k, flag, count);
	}
}