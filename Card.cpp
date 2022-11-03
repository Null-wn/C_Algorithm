#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int c[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,14,14};  //һ���������� ,14��С�� 
int player1[27]; 
int player2[27];

struct Card
{
	int data;
	Card *next;
};

Card *h1=NULL,*h2=NULL,*p=NULL,*q=NULL,*play=NULL;//play��ǰ�����ϵ��Ƶ�ָ�� 

//��Ϸ���� 
void Instructions(){
	char s;
	cout<<"��ӭ������С��������Ϸ��"<<endl;
	cout<<"�Ƿ�鿴��Ϸ�����ǣ�y���������ַ�����";
	cin>>s;
	if(s == 'y'){
		cout<<endl;
		cout<<"һ�����ܹ���54�ţ�ϴ�ƺ��Ϊ2����������Ϸ��һ��Ϊ��ң�һ��Ϊ�������"<<endl;
		cout<<"ÿ��ֻ�ܳ�����һ���ƣ����ȳ���ĵ����ʧ�ܣ�"<<endl; 
		cout<<endl;
	}
	else
	    cout<<endl;
}

//ϴ�ƺ����������Ƶ�˳�� 
void Shuffle(int *c){
	cout<<"ϴ���С�����"<<endl;
	srand(unsigned(time(NULL)));
	int a = rand();
	while(a>0){
		for(int i = 53; i > 0; i--)
		{
			srand(unsigned(time(NULL))); 
            int currentRandom = rand() % i;
            swap(c[i],c[currentRandom]);
        }
        a--;
	}
	
	//���ƣ� ��Ϊ2�ݣ�����洢 
	h1=p=(Card*)malloc(sizeof(Card));
	h2=q=(Card*)malloc(sizeof(Card));
	
	for(int i = 0;i < 27;i++){
		p->next=(Card*)malloc(sizeof(Card));
		p->data = c[i];
		p=p->next;
	}
	p->next=NULL;
	
	for(int i = 27;i < 54;i++){
		q->next=(Card*)malloc(sizeof(Card));
		q->data = c[i];
		q=q->next;
	}
	q->next=NULL;
}

bool isempty(Card *h)
{
	if(h->next==NULL)
	{
		return true;
	}
	else
	return false;
} 

void add(Card *pl,Card *tp)//�ѳ����Ʒŵ��ƾ����� tp���ͷ�ڵ㣬pl�ƾ�ͷ�ڵ� 
{
	Card *t=pl,*f=pl,*p=tp;
	int data=p->data;//��ǰ������� ���ж����ƾ������Ƿ�������� 
	
	while(p->next!=NULL)//��� 
	{
		p=p->next;
	} 
	//p�������һ���������ƵĽڵ� 
	while(f->next!=NULL)//�ƾ� 
	{
		f=f->next;
	} 
	//f�������һ������ƾ��ƵĽ��
	 
	f->next=(Card*)malloc(sizeof(struct Card));
	f->data=data;
	f=f->next;
	f->next=NULL;
	//����ǰ�Ʒ����ƾ�
	 
	for(;t->next->next!=NULL;t=t->next)//�������һ�ŷ�����ƣ��Ƿ�����ȵ� 
	{
		if(t->data==data)//������ͬ���� ,���Ҳ������ӵ���һ�� 
		{
			f=t;//��¼��㣬������������ 
			for(;t->next!=NULL;t=t->next)
			{
				p->next=(Card*)malloc(sizeof(struct Card));
				p->data=t->data;//�¼�һ���� 
				p=p->next;
				
			}
			p->next=NULL;	//��ĩβ�������� 
			f->next=NULL;//���� 
			return;
		}//���뵽β�� 
	}//���ж��Ƿ�����ͬ�ģ��ٷŵ��ƾ����� 
	return;
}

//չʾ�ƿ� 
bool toplay(Card *pl,Card *&h1,Card *&h2)//pl,p,q
{
	Card *p=h1,*q=h2,*t=pl;
	cout<<endl;
	cout<<"����ƿ⣺"; 
	for(;p->next!=NULL;p=p->next)
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
	
	cout<<"�����"<<h1->data<<"������\n";
	
	add(pl,h1);//���뵽��������,�ж��Ƿ�����ͬ���� 
	h1=h1->next;//����һ�� 
	
	if(isempty(h1))
	{
		cout<<"��һ�ʤ\n";
		return true;
	}
	
	cout<<"�����ƿ⣺"; 
	for(;q->next!=NULL;q=q->next)
	{
		cout<<q->data<<" ";
	}
	cout<<endl;
	
	cout<<"���Գ���"<<h2->data<<"������\n";
	
	add(pl,h2);
	h2=h2->next;
	
	if(isempty(h2))
	{
		cout<<"���Ի�ʤ\n";
		return true;
	}
	cout<<"��ǰ���棺"; 
	for(;t->next!=NULL;t=t->next)
	{
		cout<<t->data<<" ";
	}
	cout<<endl; 
	return false;
}

int main()
{
	//Instructions(); //���� 
	Shuffle(c);   //ϴ�� 
    play= (Card*)malloc(sizeof(struct Card));//���ٽ�� 

	for(p=h1;p->next!=NULL;p=p->next)
	cout<<p->data<<" ";
	cout<<endl; 
	for(q=h2;q->next!=NULL;q=q->next)
	cout<<q->data<<" "; 
	while(true)
	{
		
		if(toplay(play,h1,h2))
		{
			cout<<"��һ�ʤ\n";
			break;
		}
			
	}
	return 0;
}

