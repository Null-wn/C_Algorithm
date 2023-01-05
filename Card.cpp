#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int c[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,14,14};  //一副完整的牌 ,14大小王 
int player1[27]; 
int player2[27];

struct Card
{
	int data;
	Card *next;
};

Card *h1=NULL,*h2=NULL,*p=NULL,*q=NULL,*play=NULL;//play当前桌面上的牌的指针 

//游戏规则 
void Instructions(){
	char s;
	cout<<"欢迎来到推小车卡牌游戏！"<<endl;
	cout<<"是否查看游戏规则？是（y）否（任意字符）：";
	cin>>s;
	if(s == 'y'){
		cout<<endl;
		cout<<"一副牌总共有54张，洗牌后分为2叠，二人游戏，一名为玩家，一名为计算机。"<<endl;
		cout<<"每次只能出最后的一张牌，率先出完的的玩家失败！"<<endl; 
		cout<<endl;
	}
	else
	    cout<<endl;
}

//洗牌函数，打乱牌的顺序 
void Shuffle(int *c){
	cout<<"洗牌中。。。"<<endl;
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
	
	//发牌， 分为2份，链表存储 
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

void add(Card *pl,Card *tp)//把出的牌放到牌局里面 tp玩家头节点，pl牌局头节点 
{
	Card *t=pl,*f=pl,*p=tp;
	int data=p->data;//当前的玩家牌 ，判断在牌局里面是否有牌相等 
	
	while(p->next!=NULL)//玩家 
	{
		p=p->next;
	} 
	//p到了最后一个存放玩家牌的节点 
	while(f->next!=NULL)//牌局 
	{
		f=f->next;
	} 
	//f到了最后一个存放牌局牌的结点
	 
	f->next=(Card*)malloc(sizeof(struct Card));
	f->data=data;
	f=f->next;
	f->next=NULL;
	//将当前牌放入牌局
	 
	for(;t->next->next!=NULL;t=t->next)//不算最后一张放入的牌，是否有相等的 
	{
		if(t->data==data)//发现相同的牌 ,并且不是最后加的那一个 
		{
			f=t;//记录结点，最后放完了清零 
			for(;t->next!=NULL;t=t->next)
			{
				p->next=(Card*)malloc(sizeof(struct Card));
				p->data=t->data;//新加一张牌 
				p=p->next;
				
			}
			p->next=NULL;	//在末尾加入新牌 
			f->next=NULL;//清零 
			return;
		}//插入到尾部 
	}//先判断是否有相同的，再放到牌局里面 
	return;
}

//展示牌库 
bool toplay(Card *pl,Card *&h1,Card *&h2)//pl,p,q
{
	Card *p=h1,*q=h2,*t=pl;
	cout<<endl;
	cout<<"你的牌库："; 
	for(;p->next!=NULL;p=p->next)
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
	
	cout<<"你出了"<<h1->data<<"这张牌\n";
	
	add(pl,h1);//加入到桌面上面,判断是否有相同的牌 
	h1=h1->next;//出第一张 
	
	if(isempty(h1))
	{
		cout<<"玩家获胜\n";
		return true;
	}
	
	cout<<"电脑牌库："; 
	for(;q->next!=NULL;q=q->next)
	{
		cout<<q->data<<" ";
	}
	cout<<endl;
	
	cout<<"电脑出了"<<h2->data<<"这张牌\n";
	
	add(pl,h2);
	h2=h2->next;
	
	if(isempty(h2))
	{
		cout<<"电脑获胜\n";
		return true;
	}
	cout<<"当前局面："; 
	for(;t->next!=NULL;t=t->next)
	{
		cout<<t->data<<" ";
	}
	cout<<endl; 
	return false;
}

int main()
{
	//Instructions(); //规则 
	Shuffle(c);   //洗牌 
    play= (Card*)malloc(sizeof(struct Card));//开辟结点 

	for(p=h1;p->next!=NULL;p=p->next)
	cout<<p->data<<" ";
	cout<<endl; 
	for(q=h2;q->next!=NULL;q=q->next)
	cout<<q->data<<" "; 
	while(true)
	{
		
		if(toplay(play,h1,h2))
		{
			cout<<"玩家获胜\n";
			break;
		}
			
	}
	return 0;
}

