#include<iostream>
#include<string>
using namespace std;
bool mid1(int flag,string s){
	int n=s.length();
	if(flag==n-1) return true;
	for(int i=1;i+flag<n;i++){
		if(s[flag+i]!=s[flag-i])
			return false;
	}
	return true;
}

bool mid2(int flag1,string s){
	int flag2=flag1-1;
	for(int i=0;i+flag1<s.length();i++){
		if(s[flag1+i]!=s[flag2-i])
			return false;
	}
	return true;
}
int main(){
	string S;
	cin>>S;
	string output;
	int n=S.length();
	if(n%2==0){
		int flag1=n/2;
		for(int i=0;i<n;i++){
			if(i%2==0){
				if(mid2(flag1,S)){
					char *output= new char[2*flag1];
					for(int j=0;j<flag1;j++){
						
						output[j]=S[j];
						output[2*flag1-j-1]=S[j];
					}
					cout<<output<<endl;
				}
			}
			else{
				if(mid1(flag1,S)){
					char *output= new char[2*flag1+1];
					for(int j=0;j<=flag1;j++){
						
						output[j]=S[j];
						output[2*flag1-j]=S[j];
					}
					cout<<output<<endl;
				}
				flag1+=1;
			}
		}
	}
	if(n%2==1){
		int flag1=n/2;
		for(int i=0;i<=n;i++){
			if(i%2==0){
				if(mid2(flag1,S)){
					char *output= new char[2*flag1];
					for(int j=0;j<flag1;j++){		
						output[j]=S[j];
						output[2*flag1-j-1]=S[j];
					}
					cout<<output<<endl;
				}
			}
			else{
				if(mid1(flag1,S)){
					char *output= new char[2*flag1+1];
					for(int j=0;j<=flag1;j++){
						
						output[j]=S[j];
						output[2*flag1-j]=S[j];
					}
					cout<<output<<endl;
				}
				flag1+=1;
			}
		}
	}
    return 0;
}
