#include<iostream>
#include<string>
using namespace std;
bool judge(int i,string s){
	int flag1=0,flag2=i-1,n=s.length();
	string sub=s.substr(flag1,i);
	if(n%i!=0) return false;
	while(flag2!=n-1){
		if(sub!=s.substr(flag1+i,i)) return false;
		flag1+=i;
		flag2+=i;
	}
	return true;
}
int main(){
	string S;
	cin>>S;
	int n=S.length();
	for(int i=1;i<=n;i++){
		if(n%i==0){
			if(judge(i,S)){
				cout<<i<<endl;
				cout<<S.substr(0,i);
				break;
			}
		}
	}
    return 0;
}
