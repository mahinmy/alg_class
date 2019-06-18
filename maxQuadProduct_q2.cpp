#include <iostream>
#include <stdlib.h>
using namespace std;

int quickPivot(int* &arr, int n, int sIndex, int eIndex){ //use first element as pivot, put pivot in correct position, return index
    int le = sIndex;
    int ri = eIndex;
    while(le<ri){
        while(le<ri && arr[le] <= arr[ri]) ri--;
        if(le<ri){
            int tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
            le++;
        }
        while(le<ri && arr[le] <= arr[ri]) le++;
        if(le<ri){
            int tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
            ri--;
        }
    }
    return le;
}
void quickAsc(int* &arr, int n, int sIndex, int eIndex){ //start index, end index inclusive
    if(sIndex >= eIndex) return;
    int pivotPos = quickPivot(arr,n, sIndex, eIndex);
    quickAsc(arr,pivotPos,sIndex,pivotPos-1);
    quickAsc(arr,n-pivotPos-1,pivotPos+1,eIndex);
}
int maxQuadProduct(int* arr, int n){
    // TODO
    quickAsc(arr,n,0,n-1);
    int a1 = arr[n-1]*arr[n-2]*arr[n-3]*arr[n-4];
    int a2 = arr[n-1]*arr[n-2]*arr[0]*arr[1];
    int a3 = arr[0]*arr[1]*arr[2]*arr[3];
    int max1 = a1>a2?a1:a2;
    return max1>a3?max1:a3;
}

void test1(){
    int tmp1[7] = {3,7,5,1,9,10,2};
    int tmp4[10] = {-10,-8,-2,0,3,9,15,1,7,4};
    cout << "Case 1: Maximum product is " << maxQuadProduct(tmp1,7) << endl;
    cout << "Case 4: Maximum product is " << maxQuadProduct(tmp4,10) << endl;
    cout << endl;
}

int main()
{
    test1();
    return 0;
}
