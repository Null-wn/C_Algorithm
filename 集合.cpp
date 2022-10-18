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

List Read(); /*创建链表*/
void Print(List L); /*打印链表*/
List Function1(List L1, List L2);/*合并链表 并*/ 
List Function2(List L1,List L2);//交 
List Function3(List L1,List L2);//差 
void slim(List L);/*去除链表中重复元素*/

List Read() {
    List L, head;
    int num;
    int i;
    scanf("%d", &num);
    char array[100];
    for (i = 0; i < num; i++)
    {
        scanf("%c", &array[i]);//存进array 
    }
    for (int i = 0; i < num - 1; i++) {//控制比较轮次，一共 n-1 趟
        for (int j = 0; j < num - 1 - i; j++) {//控制两个挨着的元素进行比较，从小到大排序 
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    head = L = (List)malloc(sizeof(struct Node));///头结点
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
            free(q);/*回收多余空间*/
        }
        p = p->Next;
    }
}

List Function1(List L1, List L2) {
    List head, L;
    List P, S;
    head = L = (List)malloc(sizeof(struct Node));//定义一个新的头结点，用于指向新链表
    L->Next = NULL;
    P = L1->Next;//指向L1链表元素的开始位置
    S = L2->Next;//指向L2链表元素的开始位置
    while (P != NULL && S != NULL) {
        if (P->Data <= S->Data) {//判断两个指针指向的数据谁更小，将新的链表指针指向该位置
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
    slim(head);//去重 
    return head;
}

bool isin(char ch,List L2)//判断ch元素是否在L2链表中 
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

//L1和L2的并集，L1和L2都有的元素 
List Function2(List L1,List L2) {
    List head,L;
    List P=L1->Next;
    head = L = (List)malloc(sizeof(struct Node));//定义一个新的头结点，用于指向新链表
    L->Next = NULL;
    while (P != NULL)
    {
        if(isin(P->Data,L2))//判断L1的一个元素是否在L2里面 
        {
        	L->Next = (List)malloc(sizeof(struct Node));
        	L->Next->Data = P->Data;
        	L = L->Next;
		}
		P=P->Next;
    }
    L->Next = NULL;//非常关键，因为这个错了很久，如果不加这一步，会继续输出 L->Next = P->Next之后的内容！！！
    return head;
}

//L1和L2的差集，只在L1不在L2的元素 ，只需要把function2的代码复制下来，然后否定调用的isin函数
List Function3(List L1,List L2) {
    List head,L;
    List P=L1->Next;
    head = L = (List)malloc(sizeof(struct Node));//定义一个新的头结点，用于指向新链表
    L->Next = NULL;
    while (P != NULL)
    {
        if(!isin(P->Data,L2))//判断L1的一个元素是否在L2里面 ，如果不在，放入L链表 
        {
        	L->Next = (List)malloc(sizeof(struct Node));
        	L->Next->Data = P->Data;
        	L = L->Next;
		}
		P=P->Next;
    }
    L->Next = NULL;//非常关键，因为这个错了很久，如果不加这一步，会继续输出 L->Next = P->Next之后的内容！！！
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

	cout<<"1并集\n2交集\n3差集\n"; 
	int select;
	cin>>select;
	
	if(select==1)
	{
		cout <<"并集"<<endl;
    	La=Function1(L1,L2);
    	Print(La);//并集 
	}
    
    if(select==2)
    {
    	cout <<"交集"<< endl;
    	Lb=Function2(L1,L2);
   		Print(Lb);//交集 
	}
    
    if(select==3)
    {
    	cout <<"差集"<< endl;//属于L1但是不属于L2 
		Lc = Function3(L1,L2);
 		Print(Lc);//差集 
	}
    
    return 0;
}