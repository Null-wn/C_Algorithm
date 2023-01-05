include<iostream>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;

int main()
{
	string line;
	bitset<32> lock;
	int mintimes=99999999;//无穷大 
	
	cin>>line;
	bitset<32> sourcelock(line);
	cin>>line;
	bitset<32> targetlock(line);
	
	int n=line.size();
	for(int p=0;p<2;++p)
	{
		lock=sourcelock;
		int times=0;
		int nextbutton=p;
		
		for(int i=0;i<n;++i)
		{
			if(nextbutton==1)
			{
				++times;
				if(i>0)
					lock.flip(i-1);
				lock.flip(i);
				if(i<n-1)
				lock.flip(i+1);
			}
			
			if(lock[i]!=targetlock[i])
				nextbutton=1;
			else
				nextbutton=0;
			if(lock==targetlock)		
			{
				mintimes=min(mintimes,times);
			}
		}
	}
		
	if(mintimes==99999999)
	{
		cout<<"impossible\n";
	}
	
	else
	{
		cout<<mintimes<<endl;
	}
}