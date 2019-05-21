#include <iostream>
#include <iomanip>
using namespace std;
long** help(){
    long **a = new long*[61];
    for(int i=0; i<61; i++){
        a[i] = new long[4];
    }
    a[0][0] = 0; a[0][1] = 0; a[0][2] = 0; a[0][3] = 0;
    a[1][0] = 1; a[1][1] = 1; a[1][2] = 0; a[1][3] = 0;
    a[2][0] = 1; a[2][1] = 0; a[2][2] = 1; a[2][3] = 0;
    a[3][0] = 3; a[3][1] = 1; a[3][2] = 1; a[3][3] = 1;
    for(int i = 4; i <= 60; i++){
        a[i][1] = a[i-1][2] + a[i-1][3];
        a[i][2] = a[i-2][1] + a[i-2][3];
        a[i][3] = a[i-3][1] + a[i-3][2];
        a[i][0] = a[i][1] + a[i][2] + a[i][3];
    }
    return a;
}
long numWaysToReach(int n){
    // TODO
    return help()[n][0];
}

void test1(){
    for(int i=1;i<=20;i++){
        cout << "Number of ways to walk to destination (" << i << "): " << numWaysToReach(i) << endl;
    }
}

int main(){
    test1();
    return 0;
}

