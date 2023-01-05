#include<iostream>
#include<fstream> 
#include<string.h>
#define inf 99999
using namespace std;

typedef struct
{
	char name[100];//�ص����� 
}VertexType; //����ṹ

typedef struct
{ 
	VertexType vexs[20];//���20���ص� 
	int arcs[20][20];//�ڽӾ���
	int vexnum,arcnum;//vex���������arc�ߵĸ���
}MGraph; //ͼ�ṹ

MGraph mg;//ʵ����ͼ
bool S[20];
int D[20];
int Pr[20];
int total;

void Path(int m)
{
	if (Pr[m] == -1)
	{
		return;
	}
		
	Path(Pr[m]);
	cout << mg.vexs[Pr[m]].name<<"->";
}

void Dijkstra(int m,int n)
{
	
	for (int i = 0; i < mg.vexnum; i++)
	{
		S[i] = false;
		D[i] = mg.arcs[m][i];
		if (D[i] < inf)
			Pr[i] = m;
		else Pr[i] = -1;
	}
	S[m] = true;
	D[m] = 0;
	//��ʼ������,�����·����������S��
	for (int i = 1; i < mg.vexnum; i++)
	{
		int min = inf;
		int temp;
		for (int w = 0; w < mg.vexnum; w++)
			if (!S[w] && D[w] < min) //ĳ��tempδ����s������Ϊ��ǰ���·��
			{
				temp = w;
				min = D[w];
			}
		S[temp] = true;
	//���´�Դ����������������·�� ͨ��temp
		for (int w = 0; w < mg.vexnum; w++)
			if (!S[w] && D[temp] + mg.arcs[temp][w] < D[w])
			{
				D[w] = D[temp] + mg.arcs[temp][w];
				Pr[w] = temp;
			}
	}
}

void Todijkstra(int m,int n)
{
	total=0;
	Dijkstra(m,n);
	cout << "Ŀ���" << "\t" << "���·��ֵ" << "\t" << "���·��" << endl;
	for (int i = 0; i < mg.vexnum; i++)
	{
		if (i==n)
		{
			cout << "  "<<mg.vexs[i].name<< "\t" <<"        "<< D[i] << "\t";
			Path(i);
			cout<<mg.vexs[i].name<<endl;
		}
	}
}

void update()
{
	char line[1000];
	ifstream fin;
	fin.open("graph.txt"); 
	
	int num=0;
	while(true)
	{
		fin.getline(line,1000);
		if(line[0]=='#')//������һ��'###' 
		{
			break;
		}
		
		for(int i=0;i<strlen(line);i++)
		{
			if(line[i]==' ')
			{
				break;
			}
			mg.vexs[mg.vexnum].name[i]=line[i];
		}
		//cout<<mg.vexs[mg.vexnum].name<<endl;
		mg.vexnum++;//������++ 
	}
	//cout<<mg.vexnum<<"���ص�"<<endl; 
	
	while(true)
	{
		fin.getline(line,1000);
		if(line[0]=='#')//�����ڶ���'###'���ص�¼����� 
		{
			break;
		}
		
		char name1[100],name2[100];		bool second=false;		int distance;
		for(int i=0;i<100;i++)
		{
			name1[i]='\0';
		}
		for(int i=0;i<100;i++)
		{
			name2[i]='\0';
		}
		
		for(int i=0,j=0;i<strlen(line);i++)
		{
			distance=0;
			if(line[i]==' '&&second==false)
			{
				second=true;
				continue;
			}
			
			if(!second)
			{
				name1[i]=line[i];
			}
			
			if(second)
			{
				if(line[i]==' ')
				{
					while(true)
					{
						i++;
						if(line[i]>='0'&&line[i]<='9')
						{
							distance*=10;
							distance+=line[i]-'0';
						}
						else
						{
							break;
						}
					}
					break;
				}
				
				
				else
				{
					name2[j]=line[i];
					j++;
				}
			}
			
		}
		//cout<<name1<<"	"<<name2<<"		"<<distance<<endl; 
		int m,n;
		bool ok=false;
		for(int j=0;j<mg.vexnum;j++)//ƥ��name1,name2��д��distance 
		{
			if(strcmp(name1,mg.vexs[j].name)==0)
			{
				m=j;
				ok=true;
				break;
			}
		}
		//ok=false,û���ҵ������ĵص�
		 
		ok=false;
		for(int j=0;j<mg.vexnum;j++)//ƥ��name1,name2��д��distance 
		{
			if(strcmp(name2,mg.vexs[j].name)==0)
			{
				n=j;
				ok=true;
				break;
			}
		}
		mg.arcs[m][n]=distance;//�����ڽӾ��� 
		mg.arcs[n][m]=distance;//����ͼ 
		mg.arcnum++;
		//cout<<m<<" "<<n<<endl;
		
		for(int i=0;i<100;i++)
		{
			name1[i]='\0';
		}
		for(int i=0;i<100;i++)
		{
			name2[i]='\0';
		}
		
	}
}

void begin()
{
	mg.vexnum=0;	mg.arcnum=0;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			mg.arcs[i][j]=inf;
		}
	}//��ʼ������ 
	cout<<"��ӭ�������Ŵ�ѧ\n";
	cout<<"1,��ѯ������Ϣ\n";
	cout<<"2,��·��ѯ\n";
	cout<<"3,����һ�����㼰�������Ϣ\n";
	cout<<"4,�޸�һ�����㼰�������Ϣ\n";
	cout<<"5,����һ���µ�·��\n";
	cout<<"6,�˳�\n";
	update();
}

