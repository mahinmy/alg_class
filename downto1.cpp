#include<iostream>
using namespace std;
int f(int x){
	if(x%3==0)
		return x/3;
	else
		return x-1;
}
int main()
{
	int a;
	cin>>a;
	int count;
	while(a!=0){
		count=0;
		if(a==1)
			cout<<0<<endl;
		else{
			while(f(a)!=1){
				a=f(a);
				count+=1;
			}
			count+=1;
			cout<<count<<endl;
		}
		cin>>a;
	}
	return 0;
}