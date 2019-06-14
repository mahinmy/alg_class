#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <string>
using namespace std;

int hash1(int x, int hashMax){
    return x % hashMax;
}

int hash2(int x, int hashMax){
    // Here, hashMax needs to be 2 mod 3.
    int tmp1 = x%hashMax;
    int tmp2 = (tmp1 * tmp1) % hashMax;
    tmp2 = (tmp2 * tmp1) % hashMax;
    return tmp2;
}

int hash3(string x, int hashMax){
    // randomly fixed a prime 401.
    int l = x.length();
    int tmpNum = 0;
    for(int i=0;i<l;i++){
        tmpNum = (tmpNum * 401 + x[i]) % hashMax;
    }
    return tmpNum;
}

const int InitMaxSize = 10;
template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* data;
        void expand(){
            T* oldData = data;
            data = new T[capacity << 1];
            for(int j=0; j<length;j++){
                data[j] = oldData[j];
            }
            capacity = capacity << 1;
            delete[] oldData;
        }
    public:
        VecList(){
            data = new T[InitMaxSize];
            length = 0;
            capacity = InitMaxSize;
        }
        VecList(T a[], int n){
            data = new T[n << 1];
            for(int i=0;i<n;i++){
                data[i] = a[i];
            }
            length = n;
            capacity = n << 1;
        }
        ~VecList(){
            delete[] data;
        }
        int Length(){
            return length;
        }
        T Get(int i){
            if (i <0 || i >= length) throw "Bad index";
            else return data[i];
        }
        int Locate(T x){
            for(int i = 0;i<length;i++){
                if(data[i]==x) return i;
            }
            return -1;
        }
        void Insert(int i, T x){
            if(length >= capacity) expand();
            if(i < 0 || i > length) throw "Bad index";
            for(int j=length;j>i;j--){
                data[j]=data[j-1];
            }
            data[i] = x;
            length++;
        }
        void InsertLast(T x){
            Insert(length,x);
        }
        T Delete(int i){
            if(i < 0 || i >= length) throw "Bad index";
            T x = data[i];
            for(int j=i;j < length-1; j++){
                data[j] = data[j+1];
            }
            length--;
            return x;
        }
        void printList(){
            for (int i =0;i< length;i++){
                cout << data[i] << " ";
            }
        }
};

template <class T>
class OpenHashTable{
    private:
        int (*hashfn)(T,int);
        int numData;
        int hashListNum;
        int collision;
        VecList<T> **vl;
    public:
        OpenHashTable(){
            numData=0;
            hashListNum=47;
            hashfn = NULL;
            vl =  new VecList<T>*[47];
            for(int i=0;i<47;i++){
                vl[i]=new VecList<T>();
            }
            collision = 0;
        }
        OpenHashTable(int table_size){
            // pray that whatever's given to us is a prime. or else things can get real ugly.
            // TODO
            hashfn = NULL;
            numData=0;
            hashListNum=table_size;
            vl =  new VecList<T>*[table_size];
            for(int i=0;i<table_size;i++){
                vl[i]=new VecList<T>();
            }
            collision = 0;
        }
        ~OpenHashTable(){
            for(int i=0;i<hashListNum;i++){
                delete vl[i];
            }
            delete vl;
        }
        void setHashFn(int (*f)(T, int)){
            if(hashfn==NULL)
                hashfn = f;
            else{
                cout << "Cannot reset hash function." << endl;
            }
        }
        bool isEmpty(){
            return numData==0;
        }
        bool searchData(T x){
            return vl[hashfn(x, hashListNum)]->Locate(x)==-1 ? false : true;
        }
        void insertData(T x){
            int hashListPos = hashfn(x,hashListNum);
            if(vl[hashListPos]->Locate(x)!=-1){
                return;
            }
            vl[hashListPos]->InsertLast(x);
            if(vl[hashListPos]->Length()!=1){
                collision += 1;
            }
            numData += 1;
        }
        void deleteData(T x){
            int hashListPos = hashfn(x,hashListNum);
            if(vl[hashListPos]->Locate(x)!=-1){
                vl[hashListPos]->Delete(vl[hashListPos]->Locate(x));
                numData-=1;
            }
        }
        void printTable(){
            // TODO
            for(int i=0;i<hashListNum;i++){
                if(vl[i]->Length()!=0){
                    cout<<"Cell "<<i<<": ";
                    vl[i]->printList();
                    cout<<endl;
                }
            }
        }
        int getCollisionCount(){
            return collision;
        }
};

void test1(int (*h)(int, int)){
    OpenHashTable<int> ht(23); //the table with 47 entries should be fine.
    ht.setHashFn(h);
    int randomNums[20];
    for(int i=0;i<20;i++)
        randomNums[i] = rand() % 10000;
    for(int i=0;i<20;i++){
        cout << randomNums[i] << " (" << h(randomNums[i],23) << "), ";
        ht.insertData(randomNums[i]);
        if(i%5==4){
            cout << endl;
            cout << "Current Table is as follows:" << endl;
            ht.printTable();
            cout << endl;
        }
    }
    ht.printTable();
    cout << "Collision count: " << ht.getCollisionCount() << endl;
    cout << endl;
}

int main()
{
    srand(123456);
    test1(hash1);
    // probably more tests
    // OpenHashTable<int> ht(5); //the table with 47 entries should be fine.
    // ht.setHashFn(hash1);
    // ht.insertData(5);
    // ht.insertData(10);
    // ht.insertData(23);
    // cout<<ht.getCollisionCount()<<"\n"<<ht.isEmpty()<<"\n"<<ht.searchData(15)<<"\n"<<ht.searchData(14)<<"\n";
    // ht.printTable();
}
