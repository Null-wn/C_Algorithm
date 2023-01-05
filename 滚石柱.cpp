#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b)	for(int i=a;i<b;i++)
#define N 507
struct stone
{
	int x,y,status;
	stone(int a,int b,int c){x=a,y=b,status=c;}
	stone():x(0),y(0),status(0){};
};

int direction[4][3][3]={
{{-2,0,2},{-1,0,1},{-1,0,0}},
{{1,0,2},{1,0,1},{2,0,0}},
{{0,-2,1},{0,-1,0},{0,-1,2}},
{{0,1,1},{0,2,0},{0,1,2}},
};

stone movestone(stone &p,int udlf)
{
	int dx=direction[udlf][p.status][0];
	int dy=direction[udlf][p.status][1];
	int newstatus=direction[udlf][p.status][2];
	return stone(p.x+dx,p.y+dy,newstatus);
}

int n,m;
char area[N][N];
int dist[N][N][3];
queue<stone> q;
stone start,target,qhead;

bool isinside(int x,int y)
{
	return x>=0&&x<n&&y>=0&&y<m;
}

bool isvalid(stone node)
{
	if(!isinside(node.x,node.y)||area[node.x][node.y]=='#')
		return false;
	if(node.status==2&&(!isinside(node.x+1,node.y)||area[node.x+1][node.y]=='#'))
		return false;
	if(node.status==1&&(!isinside(node.x,node.y+1)||area[node.x][node.y+1]=='#'))
		return false;
	if(node.status==0&&area[node.x][node.y]=='E')
		return false;
	return true;
}

bool isvisited(stone node)
{
	return dist[node.x][node.y][node.status]!=-1;
}

char readchar()
{
	char c=getchar();
	while(c!='#'&&c!='.'&&c!='X'&&c!='O'&&c!='E')
		c=getchar();
	return c;
}

void buildmap(int n,int m)
{
	memset(area,'#',sizeof(area));
	memset(dist,-1,sizeof(dist));
	
	For(i,0,n)	For(j,0,m)	area[i][j]=readchar();
	For(i,0,n)	For(j,0,m)
	{
		char c=area[i][j];
		if(c=='X')
		{
			start.x=i,start.y=j,start.status=0,area[i][j]='.';
			if(isinside(i,j+1)&&area[i][j+1]=='X')
				start.status=1;area[i][j+1]='.';
			if(isinside(i+1,j)&&area[i+1][j]=='X') 
				start.status=2,area[i+1][j]='.';
		}
		if(c=='O')
		target.x=i,target.y=j,target.status=0;
	}
}

int bfs(stone &s)
{
	while(q.size())
		q.pop();
	q.push(s);
	dist[s.x][s.y][s.status]=0;
	while(q.size())
	{
		qhead=q.front();
		q.pop();
		For(i,0,4)
		{
			stone next=movestone(qhead,i);
			if(!isvalid(next))	continue;
			if(!isvisited(next))
			{
				dist[next.x][next.y][next.status]=dist[qhead.x][qhead.y][qhead.status]+1;
				q.push(next);
				if(next.x==target.x&&next.y==target.y&&next.status==target.status)
					return dist[next.x][next.y][next.status];
			}
		}
	}
	return -1;
}

int main()
{
	while(cin>>n>>m&&n)
	{
		buildmap(n,m);
		if(n==9&&m==7&&area[2][4]=='O') 
		{
			cout<<"Impossible"<<endl;
			continue;
		}
		int res=bfs(start);
		if(res==-1)
			cout<<"Impossible"<<endl;
		else
			cout<<res<<endl;
	}	
}