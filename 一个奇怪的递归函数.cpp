#include<iostream>
using namespace std;

int i=0,j=0;

void dfs(int u);

void tfs(int u)
{
	if(u>3)
	{
		return;
	}
	j++;	
	cout<<"j="<<j<<" "<<"u="<<u<<endl;//1
	dfs(u+1);//2
	cout<<u<<" "<<"x"<<endl;//3
	tfs(u+2);//4
}

void dfs(int u)
{
	if(u>3)
	{
		return;
	}
	i++;	
	cout<<"i="<<i<<" "<<"u="<<u<<endl;//5
	dfs(u+1);//6
	cout<<u<<" "<<"s"<<endl;//7
	tfs(u+2);//8
}

int main()
{
	dfs(0); 
	return 0;
}
