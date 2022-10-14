//枚举每一个币，分别假设其为真币和假币
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

string Left[12][3];
string Right[12][3];
string result[12][3];

bool isfeitcoin(int j,char c,bool islight)
{	
	for(int i=0;i<3;i++)
	{
		string l=Left[j][i],r=Right[j][i];
		
		if(!islight)	swap(l,r);
		
			switch(result[j][i][0])
			{
				case 'e':
					if(l.find(c)!=string::npos||r.find(c)!=string::npos)
					{
						return false;
					}
						break;
						
				case 'u'://右端高 
					if(r.find(c)==string::npos)		
					{	
						return false;
					}
						break;			
				
				case 'd'://左端高 
					if(l.find(c)==string::npos)
					{	
						return false;
					}
						break;
								
			}
	}
	return true;
}

int main()
{
	
	int t,j,i;
	cin>>t;
	for(j=0;j<t;j++)
	{
		for(i=0;i<3;i++)		
		{
			cin>>Left[j][i]>>Right[j][i]>>result[j][i];
		}
	}
	for(j=0;j<t;j++)
	{
		int ok=0;
		for(i=0;i<3;i++)
		{
			if(ok==1)
			break;
			for(char icoin='A';icoin<='L';icoin++)
			{
			if(isfeitcoin(j,icoin,true))//假设轻假币
			{
				cout<<icoin<<" is the counterfeit coin and it is light.\n";
				ok=1;
				break;
			}
			else if(isfeitcoin(j,icoin,false))//假设重假币
			{
				cout<<icoin<<" is the counterfeit coin and it is heavy.\n";
				ok=1;
				break;
			}
			}
		}
	}
}