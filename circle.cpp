#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int r;
	cin>>r;
	int i,j;
	int count=0;
	for(i=-r;i<=r;i++)
		for(j=-r;j<=r;j++){
			if(i*i+j*j<=r*r)
				count+=1;
		}
	cout<<count;
	return 0;
}