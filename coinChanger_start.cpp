#include <iostream>
#include <stdlib.h>

using namespace std;

class coinChanger{
    private:
        int numCoins;
        int *coinKinds;
        int *coinUsed;
    public:
        coinChanger(){
            numCoins=0;
        }
        coinChanger(int* coinValueSet, int n){
            numCoins = n;
            coinKinds = new int[n];
            for(int i = 0; i < n; i++){
                coinKinds[i]= coinValueSet[i];
            }
        }
        ~coinChanger(){
            if(numCoins > 0)
                delete coinKinds;
        }
        void clearResults(){
            delete coinUsed;
        }
        void setCoinValueSet(int* coinValueSet, int n){
            numCoins = n;
            coinKinds = new int[n];
            for(int i = 0; i < n; i++){
                coinKinds[i]= coinValueSet[i];
            }
        }
        int numCoinsToMakeChange(int target){
            // small to large for coinValues
            // limit target to be <= 1000;
            // return -1 if impossible.
            coinUsed = new int[target + 1];
            for(int i=0;i<target + 1;i++){
                coinUsed[i] = 0;
            }
            for(int cents=1;cents <= target;cents++){
                //先验证cents是否比所有硬币小
                bool flag=false;
                for(int i=0;i<numCoins;i++){
                    if(cents>=coinKinds[i]){
                        flag = true;
                    }
                }
                if(!flag){
                    coinUsed[cents] = -1;
                }
                else{
                    int minCoins = cents + 1;
                    for(int coin_index = 0; coin_index<numCoins; coin_index++){
                        if(coinKinds[coin_index] <= cents){
                            int tmp = coinUsed[cents - coinKinds[coin_index]] + 1;
                            if(tmp < minCoins && tmp != 0){
                                minCoins=tmp;
                            }
                        }
                    }
                    if(minCoins == cents +1){
                        coinUsed[cents] = -1;
                    }
                    else
                        coinUsed[cents] = minCoins;
                }
            }
            return coinUsed[target];
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
    /*cout << "Using the set {5,7}, making changes for: " << endl;
    cout << "99: " << cc.numCoinsToMakeChange(99) << endl;
    cout << "98: " << cc.numCoinsToMakeChange(98) << endl;
    cout << "579: " << cc.numCoinsToMakeChange(579) << endl;
    cout << "998: " << cc.numCoinsToMakeChange(998) << endl;*/
    for(int i=1;i<=1000;i++){
        cout <<i<< ": ";
        if(cc.numCoinsToMakeChange(i)==-1) cout << "Impossible" << endl;
        else cout << cc.numCoinsToMakeChange(i) << endl;
    }
    
    /*for(int i=0;i<5000;i++){
        cc.numCoinsToMakeChange(rand()%1001);
    }*/
}

int main(){
    test1();
    return 0;
}
