#include<iostream>
#include<fstream> 
#include<string.h>
#define inf 99999
using namespace std;

typedef struct
{
	char name[100];//地点名字 
}VertexType; //顶点结构

typedef struct
{ 
	VertexType vexs[20];//最多20个地点 
	int arcs[20][20];//邻接矩阵
	int vexnum,arcnum;//vex顶点个数，arc边的个数
}MGraph; //图结构

MGraph mg;//实例化图
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
	//初始化结束,求最短路径，并加入S集
	for (int i = 1; i < mg.vexnum; i++)
	{
		int min = inf;
		int temp;
		for (int w = 0; w < mg.vexnum; w++)
			if (!S[w] && D[w] < min) //某点temp未加入s集，且为当前最短路径
			{
				temp = w;
				min = D[w];
			}
		S[temp] = true;
	//更新从源点出发至其余点的最短路径 通过temp
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
	cout << "目标点" << "\t" << "最短路径值" << "\t" << "最短路径" << endl;
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
		if(line[0]=='#')//读到第一个'###' 
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
		mg.vexnum++;//顶点数++ 
	}
	//cout<<mg.vexnum<<"个地点"<<endl; 
	
	while(true)
	{
		fin.getline(line,1000);
		if(line[0]=='#')//读到第二个'###'，地点录入完毕 
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
		for(int j=0;j<mg.vexnum;j++)//匹配name1,name2，写入distance 
		{
			if(strcmp(name1,mg.vexs[j].name)==0)
			{
				m=j;
				ok=true;
				break;
			}
		}
		//ok=false,没有找到这样的地点
		 
		ok=false;
		for(int j=0;j<mg.vexnum;j++)//匹配name1,name2，写入distance 
		{
			if(strcmp(name2,mg.vexs[j].name)==0)
			{
				n=j;
				ok=true;
				break;
			}
		}
		mg.arcs[m][n]=distance;//存入邻接矩阵 
		mg.arcs[n][m]=distance;//无向图 
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
	}//初始化矩阵 
	cout<<"欢迎来到厦门大学\n";
	cout<<"1,查询景点信息\n";
	cout<<"2,问路查询\n";
	cout<<"3,增加一个景点及其相关信息\n";
	cout<<"4,修改一个景点及其相关信息\n";
	cout<<"5,增加一条新的路径\n";
	cout<<"6,退出\n";
	update();
}

void query()
{
	cout<<"地点有\n";
	for(int i=0;i<mg.vexnum;i++)
	{
		cout<<mg.vexs[i].name<<endl;	
	} 
	char line[1000];
	ifstream fin;
	fin.open("graph.txt"); 
	int select=0;
	cout<<"请输入你要查询的地点\n";
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
		cout<<"输入错误\n";
	}
}

void askfor()
{
	int m,n;
	char begin[100],end[100]; 
	bool ok=false;
	
	cout<<"请输入起点\n";
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
		cout<<"起点不存在\n";
		return;
	}
	
	
	ok=false;
	cout<<"请输入终点\n";
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
		cout<<"终点不存在\n";
		return;
	}
	
	Todijkstra(m,n);//找出从m到n最短路径
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
	cout<<"请输入你增加的地点名字\n";
	cin>>name;
	cout<<"请输入地点简介\n";
	cin>>information;
	//输出文件 
	bool ok=false;
	for(int i=0;i<mg.vexnum;i++)
	{
		if(strcmp(name,mg.vexs[i].name))
		ok=true;
	}//查重
	if(!ok)
	{
		cout<<name<<' '<<information; 
		for(int i=0;i<mg.arcnum+2;i++)
		{
			fin.getline(line,1000);
			cout<<line;
		} 
		fin.close();	//fout.close();
		update();//更新数据 
	} 
	else
	{
		cout<<"输入地点重复，请重新输入\n";
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
	cout<<"输入你要修改的地点\n";
	cin>>select;
	cout<<"输入你要修改的简介\n";
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
			fin.getline(line,1000);// 找到对应的行开始修改 
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
	else//不存在这个地点 
	{
		cout<<"输入错误\n";
	}
}

void addpath()
{
	char begin[100],end[100];	int distance,m,n;
	cout<<"请输入起点\n";
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
		cout<<"起点不存在\n";
		return;
	}
	
	
	ok=false;
	cout<<"请输入终点\n";
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
		cout<<"终点不存在\n";
		return;
	}
	
	cout<<"请输入距离\n";
	cin>>distance;
	
	//写入文件
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
				query();//更新地点数量 
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
       			cout<<"输入错误，请重新输入\n";
   		}
	}
		
	return 0; 
} 
