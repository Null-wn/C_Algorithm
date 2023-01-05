#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

typedef char ElementType;
typedef struct Node* PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /*��������*/
void Print(List L); /*��ӡ����*/
List Function1(List L1, List L2);/*�ϲ����� ��*/ 
List Function2(List L1,List L2);//�� 
List Function3(List L1,List L2);//�� 
void slim(List L);/*ȥ���������ظ�Ԫ��*/

List Read() {
    List L, head;
    int num;
    int i;
    scanf("%d", &num);
    char array[100];
    for (i = 0; i < num; i++)
    {
        scanf("%c", &array[i]);//���array 
    }
    for (int i = 0; i < num - 1; i++) {//���ƱȽ��ִΣ�һ�� n-1 ��
        for (int j = 0; j < num - 1 - i; j++) {//�����������ŵ�Ԫ�ؽ��бȽϣ���С�������� 
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    head = L = (List)malloc(sizeof(struct Node));///ͷ���
    L->Next = NULL;
    for (i = 0; i < num; i++) {
        L->Next = (List)malloc(sizeof(struct Node));
        L->Next->Data = array[i];
        L = L->Next;
    }
    L->Next = NULL;
    return head;
}

void slim(List L)
{
    List p, q;
    p = L->Next;
    while (p != NULL) {
        while (p->Next != NULL && p->Data == p->Next->Data) {
            q = p->Next;
            p->Next = q->Next;
            free(q);/*���ն���ռ�*/
        }
        p = p->Next;
    }
}

List Function1(List L1, List L2) {
    List head, L;
    List P, S;
    head = L = (List)malloc(sizeof(struct Node));//����һ���µ�ͷ��㣬����ָ��������
    L->Next = NULL;
    P = L1->Next;//ָ��L1����Ԫ�صĿ�ʼλ��
    S = L2->Next;//ָ��L2����Ԫ�صĿ�ʼλ��
    while (P != NULL && S != NULL) {
        if (P->Data <= S->Data) {//�ж�����ָ��ָ�������˭��С�����µ�����ָ��ָ���λ��
            L->Next = P;
            L = L->Next;
            P = P->Next;
        }
        else {
            L->Next = S;
            L = L->Next;
            S = S->Next;
        }
    }
    if (P != NULL) {
        L->Next = P;
    }
    if (S != NULL) {
        L->Next = S;
    }
    L1->Next = NULL;
    L2->Next = NULL;
    slim(head);//ȥ�� 
    return head;
}

bool isin(char ch,List L2)//�ж�chԪ���Ƿ���L2������ 
{
	List S=L2;
	while(S!=NULL)
	{
		if(ch==S->Data)
		{
			return true;
		}
		S=S->Next;
	}
	return false;
} 

//L1��L2�Ĳ�����L1��L2���е�Ԫ�� 
List Function2(List L1,List L2) {
    List head,L;
    List P=L1->Next;
    head = L = (List)malloc(sizeof(struct Node));//����һ���µ�ͷ��㣬����ָ��������
    L->Next = NULL;
    while (P != NULL)
    {
        if(isin(P->Data,L2))//�ж�L1��һ��Ԫ���Ƿ���L2���� 
        {
        	L->Next = (List)malloc(sizeof(struct Node));
        	L->Next->Data = P->Data;
        	L = L->Next;
		}
		P=P->Next;
    }
    L->Next = NULL;//�ǳ��ؼ�����Ϊ������˺ܾã����������һ������������ L->Next = P->Next֮������ݣ�����
    return head;
}

//L1��L2�Ĳ��ֻ��L1����L2��Ԫ�� ��ֻ��Ҫ��function2�Ĵ��븴��������Ȼ��񶨵��õ�isin����
List Function3(List L1,List L2) {
    List head,L;
    List P=L1->Next;
    head = L = (List)malloc(sizeof(struct Node));//����һ���µ�ͷ��㣬����ָ��������
    L->Next = NULL;
    while (P != NULL)
    {
        if(!isin(P->Data,L2))//�ж�L1��һ��Ԫ���Ƿ���L2���� ��������ڣ�����L���� 
        {
        	L->Next = (List)malloc(sizeof(struct Node));
        	L->Next->Data = P->Data;
        	L = L->Next;
		}
		P=P->Next;
    }
    L->Next = NULL;//�ǳ��ؼ�����Ϊ������˺ܾã����������һ������������ L->Next = P->Next֮������ݣ�����
    return head;
}

void Print(List L)
{
    List N;
    N = L;
    while (N->Next != NULL) {
        printf("%c", N->Next->Data);
        N = N->Next;
    }
    printf("\n");
}

int main()
{
    List L1, L2, La, Lb, Lc;
    L1 = Read();
    L2 = Read();
     
    slim(L1);
    slim(L2);
//  Print(L1);
//	Print(L2);

	cout<<"1����\n2����\n3�\n"; 
	int select;
	cin>>select;
	
	if(select==1)
	{
		cout <<"����"<<endl;
    	La=Function1(L1,L2);
    	Print(La);//���� 
	}
    
    if(select==2)
    {
    	cout <<"����"<< endl;
    	Lb=Function2(L1,L2);
   		Print(Lb);//���� 
	}
    
    if(select==3)
    {
    	cout <<"�"<< endl;//����L1���ǲ�����L2 
		Lc = Function3(L1,L2);
 		Print(Lc);//� 
	}
    
    return 0;
}