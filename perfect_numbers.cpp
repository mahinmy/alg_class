#include<iostream>
#include<cmath>
using namespace std;
int factorSum(int x){
	int i;
	int a;
	int sum=0;
	for(i=1;i<sqrt(x);i++){
		if(x%i==0){
			a=x/i;
			sum+=a+i;
		}
	}
	if(int(sqrt(x))==sqrt(x))
		sum+=sqrt(x);
	return sum;
}
int main()
{
	int a,b;
	cin>>a>>b;
	while(a<b){
		int i;
		int Abundant=0,Perfect=0,Deficient=0;
		for(i=a;i<=b;i++){
			if(factorSum(i)==2*i)
				Perfect+=1;
			else if(factorSum(i)>2*i)
				Abundant+=1;
			else
				Deficient+=1;
		}
		cout<<"Abundant: "<<Abundant<<endl;
		cout<<"Perfect: "<<Perfect<<endl;
		cout<<"Deficient: "<<Deficient<<endl;
		cin>>a>>b;
	}
	return 0;
}