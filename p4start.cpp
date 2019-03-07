#include <iostream>
using namespace std;

const int InitMaxSize = 10;
template <class T>
class VecList{
    private:
        
        void expand(){
            
        }
    public:
        VecList(){
            
        }
        VecList(T a[], int n){
            
        }
        ~VecList(){
            
        }
        int Length(){
            
        }
        T Get(int i){
            
        }
        int Locate(T x){
            
        }
        void Insert(int i, T x){
            
        }
        T Delete(int i){
            
        }
        void printList(){
            
        }
};

int main(){
    int r[3] = {1,2,3};
    VecList<int> L(r,3);
    cout << "Current List:" << endl;
    L.printList();
    cout << endl;
    try{
        L.Insert(1,4);
        L.Insert(4,5);
        L.Insert(5,6);
        L.Insert(6,7);
    }
    catch(char *s){
        cout << s << endl;
    }
    cout << "After adding elements" << endl;
    L.printList();
    cout << endl << "Searching for position of 3:" << L.Locate(3) << endl;
    try{
        L.Delete(0);
    }
    catch(char *s){
        cout << s << endl;
    }
    cout << "Now we have deleted element at position 0" << endl;
    L.printList();
    return 0;
}
