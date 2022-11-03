#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

char time[5];//存储当前时间
char beg[5];
//转换时间 ，格式10:10 
int covert1(char s[5])//转换小时 
{
	return (s[0]-'0')*10+s[1]-'0';
}

int covert2(char s[5])//转换分钟 
{
	return (s[3]-'0')*10+s[4]-'0';
}

bool after(char t[5],char time[5])//更新当前时间 
{
	int h1,h2,m1,m2;
	h1=covert1(t);
	h2=covert1(time);
	m1=covert2(t);
	m2=covert2(time);
	if(h1>h2||(h1==h2&&m1>=m2))
	{
		strcpy(time,t); 
		return true;
	}
	return false;
}

struct Car
{
	char t[5];//进入时间 
	int sign;//车牌号
	Car *next;
};

struct Lane
{
	Car *head;
	Car *tail;
	
	Lane()
	{
		head=(Car*)malloc(sizeof(Car));
		tail=head->next;
	}
	
	bool empty()
	{
		return head==tail?true:false;
	}
	
	void push(int tsign)//队尾入 
	{
		tail=(Car*)malloc(sizeof(Car));
		tail->sign=tsign;
		//在便道停车，不算收费时间 
		tail=tail->next;
		tail=NULL;//位置加一 
	}
	
	Car* pop()//队头出 
	{
		Car *p=head;
		head=head->next;
		return p;
	}
	
};

const int size=5;
struct Carpark
{
	int presize;//当前占用的位置个数 
	Car *head,*p;//头结点 
	Car *tail; 
	
	void begin()
	{
		presize=0;
		head=p=(Car*)malloc(sizeof(Car));
		tail=NULL;
		p->next=tail;
	}
	
	bool push(Lane lane)//队尾入 
	{
		char ttime[5];		int tsign;	
		while(true)	
		{
			cout<<"请依次输入时间和车牌号\n";	cin>>ttime>>tsign;
			if(after(ttime,time))
			{
				if(presize+1<=size)
				{
					
					while(p->next!=tail)
					{
						p=p->next;
					}
					
					p->next=(Car*)malloc(sizeof(Car));
					
					p->sign=tsign;
					strcpy(p->t,ttime);
					cout<<p->sign<<" "<<p->t;
					p=p->next;
					tail=NULL;
					p->next=tail;
					presize++;
					
					return true;
				}
				
				else
				{
					cout<<"停车厂满了，暂时停在便道\n";
					lane.push(tsign);
					return false;
				}
				
			}
			
			else
			{
				cout<<"时间错误，当前时间为"<<time<<"请重新输入\n"<<endl;
			}
		}
		
			
	}
	
	int cost(Car *q)
	{
		//每小时10元，不足一个小时不收费 
		int c=0,t1=0,t2=0;
		for(int i=0;;)
		{
			t1+=q->t[i]-'0';	t2+=time[i]-'0';
			i++;
			if(i==1)
			break; 
			t1*=10;
			t2*=10;
		}
		return (t2-t1)*10;
	}
	
	bool del(int tsign,Lane lane)//队尾出 
	{
		char ttime[5];
		cout<<"请输入当前时间\n";
		cin>>ttime;
		if(after(ttime,time))
		{	
			Car *p=head,*q=head->next;
			while(true)
			{
				if(q==tail)
				break;	
				if(q->sign==tsign)
				{
					p->next=p->next->next;
					cout<<"成功开走"<<q->sign<<"\t进入时间"<<q->t<<"\t离开时间"<<ttime<<"\t收费"<<cost(q)<<"\n"; 
					free(q);//删除q 
					presize--;
					if(!lane.empty())//便道上面有车
					{
						Car *p=lane.pop();//把便道上面的车开进来 
						tail=(Car*)malloc(sizeof(Car));
						tail->sign=p->sign;
						strcpy(tail->t,time);
						tail=tail->next;
						tail=NULL;
						presize++;
					} 
					return true;
				}
				q=p->next;
				p=q;//指向下一个 
				if(q->next==tail)
				{
					break;
				}
			
			}
			
			cout<<"找不到这辆车\n";
			return false;
			
		}
		else
		{
			cout<<"时间错误，现在已经"<<time<<"了\n";
			return false;
		}
	}
	
	bool fd(int tsign)
	{
		Car *p=head;
		while(p->next!=tail)
		{
			if(p->sign==tsign)
			{
				strcpy(beg,p->t);
				return true;
			}
			p=p->next;
		}
		return false;
	} 
	
	void print()
	{
		cout<<"共有"<<presize<<"辆车\n";
		p=head;
		for(int i=1;p->next!=tail;i++)
		{
			cout<<"第"<<i<<"辆车:	"<<"车牌号"<<p->sign<<"	"<<"开始时间:	"<<p->t<<endl;
			p=p->next;
		}
	}
	
	int findempty()
	{
		return size-presize;
	}
};

int main()
{
	Lane lane;
	Carpark carpark;
	int select;
	carpark.begin();
	while(true)
	{	
		cout<<"请输入功能选择\n1车辆进入\n2车辆离开\n3查询车辆信息\n4车辆列表\n5空停车位查询\n6退出系统\n";
		cin>>select;
		if(select==1)
		{
			if(carpark.push(lane))
			cout<<"进入成功，当前位置已占"<<carpark.presize<<endl;
			else
			cout<<"进入失败，位置已经满了\n";
		}
		
		else if(select==2)
		{
			int tsign;
			cout<<"输入车辆号码\n";
			cin>>tsign;
			if(carpark.del(tsign,lane))
			cout<<"离开成功\n";
		}
		
		else if(select==3)
		{
			int tsign;
			cout<<"请输入车牌号\n";	cin>>tsign;
			if(carpark.fd(tsign))
			{
				cout<<"开始停车时间"<<beg<<"	当前时间"<<time<<endl;
			}
			else
			{
				cout<<"在停车场没有找到这辆车\n"; 
			}
			
		}
		
		else if(select==4)
		{
			cout<<"车辆列表信息\n";
			carpark.print();
		}
		
		else if(select==5)
		{
			cout<<"还有"<<carpark.findempty()<<"个空位"<<endl;
		}
		
		else if(select==6)
		{
			break;
		}
		
		else
		{
			cout<<"输入错误，请重新输入\n";
		}
			
	
	} 

} 

