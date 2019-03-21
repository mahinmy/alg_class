#include <iostream>
#include <string>
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
        if(i<0)
            throw "Bad index";
        while(p!=NULL && count < i-1){ //seek (i-1)-th point
            p = p-> next;
            count++;
        }
        if(p==NULL)
            throw "Bad index";
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
        if(i<0)
            throw "Bad index";
        while(p!=NULL && count < i-1){ //seek (i-1)-th point
            p = p-> next;
            count++;
        }
        if(p==NULL || p->next == NULL)
            throw "Bad index";
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
        if(i<0)
            throw "Bad index";
        while(p!=NULL && count < i){ //seek i-th point
            p = p-> next;
            count++;
        }
        if(p==NULL)
            throw "Bad index";
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
            if(q.Length()==0)
                throw "Queue Empty";
            return q.Delete(0);
        }
        T PeekQueue(){
            if(q.Length()==0)
                throw "Queue Empty";
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

/* 
    priority queue with at most 10 different levels of priority
    Priority count starts from 0 (highest priority), 1 (next highest), etc...
*/

template <class T>
class SimplePriorityQueue{
    private:
        LinkList<LinkQueue<T>*> l;
        int prio;
    public:
        SimplePriorityQueue(){
            for(int i=0;i<10;i++){
                LinkQueue<T> *lq=new LinkQueue<T>();
                l.InsertLast(lq);
            }
            prio=10;
        }
        SimplePriorityQueue(int numP){
            for(int i=0;i<numP;i++){
                LinkQueue<T> *lq=new LinkQueue<T>();
                l.InsertLast(lq);
            }
            prio=numP;
        }
        ~SimplePriorityQueue(){
            while(l.Length()!=0){
                l.Delete(0);
            }
        }
        void EnQueue(T x, int p){ //the int here is for priority
            l.Get(p)->EnQueue(x);
        }
        T DeQueue(){
            for(int i=0;i<prio;i++){
                if(!l.Get(i)->IsEmpty())
                    return l.Get(i)->DeQueue();
            }
        }
        T PeekQueue(){
            for(int i=0;i<prio;i++){
                if(!l.Get(i)->IsEmpty())
                    return l.Get(i)->PeekQueue();
            }
        }
        bool IsEmpty(){
            for(int i=0;i<prio;i++)
                if(!l.Get(i)->IsEmpty())
                    return false;
            return true;
        }
};

int main(){
    // TODO
    SimplePriorityQueue<char> spq(6);
    cout << "Before insertion, queue is " << (spq.IsEmpty()?"empty":"non-empty") << endl;
    int priors[17]={0,1,2,3,4,5,0,3,2,4,0,2,1,5,1,3,2};
    //             {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q}
    for(int i=0;i<17;i++){
        spq.EnQueue('a'+i,priors[i]);
    }
    
    cout << "Front of queue is now " << spq.PeekQueue() << endl;
    // Push out first 10 items
    for(int j=0;j<10;j++){
        cout << spq.DeQueue() << " has left the queue" << endl;
    }
    cout << "Right now, queue is " << (spq.IsEmpty()?"empty":"non-empty") << endl;
    cout << "Inserting some digits according to squares mod 6" << endl;
    for(int i=0;i<10;i++){
        spq.EnQueue('0'+i,i*i%6);
    }
    // Empty the queues
    while(!spq.IsEmpty()){
        cout << spq.DeQueue() << " has left the queue" << endl;
    }
    cout << "Right now, queue is " << (spq.IsEmpty()?"empty":"non-empty") << endl;
    for(int i=0;i<10;i++){
        spq.EnQueue('0'+i,i%6);
    }
    cout << "Right now, queue is " << (spq.IsEmpty()?"empty":"non-empty") << endl;
    return 0;
}
