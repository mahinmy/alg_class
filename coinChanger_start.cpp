#include <iostream>
#include <stdlib.h>

using namespace std;

class coinChanger{
    private:
        
    public:
        coinChanger(){
            
        }
        coinChanger(int* coinValueSet, int n){
            
        }
        ~coinChanger(){
            
        }
        void clearResults(){
            
        }
        void setCoinValueSet(int* coinValueSet, int n){
            
        }
        int numCoinsToMakeChange(int target){
            // small to large for coinValues
            // limit target to be <= 1000;
            // return -1 if impossible.
            
        }
};

void test1(){
    srand(1387423);
    int coinValueSet1[4] = {1,2,5,10};
    int coinValueSet3[2] = {5,7};
    
    coinChanger cc(coinValueSet1,4);
    
    cout << "Using the set {1,2,5,10}, making changes for:" << endl;
    cout << "99: " << cc.numCoinsToMakeChange(99) << endl;
    cout << "98: " << cc.numCoinsToMakeChange(98) << endl;
    cout << "579: " << cc.numCoinsToMakeChange(579) << endl;
    cout << "998: " << cc.numCoinsToMakeChange(998) << endl;
    
    for(int i=0;i<5000;i++){
        cc.numCoinsToMakeChange(rand()%1001);
    }
    
    cc.setCoinValueSet(coinValueSet3,2);
    cc.clearResults();
    cout << "Using the set {5,7}, making changes for: " << endl;
    cout << "99: " << cc.numCoinsToMakeChange(99) << endl;
    cout << "98: " << cc.numCoinsToMakeChange(98) << endl;
    cout << "579: " << cc.numCoinsToMakeChange(579) << endl;
    cout << "998: " << cc.numCoinsToMakeChange(998) << endl;
    cout << "23: ";
    if(cc.numCoinsToMakeChange(23)==-1) cout << "Impossible" << endl;
    else cout << cc.numCoinsToMakeChange(23) << endl;
    
    for(int i=0;i<5000;i++){
        cc.numCoinsToMakeChange(rand()%1001);
    }
}

int main(){
    test1();
    return 0;
}
