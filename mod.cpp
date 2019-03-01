#include<iostream>
using namespace std;
int main()
{
	int a,x,b;
	cin>>a>>x>>b;
	int result=1,tmp=a;
	while(x!=0){
		if(x%2!=0)
			result=result*tmp%b;
		tmp=(tmp*tmp)%b; 
		x=x/2;
	}
	cout<<result;
	return 0;
}