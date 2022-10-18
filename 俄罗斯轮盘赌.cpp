#include<iostream>
#include<stdlib.h>
#include <sys/time.h>
using namespace std;

struct people
{
	int data;//序号 
	struct people*next;
};

void load(bool bullet[],int k)
{
	srand(time(0)+k);
	for(int i=0;i<6;i++)
	{
		bullet[i]=false;//重置每轮手枪状态 
	}
	int m= rand() % 6+1;//装入m颗子弹 ，随机数 
	for(int i=0;i<m;)//子弹随机位置 
	{
		int t;
		srand(time(0)+i+k);
		t=rand()%6+1;
		if(bullet[t]==false)
		{
			bullet[t]=true;//装入子弹 
			i++;
		}
	} 
}

int main()
{
	int n,m;

	people *head,*p,*q,*t;
	cin>>n;//输入赌徒人数
	head=NULL;
	for(int i=1;i<=n;i++)
	{
		p=(struct people*)malloc(sizeof(struct people));
		p->data=i;
        p->next=NULL;
        if(head==NULL)
        {
        	head=p;
		}
        q->next=p;
        q=q->next;
	}
	q->next=head;//循环链表 
	
	
//		t=head;
//		for(int i=0;i<10;i++)
//		{
//			cout<<t->data<<" ";
//			t=t->next;
//		}	
	
	bool bullet[6];
	t=head;		bool ok=false;		int k=0;
	while(true)
	{
		for(int i=0;i<6;i++)
		bullet[i]=false;
		load(bullet,k);//随机数字和位置上膛 
		k++;
	
//			for(int i=0;i<6;i++)
//			{
//				if(bullet[i])
//				cout<<"yes"<<" ";
//				else
//				cout<<"no"<<" ";
//			} 
//			cout<<endl;

		int turn=0;
		for(;turn<6;turn++)
		{
			if(n==1)
			{
				cout<<"获胜者是:"<<t->data;
				ok=true;
				break;
			}
			if(bullet[turn]==true)//淘汰，删除结点 
			{
				people *q;
				q = t->next;
			    t->next = q->next;
			    free(q);
				n--;
			}
			t=t->next;
		}
		if(ok==true)
		break;

	}
	
} 
