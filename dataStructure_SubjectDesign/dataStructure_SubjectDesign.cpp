// dataStructure_SubjectDesign.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*24.��Ʒ���������ϵͳ����1 ����ɣ�����ʽ�洢��
�������������ĳһ����ҵ�Ŀⷿ�Ĳ�Ʒ������������й���
����Ҫ��
1.	������ʽ�ṹ�Կⷿ�Ļ�Ʒ�����������з������
2.	���Խ��в�Ʒ�����ӡ���Ʒ����ӡ���Ʒ��������ӣ�
3.	 �ܹ���ѯ�ⷿÿ�ֲ�Ʒ���������������ڡ���������������ʱ��ȣ�
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int kindCount=0;
typedef struct DATE {
	int year;
	int month;
	int day;
}date;
date initDate(int year, int month, int day) {
	date newdate;
	newdate.year = year;
	newdate.month = month;
	newdate.day = day;
	return newdate;
}
typedef struct Product
{
	string proNO;
	string name;
	int count;//����
	string proKind;//��Ʒ��
	int saleCount;//��������
	date dateIn;//��������
}product,ElemType;
typedef struct LNode
{
	LNode *pre;
	product data;
	LNode *next;
}LNode;
typedef struct Len {
	LNode *Head;
	LNode *Tail;
}*LinkList;
typedef struct idx {
	string index;//proNO��������proNO�Ͻ�������
	LNode *product;
	int length;
}Idx;
void Qsort(Idx *index, int low, int high) {
	if (low >= high) {
		return;
	}
	int first = low;
	int last = high;
	Idx key = index[first];
	while (first < last) {
		while (first < last && index[last].index.compare(key.index) >= 0) {
			--last;
		}
		index[first] = index[last];
		while (first < last&& index[first].index.compare(key.index) <= 0) {
			++first;
		}
		index[last] = index[first];
	}
	index[first] = key;
	Qsort(index, low, first - 1);
	Qsort(index, first + 1, high);
}
void sort(Idx *index) {
	Qsort(index, 0, index->length - 1);
}
void IdxInsert(Idx *index, LNode *product) {
	index->length += 1;
	index = (Idx *)realloc(index, index->length);
	index[index->length - 1].index = product->data.proNO;
	index[index->length - 1].product = product;
	sort(index);
}

string proS(product pro) {
	char temp[64];
	sprintf_s(temp, "%d", pro.count);
	string count(temp);
	string pros = pro.proNO + "\t" + pro.name + "\t" + count + "\t" + pro.proKind;
	return pros;
}

LinkList initLen() {
	LinkList L = (LinkList)malloc(sizeof(LinkList));
	L->Head = (LNode *)malloc(sizeof(LNode));
	L->Tail = (LNode *)malloc(sizeof(LNode));
	L->Head->pre = NULL;
	L->Head->next = L->Tail;
	L->Tail->pre = L->Head;
	L->Tail->next = NULL;
	return L;
}
void LenInsert(LinkList L, product pro, Idx *index) {
	LNode *p;
	p = (LNode *)malloc(sizeof(LNode));
	p->next = L->Tail;
	p->pre = L->Tail->pre;
	L->Tail->pre = p;
	p->pre->next = p;
	p->data = pro;
	IdxInsert(index, p);
}
int getLenLength(LinkList L) {
	LNode *p = L->Head->next;
	int length = 0;
	while (p) {
		length++;
		p = p->next;
	}
	length--;
	return length;
}
void kindInit(string kind[]) {
	ifstream fin("dbKind.txt");
	string tmpS;
	for (int i = 0; !fin.eof(); i++) {
		kind = (string *)realloc(kind, ++kindCount);
		fin >> kind[i];
	}
}

void programInit(LinkList L, string kind[], Idx *proIdx) {
	LNode *p;
	char *c=NULL;
	string s;
	//���ļ������ݣ��������ڴ�
	ofstream fout("dbMain_tmp");
	fout << "test" << endl;
	/*ifstream fin("dbMain.txt");
	for (int i = 0; !fin.eof(); i++) {
		fin.getline(c, 255);
		string s(c);
	}
	//��ʼ��Kind
	kindInit(kind);
	//��ʼ����������
	p = L->Head->next;
	proIdx = (Idx *)malloc(getLenLength(L)* sizeof(LNode));
	proIdx->length = getLenLength(L);
	for (int i = 0; i < proIdx->length; i++) {
		proIdx[i].index = p->data.proNO;
		proIdx[i].product = p;
		p = p->next;
	}
	sort(proIdx);*/
	cout << "��ʼ�����" << endl;
}
void printAll(Idx *index) {
	for (int i = 0; i < index->length; i++) {
		cout << proS(index[i].product->data) << endl;
	}
}
void sync(Idx *index) {
	//�����dbMain_tmp
	//del dbMain.txt
	//ren dbMain_tmp
}
void findPro(LNode *pro, string proNo) {

}
void menu() {
	cout << "��������Ӧ������ѡ����" << endl;
	cout << "0.�鿴��ǰ���в�Ʒ" << endl;
	cout << "1.�¼Ӳ�Ʒ" << endl;
	cout << "2.�޸�ָ����Ʒ��Ϣ" << endl;
}
void submenu() {
	cout << "��������Ӧ������ѡ����" << endl;
	cout << "1.�޸Ĳ�Ʒ��" << endl;
	cout << "2.����" << endl;
	cout << "3.����" << endl;
}
bool kindIn(string thiskind,string kind[]) {
	bool in = false;
	for (int i = 0; i < kindCount;i++) {
		if (thiskind.compare(kind[i])) {
			in = true;
		}
	}
	return in;
}
int main()
{
	cout << "���ݳ�ʼ����" << endl;
	LinkList L = initLen();
	Idx proIdx;
	string *kind=NULL;
	string proNO;
	string switchS = "normal";
	product pro;
	LNode *proL=NULL;
	int iCount;
	programInit(L, kind, &proIdx);
	while (switchS.compare("exit") != 0) {
		menu();
		int menuIdx;
		cin >> menuIdx;
		switch (menuIdx)
		{
		case 0:
			printAll(&proIdx);
			break;
		case 1:
			cout << "�������Ʒ��ţ�" << endl;
			cin >> pro.proNO;
			cout << "�������Ʒ���ƣ�" << endl;
			cin >> pro.name;
			cout << "�����뱾�ν���������" << endl;
			cin >> pro.count;
			cout << "�������Ʒ���" << endl;
			cin >> pro.proKind;
			pro.saleCount = 0;
			pro.dateIn = initDate(2016,6,28);
			if (!kindIn(pro.proKind, kind)) {
				kind = (string *)realloc(&kind, ++kindCount);
				kind[kindCount] = pro.proKind;
			}
			LenInsert(L, pro, &proIdx);
			break;
			case 2:
				submenu();
				cin >> menuIdx;
				cout << "��������Ʒ��" << endl;
				cin >> proNO;
				findPro(proL, proNO);
				switch (menuIdx)
				{
				case 1:
					cout << "�������µĲ�Ʒ����";
					cin >> proL->data.name;
					break;
				case 2:
					cout << "���������������";
					cin >> iCount;
					proL->data.count += iCount;
					break;
				case 3:
					cout << "����������������";
					cin >> iCount;
					proL->data.saleCount += iCount;
					proL->data.count -= iCount;
					break;
				default:
					break;
				}

				break;
		default:
			cout << "��������������" << endl;
			break;
		}
		cout << "��������������(exit�˳�)";
	}
	return 0;
}

