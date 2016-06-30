// dataStructure_SubjectDesign.cpp : 定义控制台应用程序的入口点。
//
/*24.产品进销存管理系统（限1 人完成）（链式存储）
问题描述：针对某一种行业的库房的产品进销存情况进行管理。
基本要求：
1.	采用链式结构对库房的货品及其数量进行分类管理；
2.	可以进行产品类的添加、产品的添加、产品数量的添加；
3.	 能够查询库房每种产品的总量、进货日期、销出数量、销售时间等；
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
	int count;//总量
	char proKind[10];//产品类
	int saleCount;//销出数量
	char dateIn[11];//进货日期
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
	char index[13];//proNO，即在在proNO上建立索引
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
	//从文件读数据，加载至内存
	ifstream fin("dbMain.txt");
	//TODO 初始化各项
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
	cout << "初始化完成" << endl;
}
void printAll(Idx *index) {
	for (int i = 0; i < index->length; i++) {
		cout << proS(index->elem[i].proNode->data) << endl;
	}
}
void sync(Idx *index) {
	//输出到dbMain_tmp
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
	cout << "请输入相应数字以选择功能" << endl;
	cout << "0.查看当前所有产品" << endl;
	cout << "1.新加产品" << endl;
	cout << "2.修改指定产品信息" << endl;
}
void submenu() {
	cout << "请输入相应数字以选择功能" << endl;
	cout << "1.修改产品名" << endl;
	cout << "2.进货" << endl;
	cout << "3.销售" << endl;
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
	cout << "数据初始化中" << endl;
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
	cout << "请输入今天的日期：(yyyy-mm-dd)";
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
			cout << "请输入产品编号：";
			cin >> proL->data.proNO;
			cout << "请输入产品名称：" ;
			cin >> proL->data.name;
			cout << "请输入本次进货数量：";
			cin >> proL->data.count;
			cout << "请输入产品类别：";
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
				cout << "请输入商品号" << endl;
				cin >> proNO;
				cout << proNO << endl;
				findPro(proL,proNO, &proIdx);
				cout << proS(proL->data);
				switch (menuIdx)
				{
				case 1:
					cout << "请输入新的产品名：";
					cin >> proL->data.name;
					break;
				case 2:
					cout << "请输入进货数量：";
					cin >> iCount;
					proL->data.count += iCount;
					break;
				case 3:
					cout << "请输入销售数量：";
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
			cout << "输入有误，请重试" << endl;
			break;
		}
		cout << "进行其它操作吗？(exit退出)";
		cin >> switchS;
	}
	exit(0);
	return 0;
}

