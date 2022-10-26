#include<iostream>
using namespace std;
#define maxn 1001
int d[maxn][maxn];
int volumn[maxn],weight[maxn];

int main()
{
	int n,m;
	cin>>n>>m;
	int *dp=d[0];
	for(int i=1;i<=n;i++)
	{
		cin>>volumn[i]>>weight[i];
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=volumn[i];j--)
		{
			dp[j]=max(dp[j],dp[j-volumn[i]]+weight[i]);
		}
	}
	cout<<dp[m]<<endl;
}