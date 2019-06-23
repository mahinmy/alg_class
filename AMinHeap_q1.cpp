#include <iostream>
#include <iomanip>
using namespace std;

void
template <class T>
class AMinHeap{ // class T better has its comparison operators correctly overloaded
    private:
        int capacity;
        int numData;
        T* data;
        void expand(){
            T* oldData = data;
            data = new T[capacity << 1];
            for(int j=0; j<numData;j++){
                data[j] = oldData[j];
            }
            capacity = capacity << 1;
            delete[] oldData;
        }
    public:
        AMinHeap(){
            numData=0;
            capacity=0;
        }
        AMinHeap(T* arr, int n){
            numData = n;
            capacity = n;
            data = new int[n];
            for(int i=0;i<n;i++){
                data[i]=arr[i];
            }
        }
        ~AMinHeap(){
            delete data;
        }
        bool isEmpty(){
            return numData == 0;
        }
        T getMin(){

        }
        void push(T x){

        }
        T delMin(){

        }
        T* getLevelOrderArray(){

        }
        int getNumData(){
            return numData;
        }
};

template <class T>
void printLevelOrder(T* data, int numItems){ //assumes class T has an overloaded ostream << operator.
    for(int i=1;i<=numItems;i++){
        cout << data[i] << " ";
    }
}

int test1(){ // normal test
    AMinHeap<int> amh;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    amh.push(10);
    amh.push(8);
    amh.push(6);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    amh.push(4);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;

    cout << "Top: " << amh.getMin() << endl;
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;

    cout << "Popping:" << endl;
    while(!amh.isEmpty()){
        cout << "Current Min: " << amh.delMin() << endl;
        cout << endl;
    }
    return 0;
}

int main(){
    //unit test for Heap.
    test1();
    return 0;
}
