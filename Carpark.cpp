#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

char time[5];//�洢��ǰʱ��
char beg[5];
//ת��ʱ�� ����ʽ10:10 
int covert1(char s[5])//ת��Сʱ 
{
	return (s[0]-'0')*10+s[1]-'0';
}

int covert2(char s[5])//ת������ 
{
	return (s[3]-'0')*10+s[4]-'0';
}

bool after(char t[5],char time[5])//���µ�ǰʱ�� 
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
	char t[5];//����ʱ�� 
	int sign;//���ƺ�
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
	
	void push(int tsign)//��β�� 
	{
		tail=(Car*)malloc(sizeof(Car));
		tail->sign=tsign;
		//�ڱ��ͣ���������շ�ʱ�� 
		tail=tail->next;
		tail=NULL;//λ�ü�һ 
	}
	
	Car* pop()//��ͷ�� 
	{
		Car *p=head;
		head=head->next;
		return p;
	}
	
};

const int size=5;
struct Carpark
{
	int presize;//��ǰռ�õ�λ�ø��� 
	Car *head,*p;//ͷ��� 
	Car *tail; 
	
	void begin()
	{
		presize=0;
		head=p=(Car*)malloc(sizeof(Car));
		tail=NULL;
		p->next=tail;
	}
	
	bool push(Lane lane)//��β�� 
	{
		char ttime[5];		int tsign;	
		while(true)	
		{
			cout<<"����������ʱ��ͳ��ƺ�\n";	cin>>ttime>>tsign;
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
					cout<<"ͣ�������ˣ���ʱͣ�ڱ��\n";
					lane.push(tsign);
					return false;
				}
				
			}
			
			else
			{
				cout<<"ʱ����󣬵�ǰʱ��Ϊ"<<time<<"����������\n"<<endl;
			}
		}
		
			
	}
	
	int cost(Car *q)
	{
		//ÿСʱ10Ԫ������һ��Сʱ���շ� 
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
	
	bool del(int tsign,Lane lane)//��β�� 
	{
		char ttime[5];
		cout<<"�����뵱ǰʱ��\n";
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
					cout<<"�ɹ�����"<<q->sign<<"\t����ʱ��"<<q->t<<"\t�뿪ʱ��"<<ttime<<"\t�շ�"<<cost(q)<<"\n"; 
					free(q);//ɾ��q 
					presize--;
					if(!lane.empty())//��������г�
					{
						Car *p=lane.pop();//�ѱ������ĳ������� 
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
				p=q;//ָ����һ�� 
				if(q->next==tail)
				{
					break;
				}
			
			}
			
			cout<<"�Ҳ���������\n";
			return false;
			
		}
		else
		{
			cout<<"ʱ����������Ѿ�"<<time<<"��\n";
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
		cout<<"����"<<presize<<"����\n";
		p=head;
		for(int i=1;p->next!=tail;i++)
		{
			cout<<"��"<<i<<"����:	"<<"���ƺ�"<<p->sign<<"	"<<"��ʼʱ��:	"<<p->t<<endl;
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
		cout<<"�����빦��ѡ��\n1��������\n2�����뿪\n3��ѯ������Ϣ\n4�����б�\n5��ͣ��λ��ѯ\n6�˳�ϵͳ\n";
		cin>>select;
		if(select==1)
		{
			if(carpark.push(lane))
			cout<<"����ɹ�����ǰλ����ռ"<<carpark.presize<<endl;
			else
			cout<<"����ʧ�ܣ�λ���Ѿ�����\n";
		}
		
		else if(select==2)
		{
			int tsign;
			cout<<"���복������\n";
			cin>>tsign;
			if(carpark.del(tsign,lane))
			cout<<"�뿪�ɹ�\n";
		}
		
		else if(select==3)
		{
			int tsign;
			cout<<"�����복�ƺ�\n";	cin>>tsign;
			if(carpark.fd(tsign))
			{
				cout<<"��ʼͣ��ʱ��"<<beg<<"	��ǰʱ��"<<time<<endl;
			}
			else
			{
				cout<<"��ͣ����û���ҵ�������\n"; 
			}
			
		}
		
		else if(select==4)
		{
			cout<<"�����б���Ϣ\n";
			carpark.print();
		}
		
		else if(select==5)
		{
			cout<<"����"<<carpark.findempty()<<"����λ"<<endl;
		}
		
		else if(select==6)
		{
			break;
		}
		
		else
		{
			cout<<"�����������������\n";
		}
			
	
	} 

} 

