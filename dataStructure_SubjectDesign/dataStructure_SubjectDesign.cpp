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

using namespace std;
typedef struct Product
{
	string proNO;
	string name;
	int count;
	string proKind;


}product;
typedef struct LNode
{
	LNode *pre;
	product data;
	LNode *next;
}LNode;
typedef struct Len {

}len;
void programInit() {
	//从文件读数据，加载至内存
	//初始化
}
int main()
{
    return 0;
}

