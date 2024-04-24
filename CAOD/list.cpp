#include"list.h"

cycList* init(string nPass, string nFl, string nTick)
{
	cycList* lst = new cycList;
	lst->numberOfFlight = nFl;
	lst->numberOfPassword = nPass;
	lst->numberOfTicket = nTick;
	lst->next = lst;
	lst->prev = lst;
	return(lst);
}
cycList* addelem(cycList* lst, string nPass, string nFl, string nTick) 
{
	if (lst == nullptr) {
		lst = init(nPass, nFl, nTick);
		return(lst);
	}
	cycList* temp = new cycList, * p;
	p = lst->next;
	lst->next = temp;
	temp->numberOfFlight = nFl;
	temp->numberOfPassword = nPass;
	temp->numberOfTicket = nTick;
	temp->next = p;
	temp->prev = lst;
	p->prev = temp;
	return(sortlist(temp));
}
cycList* deletelemptr(cycList* lst)
{
	cycList* prev, * next;
	prev = lst->prev;
	next = lst->next;
	if (prev == lst && next == lst) {
		free(lst);
		return(nullptr);
	}
	prev->next = lst->next;
	next->prev = lst->prev;
	free(lst);
	return(prev);
}
cycList* deletelem(cycList* lst, string nTick) {
	if (lst == nullptr) {
		return lst;
	}
	cycList* p;
	bool isDel = false;
	if (lst->numberOfTicket == nTick) {
		p = lst->prev;
	}
	else {
		p = lst;
	}
	do {
		if (lst->numberOfTicket == nTick) {
			lst = deletelemptr(lst);
			isDel = true;
		}
		else {
			lst = lst->next; // ������� � ���������� ����
		}
	} while (p != lst && lst != nullptr); // ������� ��������� ������
	if (!isDel) {
		cout << "No value for delete" << endl;
	}
	return sortlist(lst);
}
void listprint(cycList* lst)
{
	if (lst == nullptr) {
		cout << "��� ���������� ������������������ �� �����!" << endl;
		return;
	}
	cout << setw(15) << "����� ������" << setw(18) << "����� ��������" << setw(14) << "����� �����" << endl;
	cycList* p;
	p = lst;
	do {
		cout << setw(15) << p->numberOfTicket << setw(18) << p->numberOfPassword << setw(14) << p->numberOfFlight << endl; // ����� �������� �������� p
		p = p->next; // ������� � ���������� ����
	} while (p != lst); // ������� ��������� ������
	cout << endl;
}
void listprintr(cycList* lst)
{
	if (lst == nullptr) {
		return;
	}
	cout << setw(15) << "����� ������" << setw(18) << "����� ��������" << setw(14) << "����� �����" << endl;
	cycList* p;
	p = lst;
	do {
		p = p->prev;  // ������� � ����������� ����
		cout << setw(15) << p->numberOfTicket << setw(18) << p->numberOfPassword << setw(14) << p->numberOfFlight << endl; // ����� �������� �������� p
	} while (p != lst); // ������� ��������� ������
	cout << endl;
}
int findMax(cycList* lst) {
	int max = 0;
	cycList* p;
	p = lst;
	do {
		if (stoi(p->numberOfTicket) > max) {
			max = stoi(p->numberOfTicket);
		}
		p = p->next;
	} while (p != lst); // ������� ��������� ������
	return max;
}
cycList* sortlist(cycList* lst) {
	if (lst == nullptr) {
		return lst;
	}
	vector <sortli> additional(findMax(lst) + 1);
	cycList* p;
	p = lst;
	int index;
	do {
		index = stoi(p->numberOfTicket);
		additional[index].count += 1;
		additional[index].numberOfFlight = p->numberOfFlight;
		additional[index].numberOfPassword = p->numberOfPassword;
		additional[index].numberOfTicket = p->numberOfTicket;
		p = p->next;  // ������� � ����������� ����
	} while (p != lst); // ������� ��������� ������
	for (int i = 0; i < additional.size(); i++) {
		if (additional[i].count > 0) {
			lst->numberOfFlight = additional[i].numberOfFlight;
			lst->numberOfPassword = additional[i].numberOfPassword;
			lst->numberOfTicket = additional[i].numberOfTicket;
			lst = lst->next;
		}
	}
	return lst;
}
bool isUniqAll(cycList* lst, string nTick, string nPass, string nFl) {
	if (lst == nullptr) {
		return true;
	}
	cycList* p;
	p = lst;
	do {
		if (p->numberOfTicket == nTick || (p->numberOfPassword == nPass && p->numberOfFlight == nFl)) return false;
		p = p->next; // ������� � ���������� ����
	} while (p != lst); // ������� ��������� ������
	return true;
}
string getNumberFlight(cycList* lst, string nTick) {
	cycList* p;
	p = lst;
	do {
		if (p->numberOfTicket == nTick) return p->numberOfFlight;
		p = p->next; // ������� � ���������� ����
	} while (p != lst); // ������� ��������� ������
}
bool isRegisterOfFlight(cycList* lst, string nFl) {
	if (lst == nullptr) {
		return false;
	}
	cycList* p;
	p = lst;
	do {
		if (p->numberOfFlight == nFl) return true;
		p = p->next; // ������� � ���������� ����
	} while (p != lst); // ������� ��������� ������
	return false;
}
bool isRegister(cycList* lst, string nPass) {
	if (lst == nullptr) {
		return false;
	}
	cycList* p;
	p = lst;
	do {
		if (p->numberOfPassword == nPass) return true;
		p = p->next; // ������� � ���������� ����
	} while (p != lst); // ������� ��������� ������
	return false;
}
void findelemByPass(cycList* lst, string nPass) {
	bool isFind = false;
	if (lst == nullptr) {
		cout << "�������� �� ��������������� �� �����!" << endl;
		return;
	}
	cycList* p;
	p = lst;
	do {
		if (p->numberOfPassword == nPass) {
			if (!isFind) {
				cout << setw(15) << "����� ������" << setw(18) << "����� ��������" << setw(14) << "����� �����" << endl;
				isFind = true;
			}
			cout << setw(15) << p->numberOfTicket << setw(18) << p->numberOfPassword << setw(14) << p->numberOfFlight << endl;
		}
		p = p->next; // ������� � ���������� ����
	} while (p != lst); // ������� ��������� ������
	if (!isFind) cout << "�������� �� ��������������� �� �����!" << endl;
	return;
}
void findelemByNumber(cycList* lst, string nFl) {
	bool isFind = false;
	if (lst == nullptr) {
		cout << "�� ���� �� ����������������� ���������!" << endl;
		return;
	}
	cycList* p;
	p = lst;
	do {
		if (p->numberOfFlight == nFl) {
			if (!isFind) {
				cout << setw(15) << "����� ������" << setw(18) << "����� ��������" << setw(14) << "����� �����" << endl;
				isFind = true;
			}
			cout << setw(15) << p->numberOfTicket << setw(18) << p->numberOfPassword << setw(14) << p->numberOfFlight << endl;
		}
		p = p->next; // ������� � ���������� ����
	} while (p != lst); // ������� ��������� ������
	if (!isFind) cout << "�� ���� �� ����������������� ���������!" << endl;
	return;
}

void clearList(cycList* head) {
	cycList* curr = head;
	cycList* next = nullptr;
	while (curr != nullptr) {
		next = curr->next;
		delete curr;
		curr = next;
		if (curr == head) {
			break;  // ������ �������, ������� �� �����
		}
	}
}