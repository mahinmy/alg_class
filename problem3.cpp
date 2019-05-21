#include <iostream>
#include <iomanip>
using namespace std;

long long* help(){
    long long *a = new long long[61];
    a[0]=0;
    a[1]=1;
    a[2]=1;
    a[3]=3;
    a[4]=3;
    a[5]=6;
    a[6]=13;
    for(int i=7;i<=60;i++){
        a[i]=a[i-4]+a[i-2]+a[i-6];
    }
    for(int i=4;i<=60;i++){
        a[i] = a[i-1] + a[i-2] + a[i-3];
    }
    return a;
}
long long numWaysToReach(int n){
    // TODO
    return help()[n];
}

void test1(){
    for(int i=1;i<=60;i++){
        cout << "Number of ways to walk to destination (" << i << "): " << numWaysToReach(i) << endl;
    }
}

int main(){
    test1();
    return 0;
}