void query()
{
	cout<<"�ص���\n";
	for(int i=0;i<mg.vexnum;i++)
	{
		cout<<mg.vexs[i].name<<endl;	
	} 
	char line[1000];
	ifstream fin;
	fin.open("graph.txt"); 
	int select=0;
	cout<<"��������Ҫ��ѯ�ĵص�\n";
	cin>>select;
	if(select>0&&select<=mg.vexnum)
	{
		for(int i=0;i<select;i++) 
		{
			fin.getline(line,1000);
		}
		cout<<line<<endl;
	}
	else
	{
		cout<<"�������\n";
	}
}

void askfor()
{
	int m,n;
	char begin[100],end[100]; 
	bool ok=false;
	
	cout<<"���������\n";
	cin>>begin;
	for(int i=0;i<mg.vexnum;i++)
	{
		if(strcmp(begin,mg.vexs[i].name)==0)
		{
			ok=true;
			m=i;
		}	
	}
	if(!ok)
	{
		cout<<"��㲻����\n";
		return;
	}
	
	
	ok=false;
	cout<<"�������յ�\n";
	cin>>end;
	for(int i=0;i<mg.vexnum;i++)
	{
		if(strcmp(end,mg.vexs[i].name)==0)
		{
			ok=true; 
			n=i;
		}		
	}
	if(!ok)
	{
		cout<<"�յ㲻����\n";
		return;
	}
	
	Todijkstra(m,n);//�ҳ���m��n���·��
}

void addpoint()
{
	char information[1000];		char line[1000];		char name[100];
	ifstream fin;
	ofstream fout;
	fin.open("graph.txt"); 
	fout.open("graph.txt");
	for(int i=0;i<mg.vexnum;i++)
	{
		fin.getline(line,1000);
		cout<<line;
	} 
	fin.getline(line,1000);
	cout<<line;
	cout<<"�����������ӵĵص�����\n";
	cin>>name;
	cout<<"������ص���\n";
	cin>>information;
	//����ļ� 
	bool ok=false;
	for(int i=0;i<mg.vexnum;i++)
	{
		if(strcmp(name,mg.vexs[i].name))
		ok=true;
	}//����
	if(!ok)
	{
		cout<<name<<' '<<information; 
		for(int i=0;i<mg.arcnum+2;i++)
		{
			fin.getline(line,1000);
			cout<<line;
		} 
		fin.close();	//fout.close();
		update();//�������� 
	} 
	else
	{
		cout<<"����ص��ظ�������������\n";
		return;
	}
}

void modify()
{
	int select;	int i=1; char introduce[1000]; 
	for(int i=0;i<mg.vexnum;i++)
	{
		cout<<i<<mg.vexs[i].name<<endl;	
	}
	cout<<"������Ҫ�޸ĵĵص�\n";
	cin>>select;
	cout<<"������Ҫ�޸ĵļ��\n";
	cin>>introduce;
	char line[1000],name[100];
	ifstream fin;
	ofstream fout;
	fin.open("graph.txt"); 
	fout.open("graph.txt");
	if(select>0&&select<=mg.vexnum)
	{
		for(int i=0;i<select;i++) 
		{
			fin.getline(line,1000);// �ҵ���Ӧ���п�ʼ�޸� 
			for(int i=0;i<strlen(line);i++)
			{
				if(line[i]==' ')
				{
					break;
				}
				name[i]=line[i];
			}
			if(strcmp(mg.vexs[select].name,name)==0)
			{
				fout<<introduce<<endl;
			}
		}
		update();
	}
	else//����������ص� 
	{
		cout<<"�������\n";
	}
}

void addpath()
{
	char begin[100],end[100];	int distance,m,n;
	cout<<"���������\n";
	cin>>begin;
	bool ok=false;
	for(int i=0;i<mg.vexnum;i++)
	{
		if(strcmp(begin,mg.vexs[i].name)==0)
		{
			ok=true;
			m=i;
		}	
	}
	if(!ok)
	{
		cout<<"��㲻����\n";
		return;
	}
	
	
	ok=false;
	cout<<"�������յ�\n";
	cin>>end;
	for(int i=0;i<mg.vexnum;i++)
	{
		if(strcmp(end,mg.vexs[i].name)==0)
		{
			ok=true; 
			n=i;
		}		
	}
	if(!ok)
	{
		cout<<"�յ㲻����\n";
		return;
	}
	
	cout<<"���������\n";
	cin>>distance;
	
	//д���ļ�
	char line[1000];
	ifstream fin;
	ofstream fout;
	for(int i=0;i<mg.vexnum;i++)
	{
		fin.getline(line,1000);
	}
	fout<<begin<<' '<<end<<' '<<distance<<endl;
	update();
}

int main()
{
	begin();
	int select=0,num=0;	bool out=false;
	
	while(!out)
	{
		cin>>select;
		switch(select)
		{
			case 1:
				query();//���µص����� 
	   			break;
			case 2:
	   			askfor();
	   			break;
	   		case 3:
	   			addpoint();
	   			break;
	   		case 4:
	   			modify();
	   			break;
	   		case 5:
	   			addpath();
	   			break;
	   		case 6:
	   			out=true;
	   			break;
    		default:
       			cout<<"�����������������\n";
   		}
	}
		
	return 0; 
} 
