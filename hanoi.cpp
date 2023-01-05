//只有两个盘子时，1号1移动到2，2号2移动到3，1号1移动到3
#include<iostream>
using namespace std;
int main()
{
	void hanoi(int n, int id, char one, char two, char three);
	int m;		char a,b,c;
	cin>>m; 
	cin>>a>>b>>c;
	hanoi(m, 1, a,b,c);
}
void hanoi(int n, int id, char one, char two, char three)
{
	void move(int id, char x, char y);
	if (n == 1)
		move(id, one, three);
	else
	{
		hanoi(n - 1, id, one, three, two);
		int newid=id+n-1;//下一个盘子
		move(newid, one, three);
		hanoi(n - 1, id, two, one, three);
		return;
	}
}
void move(int id, char x, char y)
{
	cout<<id<<":"<<x<<"->"<<y<<endl;
}