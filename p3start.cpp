#include <iostream>
using namespace std;

const int MaxSize = 100;

template <class T>
class SeqList{
    private:
        int count;
        T data[MaxSize];
    public:
        SeqList(){
            count =0;
        }
        SeqList(T a[], int n){
            if(n > MaxSize) throw "Too many items";
            for(int i=0;i<n;i++){
                data[i] = a[i];
            }
            count = n;
        }
        ~SeqList(){
        }
        int Length(){
            return count;
        }

        T Get(int i){
            if(i < 0 || i >= count) throw "Bad index";
            return data[i];
        }

        int Locate(T x){
            for(int i=0;i<count;i++){
                if(data[i] == x) return i;
            }
            return -1;
        }

        void Insert(int i, T x){
            if(count >= MaxSize) throw "List full";
            if(i < 0 || i > count) throw "Bad index";
            for(int j=count;j>i;j--){
                data[j] = data[j-1];
            }
            data[i] = x;
            count++;
        }
        
        void Set(int i, T x){
            if(i < 0 || i >= count) throw "Bad index";
            data[i] = x;
        }

        T Delete(int i){
            if(i<0 || i>=count) throw "Bad index";
            T x = data[i];
            for(int j=i;j<count-1;j++){
                data[j] = data[j+1];
            }
            count--;
            return x;
        }
        void printList(){
            for(int i=0;i<count;i++){
                cout << data[i] << " ";
            }
        }
};

class IntPolynomial{
    private:
        
    public:
        IntPolynomial(){
            
        }
        IntPolynomial(int* a, int n){
            
        }
        ~IntPolynomial(){
            
        }
        int getDegree(){
            
        }
        IntPolynomial* Add(IntPolynomial* b){
            
        }
        IntPolynomial* Subtract(IntPolynomial* b){
            
        }
        IntPolynomial* Multiply(IntPolynomial* b){
            
        }
        void printPolynomial(){
            
        }
};

int main(){    
    int a[3] = {1,1,1};
    int b[3] = {1,-1,1};
    IntPolynomial* ip5 = new IntPolynomial(a,2);
    IntPolynomial* ip6 = new IntPolynomial(b,2);
    ip5->Add(ip6)->printPolynomial();
    cout << endl;
    ip5->Subtract(ip6)->printPolynomial();
    cout << endl;
    ip5->Multiply(ip6)->printPolynomial();
    cout << endl;
    return 0;
}
