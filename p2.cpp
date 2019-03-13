#include <iostream>
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
        return 0;
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
/*api:Insert(i,x),InsertLast(x),Delete(i),Locate(x),Get(i),printList(),Length()*/
struct vecData{
    int position;
    int data;
};
int main(){
    LinkList<vecData> a=LinkList<vecData>();
    LinkList<vecData> b=LinkList<vecData>();
    /*a = new LinkList<vecData>();
    b = new LinkList<vecData>();*/
    int s,t;
    cin>>s;
    while(s!=-1){
        cin>>t;
        struct vecData input={s,t};
        a.InsertLast(input);
        cin>>s;
    }
    cin>>s;
    while(s!=-1){
        cin>>t;
        struct vecData input={s,t};
        b.InsertLast(input);
        cin>>s;
    }
    //finish input
    int sum=0;
    int i,j;
    for(i=0;i<a.Length();i++){
        for(j=0;j<b.Length();j++){
            int positionA = a.Get(i).position;
            int positionB = b.Get(j).position;
            if(positionA == positionB){
                int dataA = a.Get(i).data;
                int dataB = b.Get(j).data;
                sum+=dataA*dataB;
            }
        }
    }
    cout<<sum;
    return 0;
}