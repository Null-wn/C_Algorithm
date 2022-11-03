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
    Next(T,next,k);//����ģʽ��T,��ʼ��next����
    int i=1;
    int j=1;
    while (i<=l&&j<=k) {
        //j==0:����ģʽ���ĵ�һ���ַ��ͺ͵�ǰ���Ե��ַ�����ȣ�S[i-1]==T[j-1],�����Ӧλ���ַ���ȣ���������£�ָ��ǰ���Ե�����ָ���±�i��j�������
        if (j==0 || S[i-1]==T[j-1]) {
            i++;
            j++;
        }
        else{
            j=next[j];//������Ե������ַ�����ȣ�i������j��Ϊ��ǰ�����ַ�����nextֵ
        }
    }
    if (j>k) {//�������Ϊ�棬˵��ƥ��ɹ�
        return true;
    }
    return false;
}
int main() 
{
	ifstream fin;
	fin.open("������Ⱦ�����������.txt"); 
	int num;	fin>>num;
	ofstream fout;
	fout.open("������Ⱦ����������.txt");
	for(int i=0;i<num;i++)
	{
		char a[1000],b[1000],c[1000]; 
		fin>>a;		strcpy(c,a);	fin>>b;//aģʽ��������bƥ�䴮���� 
		int n=strlen(a);//a�����һ��Ԫ�� 
		int l=strlen(b);
		int j;
		for(j=0;j<n-1;j++)
		{
			a[n+j]=a[j];//��Ҫ���ǲ������ε�DNA 
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
			//kΪc�ĳ���,cΪƥ�䴮 
	    
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
