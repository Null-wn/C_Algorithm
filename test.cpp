#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream> 
using namespace std;
void Next(char*T,int *next,int k){
    int i=1;
    next[1]=0;
    int j=0;
    while (i<k) {
        if (j==0||T[i-1]==T[j-1]) {
            i++;
            j++;
            next[i]=j;
        }else{
            j=next[j];
        }
    }
}
bool KMP(char * S,char * T,int l,int k)
{
    int next[10];
    Next(T,next,k);//根据模式串T,初始化next数组
    int i=1;
    int j=1;
    while (i<=l&&j<=k) {
        //j==0:代表模式串的第一个字符就和当前测试的字符不相等；S[i-1]==T[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
        if (j==0 || S[i-1]==T[j-1]) {
            i++;
            j++;
        }
        else{
            j=next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
        }
    }
    if (j>k) {//如果条件为真，说明匹配成功
        return true;
    }
    return false;
}
int main() 
{
	ifstream fin;
	fin.open("病毒感染检测输入数据.txt"); 
	int num;	fin>>num;
	ofstream fout;
	fout.open("病毒感染检测输出数据.txt");
	for(int i=0;i<num;i++)
	{
		char a[1000],b[1000],c[1000]; 
		fin>>a;		strcpy(c,a);	fin>>b;//a模式串病毒，b匹配串人体 
		int n=strlen(a);//a的最后一个元素 
		int l=strlen(b);
		int j;
		for(j=0;j<n-1;j++)
		{
			a[n+j]=a[j];//需要考虑病毒环形的DNA 
		}
		bool t=false;
		
	    for(int i=0;i<=j;i++)
	    {
	    	char c[1000];
	    	int k=0;
	    	for(int j=i;k<n;k++,j++)
	    	{
	    		c[k]=a[j];
			}
			
	    	if(KMP(b,c,l,k))
			{
				t=true;
			}
			//k为c的长度,c为匹配串 
	    
		}
		
    	if(t)
	    {
		    fout<<c<<"		"<<b<<"		"<<"Yes\n";
		}
	    else if(!t)
	    {
	    	fout<<c<<"		"<<b<<"		"<<"No\n";
		}
	  	
	}
	fin.close();
	fout.close();
	return 0;	
}
