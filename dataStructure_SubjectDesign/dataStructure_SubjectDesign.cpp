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
	int count;//总量
	string proKind;//产品类
	int saleCount;//销出数量
	date dateIn;//进货日期
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
	string index;//proNO，即在在proNO上建立索引
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
	//从文件读数据，加载至内存
	ofstream fout("dbMain_tmp");
	fout << "test" << endl;
	/*ifstream fin("dbMain.txt");
	for (int i = 0; !fin.eof(); i++) {
		fin.getline(c, 255);
		string s(c);
	}
	//初始化Kind
	kindInit(kind);
	//初始化索引数组
	p = L->Head->next;
	proIdx = (Idx *)malloc(getLenLength(L)* sizeof(LNode));
	proIdx->length = getLenLength(L);
	for (int i = 0; i < proIdx->length; i++) {
		proIdx[i].index = p->data.proNO;
		proIdx[i].product = p;
		p = p->next;
	}
	sort(proIdx);*/
	cout << "初始化完成" << endl;
}
void printAll(Idx *index) {
	for (int i = 0; i < index->length; i++) {
		cout << proS(index[i].product->data) << endl;
	}
}
void sync(Idx *index) {
	//输出到dbMain_tmp
	//del dbMain.txt
	//ren dbMain_tmp
}
void findPro(LNode *pro, string proNo) {

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
	cout << "数据初始化中" << endl;
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
			cout << "请输入产品编号：" << endl;
			cin >> pro.proNO;
			cout << "请输入产品名称：" << endl;
			cin >> pro.name;
			cout << "请输入本次进货数量：" << endl;
			cin >> pro.count;
			cout << "请输入产品类别：" << endl;
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
				cout << "请输入商品号" << endl;
				cin >> proNO;
				findPro(proL, proNO);
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
					proL->data.saleCount += iCount;
					proL->data.count -= iCount;
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
	}
	return 0;
}

