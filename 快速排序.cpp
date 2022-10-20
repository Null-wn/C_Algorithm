#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

long long *numbers;
void quicksort(long long nums[],int left,int right)
{
	if(left>=right)
	return;
	long long target=nums[left];
	int i=left-1,j=right+1;
	while(i<j)
	{
		do
			i++;
		while(nums[i]<target);
		do
			j--;
		while(nums[j]>target);
		if(i<j)
		swap(nums[i],nums[j]);
	}
	quicksort(nums,left,j);
	quicksort(nums,j+1,right);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	numbers=new long long [n];
	for(int i=0;i<n;i++)
	{
		cin>>numbers[i];
	}
	quicksort(numbers,0,n-1);
	for(int i=0;i<n;i++)
	{
		cout<<numbers[i]<<" ";
	}
	delete numbers;
	return 0;
}