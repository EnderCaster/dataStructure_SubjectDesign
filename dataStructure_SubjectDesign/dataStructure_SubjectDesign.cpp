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
	//���ļ������ݣ��������ڴ�
	//��ʼ��
}
int main()
{
    return 0;
}

