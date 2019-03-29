#include<iostream>
#include<string>
using namespace std;
bool del3(string s,int pos){
	int n=s.length();
	if(pos>n-3) return false;
	if(s[pos]==s[pos+1]&&s[pos]==s[pos+2]) return true;
	else return false;
}
bool doubledouble(string s,int pos){
	int n=s.length();
	if(pos>n-4) return false;
	if(s[pos]==s[pos+1]&&s[pos+2]==s[pos+3]) return true;
	else return false;
}
int main(){
	string s;
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(del3(s,i)){
			s=s.erase(i+2,1);
			i=i-1;
		}
		else if(doubledouble(s,i)){
			s=s.erase(i+3,1);
			i=i-1;
		}
	}
	cout<<s;
    return 0;
}
