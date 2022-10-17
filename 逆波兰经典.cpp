#include <iostream>

using namespace std;

double poland() 
{
	char str[32];
	cin>>str;
	switch(str[0])
	{
		case'+':
			return poland()+poland();
			break;
		case'-':
			return poland()-poland();
			break;
		case'*':
			return poland()*poland();
			break;
		case'/':
			return poland()/poland();
		default:
			return atof(str);
		break;
	}
}
int main()
{
	printf("%lf",poland());
}
