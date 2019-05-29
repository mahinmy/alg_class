#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

class PancakeStack{
    private:
        int* stacksizes;
        int numCakes;
    public:
        PancakeStack(){
            stacksizes = NULL;
            numCakes = 0;
        }
        PancakeStack(int* sizes, int n){
            stacksizes = new int[n];
            numCakes = n;
            for(int i=0;i<n;i++){
                stacksizes[i] = sizes[i];
            }
        }
        ~PancakeStack(){
            if(stacksizes!=NULL) delete [] stacksizes;
        }
        void printsizes(){
            for(int i=0;i<numCakes;i++){
                cout << left << setw(4) << stacksizes[i];
                if(i%10==9) cout << endl;
            }
            cout << endl;
        }
        int getStackSize(){
            return numCakes;
        }
        int getSizeAtPos(int x){
            return stacksizes[x];
        }
        void flip(int k){
            // flip the cakes from stacksizes[0] through stacksizes[k] around.
            // (0,1,2,3,4,5,...,k,k+1,...,n) -> (k,k-1,...,1,0,k+1,...,n)
            int tmp = 0;
            for(int i=0;i<k-i;i++){
                tmp = stacksizes[i];
                stacksizes[i] = stacksizes[k-i];
                stacksizes[k-i] = tmp;
            }
        }
};

bool isSorted(PancakeStack &x){
    for(int i=0;i<x.getStackSize()-1;i++){
        if(x.getSizeAtPos(i)>x.getSizeAtPos(i+1)){
            return false;
        }
    }
    return true;
}

int getMax(PancakeStack &x, int n){//返回前n个位置里面最大的数字的位置
    int max = x.getSizeAtPos(0);
    int maxPos = 0;
    for(int i=1;i<n;i++){
        if(x.getSizeAtPos(i) > max){
            max = x.getSizeAtPos(i);
            maxPos = i;
        }
    }
    return maxPos;
}
void sortCakes(PancakeStack &x){
    // TODO
    // arrange cakes from small to large.
    for(int i=x.getStackSize()-1;i>=0;i--){
        if(!isSorted(x)){
            int maxPos = getMax(x, i+1);
            x.flip(maxPos);
            x.flip(i);
        }
    }
}

void test1(){
    int cakes[10] = {9,7,3,2,10,1,5,6,8,4};
    PancakeStack pcs(cakes,10);

    sortCakes(pcs);
    pcs.printsizes();
}

int main(){
    test1();
    return 0;
}

