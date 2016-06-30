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
#include <vector>
#include <Windows.h>

using namespace std;
int kindCount=0;
typedef struct Product
{
	char proNO[13];
	char name[20];
	int count;//����
	char proKind[10];//��Ʒ��
	int saleCount;//��������
	char dateIn[11];//��������
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
typedef struct idxType {
	char index[13];//proNO��������proNO�Ͻ�������
	LNode *proNode;
}idxElem;
typedef struct idx {
	idxElem *elem;
	int length;
	int idxsize;
}Idx;
Idx initIdx() {
	Idx proIdx;
	proIdx.elem = (idxElem *)malloc(sizeof(idxElem));
	proIdx.idxsize = 0;
	proIdx.length = 0;
	return proIdx;
}
void Qsort(Idx *index, int low, int high) {
	if (low >= high) {
		return;
	}
	int first = low;
	int last = high;
	idxElem key = index->elem[first];
	while (first < last) {
		while (first < last && strcmp(index->elem[last].index,key.index) >= 0) {
			--last;
		}
		index[first] = index[last];
		while (first < last&& strcpy_s(index->elem[first].index,key.index) <= 0) {
			++first;
		}
		index[last] = index[first];
	}
	index->elem[first] = key;
	Qsort(index, low, first - 1);
	Qsort(index, first + 1, high);
}
void sort(Idx *index) {
	Qsort(index, 0, index->length - 1);
}
void IdxInsert(Idx *index, LNode *product) {
	idxElem *newbase;
	newbase = (idxElem *)realloc(index->elem, (index->idxsize + 1) * sizeof(idxElem));
	index->idxsize += 1;
	strcpy_s(index->elem[index->length].index,13*sizeof(char), product->data.proNO);
	index->elem[index->length].proNode = product;
	index->length++;
	sort(index);
}
string proS(product pro) {
	char temp[64];
	sprintf_s(temp, "%d", pro.count);
	string count(temp);
	sprintf_s(temp, "%d", pro.saleCount);
	string Salecount(temp);
	string proNO(pro.proNO);
	string proName(pro.name);
	string proKind(pro.proKind);
	string dateIn(pro.dateIn);
	string pros = proNO + "\t" + proName + "\t" + count + "\t" + proKind + "\t" + Salecount + "\t" + dateIn;
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
char** kindInit() {
	char **kind=NULL;
	ifstream fin("dbKind.txt");
	char *tmpS = (char *)malloc(sizeof(char[10]));
	char **newbase;
	for (int i = 0; fin.getline(tmpS,10); i++) {
		newbase = (char **)realloc(kind, (++kindCount)*sizeof(char[10]));
		kind = newbase;
		kind[i] = tmpS;
		tmpS = (char *)malloc(sizeof(char[10]));
	}
	return kind;
}

void programInit(LinkList L, Idx *proIdx) {
	product *p=(product *)malloc(sizeof(product));
	const int LINE_LENGTH = 1024;
	char c[LINE_LENGTH];
	char *str;
	char *nextToken;
	//���ļ������ݣ��������ڴ�
	ifstream fin("dbMain.txt");
	//TODO ��ʼ������
	/*for (int i = 0; fin.getline(c, LINE_LENGTH); i++) {
		str = strtok_s(c, "\t", &nextToken);
		sprintf_s((*p).proNO, "%s", *str);
		str = strtok_s(NULL, "\t", &nextToken);
		strcpy_s((*p).name,20, str);
		str = strtok_s(NULL, "\t", &nextToken);
		(*p).count = atoi(str);
		str = strtok_s(NULL, "\t", &nextToken);
		strcpy_s((*p).proKind,10, str);
		str = strtok_s(NULL, "\t", &nextToken);
		(*p).saleCount = atoi(str);
		str = strtok_s(NULL, "\t", &nextToken);
		strcpy_s((*p).dateIn,10, str);
		LenInsert(L, *p, proIdx);
	}*/
	cout << "��ʼ�����" << endl;
}
void printAll(Idx *index) {
	for (int i = 0; i < index->length; i++) {
		cout << proS(index->elem[i].proNode->data) << endl;
	}
}
void sync(Idx *index) {
	//�����dbMain_tmp
	ofstream fout("dbMain_tmp");
	for (int i = 0; i < index->length; i++) {
		fout << proS(index->elem[i].proNode->data) << endl;
	}
	//del dbMain.txt
	system("del /f dbMain.txt");
	//ren dbMain_tmp
	system("ren dbMain_tmp dbMain.txt");
}
void findPro(LNode *p,char *proNo,Idx *index) {
	int low = 0, high = index->length-1;
	int mid = 0;
	while (low <= high) {
		mid = (low + high) / 2;
		if (strcmp(index->elem[low].index, proNo) == 0) {
			p = index->elem[low].proNode;
			cout << "testNode" << endl;
		}
		else if (strcmp(index->elem[high].index, proNo) == 0) {
			p = index->elem[high].proNode;
			cout << "testNode2" << endl;
		}
		mid = low + ((high + low) / 2);
		if (strcmp(index->elem[low].index, proNo)==0) {
			p = index->elem[low].proNode;
			cout << "testNode3" << endl;
		}
		if (strcmp(index->elem[mid].index, proNo) < 0) {
			low = mid + 1;
			cout << "testNode4" << endl;
		}
		else {
			high = mid - 1;
			cout << "testNode5" << endl;
		}
	}
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
bool kindIn(char thiskind[],char **kind) {
	bool in = false;
	for (int i = 0; i < kindCount;i++) {
		if (strcmp(thiskind,kind[i])==0) {
			in = true;
		}
	}
	return in;
}
int main()
{
	cout << "���ݳ�ʼ����" << endl;
	LinkList L = initLen();
	Idx proIdx=initIdx();
	char **kind=kindInit();
	char **tmpkind;
	char *proNO = (char*)malloc(sizeof(char[13]));
	char *proName = (char *)malloc(sizeof(char[20]));
	string switchS = "normal";
	LNode *proL=(LNode *)malloc(sizeof(LNode));
	int iCount;
	char *today=(char *)malloc(sizeof(char[20]));
	int menuIdx;
	programInit(L, &proIdx);
	cout << "�������������ڣ�(yyyy-mm-dd)";
	cin >> today;
	while (switchS.compare("exit") != 0) {
		menu();
		cin >> menuIdx;
		switch (menuIdx)
		{
		case 0:
			printAll(&proIdx);
			break;
		case 1:
			cout << "�������Ʒ��ţ�";
			cin >> proL->data.proNO;
			cout << "�������Ʒ���ƣ�" ;
			cin >> proL->data.name;
			cout << "�����뱾�ν���������";
			cin >> proL->data.count;
			cout << "�������Ʒ���";
			cin >> proL->data.proKind;
			proL->data.saleCount = 0;
			strcpy_s(proL->data.dateIn,13*sizeof(char), today);
			/*if (!kindIn(proL->data.proKind, kind)) {
				tmpkind = (char **)realloc(kind, (++kindCount) * sizeof(char[10]));
				kind = tmpkind;
				kind[kindCount] = proL->data.proKind;
			}*/
			LenInsert(L, proL->data, &proIdx);
			break;
			case 2:
				submenu();
				cin >> menuIdx;
				cout << "��������Ʒ��" << endl;
				cin >> proNO;
				cout << proNO << endl;
				findPro(proL,proNO, &proIdx);
				cout << proS(proL->data);
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
					if (!(proL->data.count < iCount)) {
						proL->data.saleCount += iCount;
						proL->data.count -= iCount;
					}
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
		cin >> switchS;
	}
	exit(0);
	return 0;
}

