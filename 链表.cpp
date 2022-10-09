#include<iostream>
#include <stdlib.h>
using namespace std;
​
struct Node
{
    int data;
    struct Node*next;
};
​
int main()
{
    int num;
    cin>>num;
    Node*head,*p,*q,*t;
    head=NULL;
    for(int i=0;i<num;i++)
    {
        p=(struct Node*)malloc(sizeof(struct Node));
        cin>>p->data;
        p->next=NULL;
        if(head==NULL)
        {
            head=p;
        }
        q->next=p;
        q=q->next;
    }
    for(t=head;t!=NULL;t=t->next)
    {
        cout<<t->data;
    }
}