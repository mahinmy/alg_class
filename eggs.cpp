#include <iostream>
#include <iomanip>
using namespace std;

class EggDropTest{
    private:
        int critFloor;
        int highestFloor;

        int numTries;
        int eggsBroken;
        bool exactFloorTested;
        bool oneAboveTested;

    public:
        EggDropTest(){ // do not use this.
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
        EggDropTest(int cfloor, int tfloor){
            critFloor = cfloor;
            highestFloor = tfloor;
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
        bool testFloor(int fnum){
            // true if egg survives, false if egg breaks.
            numTries++;
            if(fnum <= critFloor){
                if(fnum==critFloor) exactFloorTested = true;
                return true;
            }
            else{
                if(fnum == critFloor + 1) oneAboveTested = true;
                eggsBroken++;
                return false;
            }
        }
        int getTries(){
            return numTries;
        }
        int getEggsBroken(){
            return eggsBroken;
        }
        bool floorConfirmed(){
            if(critFloor == 0){
                return oneAboveTested;
            }
            else if(critFloor==highestFloor){
                return exactFloorTested;
            }
            else{
                return (oneAboveTested && exactFloorTested);
            }
        }

        void setData(int cfloor, int tfloor){
            resetTries();
            critFloor = cfloor;
            highestFloor = tfloor;
        }
        void resetTries(){
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
};

// guaranteed at worst 300 floors, and at worst 10 eggs.

void initAnswers(){
    // TODO
}

int nextTestFloor(int hFloor, int eggsLeft, int lastSurvival,int lastBreak){
    int eggs = eggsLeft;
    int numFloors = lastBreak - lastSurvival - 1;
    if(numFloors == 0||eggs == 0){
        return -1;
    }
    if(numFloors==2 && eggs==2){
        return lastSurvival + 1;
    }
    if(numFloors == 1){
        return lastSurvival + 1;
    }
    if(eggs==1){
        return lastSurvival + 1;
    }
    int **cache = new int*[eggs+1];
    int **kCache = new int*[eggs+1];
    for(int i=0;i<=eggs;i++){
        cache[i] = new int[numFloors+1];
        kCache[i] = new int[numFloors+1];
    }
    for(int i=1;i<=eggs;i++){
        for(int j=1;j<=numFloors;j++){
            cache[i][j] = j;
        }
    }
    for(int i=1;i<=numFloors;i++){
        kCache[1][i] = 1;
    }
    for(int i=1;i<=eggs;i++){
        kCache[i][1] = 1;
    }
    for(int n=2;n<=eggs;n++){
        for(int m=1;m<=numFloors;m++){
            for(int k=1;k<m;k++){
                int part1 = cache[n-1][k-1];
                int part2 = cache[n][m-k];
                int max = part1 > part2 ? part1 : part2;
                if(cache[n][m]>1+max){
                    cache[n][m] = 1+max;
                    kCache[n][m] = k;
                }
            }
        }
    }
    // for(int i=1;i<=eggs;i++){
    //     for(int j=1;j<=numFloors;j++){
    //         cout<<right<<setw(5)<<cache[i][j];
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // for(int i=1;i<=eggs;i++){
    //     for(int j=1;j<=numFloors;j++){
    //         cout<<right<<setw(5)<<kCache[i][j];
    //     }
    //     cout<<endl;
    // }
    return kCache[eggs][numFloors] + lastSurvival;

}
int pow(int x, int y){
    int sum = 1;
    for(int i=0;i<y;i++){
        sum = sum * x;
    }
    return sum;
}
int canHandleFloors(int eggs, int numTries){
    if(eggs==1){
        return numTries;
    }
    if(eggs>=numTries){
        return pow(2, numTries)-1;
    }
    int **d;
    d = new int*[eggs+1];
    for(int i=0;i<=eggs;i++){
        d[i] = new int[numTries+1];
    }
    for(int i=1;i<=eggs;i++){
        d[i][i] = pow(2,i) - 1;
    }
    for(int i=1;i<=numTries;i++){
        d[1][i] = i;
    }
    for(int m=1;m<=numTries;m++){
        for(int n=m+1;n<=eggs;n++){
            d[n][m] = d[m][m];
        }
    }
    for(int i=2;i<=eggs;i++){
        for(int j=i+1;j<=numTries;j++){
            d[i][j] = d[i-1][j-1] + d[i][j-1] + 1;
        }
    }
    // for(int i=1;i<=eggs;i++){
    //     for(int j=1;j<=numTries;j++){
    //         cout<<right<<setw(5)<<d[i][j];
    //     }
    //     cout<<endl;
    // }
    return d[eggs][numTries];
}

int minTimesForBuilding(int eggs, int numFloors){
    if(eggs<1||numFloors<1){
        return 0;
    }
    int *preCache = new int[numFloors+1];
    int *currentCache = new int[numFloors+1];
    for(int i=1;i<=numFloors;i++){
        currentCache[i]=i;
    }
    for(int n=2;n<=eggs;n++){
        for(int i=1;i<=numFloors;i++){
            preCache[i]=currentCache[i];
        }
        for(int i=1;i<=numFloors;i++){
            currentCache[i]=i;
        }
        for(int m=1;m<=numFloors;m++){
            for(int k=1;k<m;k++){
                int max = preCache[k-1]>currentCache[m-k]?preCache[k-1]:currentCache[m-k];
                currentCache[m]=currentCache[m]<(1+max)?currentCache[m]:(1+max);
            }
        }
    }
    // for(int i=1;i<=numFloors;i++){
    //     cout<<right<<setw(5)<<currentCache[i];
    // }
    return currentCache[numFloors];
}

void minTimesTest(){
    for(int i=1;i<=10;i++){
        cout << right << setw(5) << i;
    }
    cout << endl;
    for(int j=1;j<=25;j++){
        for(int i=1;i<=10;i++)
            cout << right << setw(5) << minTimesForBuilding(i,j);
        cout << endl;
    }
    int testings[4] = {50,100,200,300};
    for(int j=0;j<4;j++){
        for(int i=1;i<=10;i++)
            cout << right << setw(5) << minTimesForBuilding(i,testings[j]);
        cout << endl;
    }
    cout << endl;
}

void handleFloorTest(){
    cout << right << setw(5) << " ";
    for(int i=1;i<=10;i++){
        cout << right << setw(5) << i;
    }
    cout << endl;
    for(int i=1;i<=8;i++){
        cout << right << setw(5) << i;
        for(int j=1;j<=10;j++){
            cout << right << setw(5) << canHandleFloors(j,i);
        }
        cout << endl;
    }
    cout << endl;
}

void setUpCase(int eggCount, int cFloor, int hFloor, int target){
    int lastSurvival = 0;
    int lastBreak = hFloor+1;
    int nextTest = 0;
    int eggsLeft = eggCount;
    EggDropTest edt(cFloor,hFloor);
    while(nextTest!=-1){
        nextTest = nextTestFloor(hFloor,eggsLeft,lastSurvival,lastBreak);
        if(nextTest==-1) break;
        if(edt.testFloor(nextTest)){
            lastSurvival = nextTest;
        }
        else{
            eggsLeft--;
            lastBreak = nextTest;
            if(eggsLeft==0) break;
        }
    }
    if(edt.floorConfirmed() && edt.getTries()<= target){
        cout << "Good" << endl;
    }
    else{
        cout << "Bad" << endl;
    }
}

void specificTests(int i){
    int floors[6] = {0,20,40,60,80,100};
    int counts[11] = {0,0,14,9,8,7,7,7,7,7,7};
    switch(i){
        case 10:
        case 9:
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
            for(int j=0;j<6;j++)
                setUpCase(i,floors[j],100,counts[i]);
            break;
        case 1: // reality check
            setUpCase(1,0,100,1);
            setUpCase(1,100,100,100);
            setUpCase(1,50,300,51);
            setUpCase(1,89,200,90);
        default:
            break;
    }
}

int main(){
    int testNum = 0;
    initAnswers();
    cin >> testNum;
    while(testNum!=11){
        switch(testNum){
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                specificTests(testNum);
                break;
            default:
                minTimesTest();
                handleFloorTest();
        }
        cin>>testNum;
    }
    return 0;
    nextTestFloor(100,3,56,78);
}

