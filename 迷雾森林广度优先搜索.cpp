#include<iostream>
using namespace std;
int w,h;
char fogforest[27][27];
int res=0;

int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};

int dfs(int i,int j)
{
	int res=1;
	fogforest[i][j]='#';
	for(int k=0;k<4;k++)
	{
		int x=i+dx[k],y=j+dy[k];
		if(x>=0&&y>=0&&x<h&&y<w&&fogforest[x][y]=='.')
		res+=dfs(x,y);
	}
	return res;
}

int main()
{
	while(cin>>w>>h,w||h)
	{
		int startx,starty;
		for(int i=0;i<h;i++)
		{
			for(int j=0;j<w;j++)
			{
				cin>>fogforest[i][j];
				if(fogforest[i][j]=='@')
				{
					startx=i;
					starty=j;
				}
			}
		}
		cout<<dfs(startx,starty)<<endl;
	}
}