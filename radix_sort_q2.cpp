#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

template <class T>
struct Node{
    T data;
    Node<T> *next;
};

template <class T>
class LinkList{
private:
    Node<T> *first, *last;
    int length;
public:
    LinkList(){
        first = new Node<T>;
        first->next = NULL;
        last = first;
        length = 0;
    }

    LinkList(T a[], int n){ //tail insertion style
        Node<T>* r, *s;
        first = new Node<T>;
        r=first;
        for(int i=0;i<n;i++){
            s = new Node<T>;
            s->data = a[i];
            r->next = s;
            r = s;
        }
        r->next = NULL;
        last = r;
        length = n;
    }

    ~LinkList(){
        Node<T> *q = NULL;
        while(first!=NULL){
            q=first;
            first=first->next;
            delete q;
        }
    }

    void Insert(int i, T x){
        Node<T> *p = first, *s = NULL;
        int count = -1;
        if(i<0) throw "Bad index";
        while(p!=NULL && count < i-1){ //seek (i-1)-th point
            p = p-> next;
            count++;
        }
        if(p==NULL) throw "Bad index";
        else{
            s = new Node<T>;
            s->data = x;
            s->next = p->next;
            p->next = s;
            if(s->next==NULL) last=s;
        }
        length++;
    }

    void InsertLast(T x){
        Node<T> *s = NULL;
        s = new Node<T>;
        s->data = x;
        s->next = NULL;
        last->next = s;
        last = s;
        length++;
    }

    T Delete(int i){
        Node<T> *p = first, *q = NULL;
        T x;
        int count=-1;
        if(i<0) throw "Bad index";
        while(p!=NULL && count < i-1){ //seek (i-1)-th point
            p = p-> next;
            count++;
        }
        if(p==NULL || p->next == NULL) throw "Bad index";
        else{
            q=p->next;
            x=q->data;
            p->next = q->next;
            if(last==q) last=p;
            delete q;
            length--;
            return x;
        }
    }

    int Locate(T x){
        Node<T> *p = first->next;
        int count=0;
        while(p!=NULL){
            if(p->data == x){
                return count;
            }
            p = p->next;
            count++;
        }
        return -1;
    }

    void printList(){
        //print all the elements in this list, but will not give an "endl" at the end.
        Node<T> *p = first->next;
        while(p!=NULL){
            cout << p->data << " ";
            p = p->next;
        }
    }

    T Get(int i){
        Node<T> *p = first;
        int count=-1;
        if(i<0) throw "Bad index";
        while(p!=NULL && count < i){ //seek i-th point
            p = p-> next;
            count++;
        }
        if(p==NULL) throw "Bad index";
        return p->data;
    }

    int Length(){
        return length;
    }
};

template <class T>
class LinkQueue{
    private:
        LinkList<T> q;
    public:
        LinkQueue(){
            
        }
        ~LinkQueue(){
              
        }
        void EnQueue(T x){
            q.InsertLast(x);
        }
        T DeQueue(){
            if(q.Length()==0) throw "Queue Empty";
            return q.Delete(0);
        }
        T PeekQueue(){
            if(q.Length()==0) throw "Queue Empty";
            return q.Get(0);
        }
        bool IsEmpty(){
            return (q.Length()==0);
        }
        void PrintQueue(){
            cout << "Front of Queue: ";
            q.printList();
            cout << "End of Queue" << endl;
        }
};

int* generateRandom(int num, int min, int max){ //generate random numbers between min and max, inclusive
    int* tmp = new int[num];
    for(int i=0;i<num;i++)
        tmp[i] = rand() % (max+1-min) + min;
    return tmp;
}

template <class T>
T* dupArray(T* arr, int n){
    T* tmp = new T[n];
    for(int i=0;i<n;i++){
        tmp[i] = arr[i];
    }
    return tmp;
}

template <class T>
struct MultiKey{
    T* keys;
    int keylength;
};

template <class T>
void radixDesc(MultiKey<T>** mk, int n, int keylen, int low, int high){
    // mk is an array of MultiKey<T>*
    // n = number of items in mk.
    //key[0] most important, key[1] second most important
    // low and high inclusive
    // TODO
    LinkList<MultiKey<T>*>** l=new LinkList<MultiKey<T>*>*[high-low+1];
    for(int i=0;i<=high-low;i++){
        l[i]=new LinkList<MultiKey<T>*>();
    }
    int tmp;
    for(int i=keylen-1;i>=0;i--){
        for(int j=0;j<n;j++){
            tmp=mk[j]->keys[i]-low;
            l[tmp]->InsertLast(mk[j]);
        }
        int t=high-low;
        for(int k=0;k<n;k++){
            while(l[t]->Length()==0) t--;
            mk[k]=l[t]->Delete(0);
        }
    }
}

int simpleTest(){
    srand(time(NULL));
    MultiKey<int>** mk = new MultiKey<int>*[40];
    for(int i=0;i<40;i++){
        mk[i] = new MultiKey<int>;
        mk[i]->keys = generateRandom(5,0,9);
        mk[i]->keylength = 5;
    }
    
    radixDesc(mk,40,5,0,9);
    
    //print results
    for(int i=0;i<40;i++){
        for(int j=0;j<5;j++){
            cout << mk[i]->keys[j];
        }
        cout << " ";
        if(i%10==9) cout << endl;
    }
    
    return 0;
}

int main(){
    simpleTest();
    return 0;
}
