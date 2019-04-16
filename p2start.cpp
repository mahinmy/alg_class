#include <iostream>
#include <string>

using namespace std;

template <class T>
struct Node{
    T data;
    Node<T> *next;
};

template <class T>
class LinkStack{
private:
    Node<T> *top;
public:
    LinkStack(){
        top = NULL;
    }
    ~LinkStack(){
        Node<T> *tmp = NULL;
        while(top!=NULL){
            tmp = top;
            top = top->next;
            delete tmp;
        }
    }
    void PrintStack(){
        Node<T> *tmp = NULL;
        tmp = top;
        cout << "Top of stack: ";
        while(tmp!=NULL){
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << "Bottom of stack" << endl;
    }
    void Push(T x){
        Node<T> *s = NULL;
        s = new Node<T>;
        s->data = x;
        s->next = top;
        top = s;
    }
    T Pop(){
        Node<T> *tmp = NULL;
        if(top==NULL) throw "Empty";
        tmp = top;
        top = top->next;
        T x = tmp->data;
        delete tmp;
        return x;
    }
    T GetTop(){
        if(top!=NULL) return top->data;
        else throw "Empty";
    }
    bool IsEmpty(){
        return (top==NULL);
    }
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

template <class T>
class FCRSTree{
    private:
        T data;
        FCRSTree<T> *fchild;
        FCRSTree<T> *rsib;
        bool isLeaf(){
            return (fchild==NULL);
        }
    public:
        FCRSTree(){
            fchild = NULL;
            rsib = NULL;
        }
        FCRSTree(T x){
            data = x;
            fchild = NULL;
            rsib = NULL;
        }
        
        ~FCRSTree(){
            // Destroy the tree using postorder.
            if(fchild!=NULL) delete fchild;
            if(rsib!=NULL) delete rsib;
        }
        void addFirstChild(FCRSTree<T> * bt){
            fchild = bt;
        }
        void addRightSib(FCRSTree<T> * bt){
            rsib = bt;
        }
        void addFirstChild(T x){
            FCRSTree<T> * bt = new FCRSTree<T>(x);
            fchild = bt;
        }
        void addRightSib(T x){
            FCRSTree<T> * bt = new FCRSTree<T>(x);
            rsib = bt;
        }
        void addNewChild(FCRSTree<T> * bt){ //add to last
            if(fchild==NULL) {fchild = bt; return;}
            FCRSTree<T>* tmp = fchild;
            while(tmp->rsib!=NULL){
                tmp = tmp->rsib;
            }
            tmp->rsib = bt;
        }
        void addNewChild(T x){ //add to last
            addNewChild(new FCRSTree<T>(x));
        }
        void addNewSib(FCRSTree<T> * bt){ //add to last
            if(rsib==NULL) {rsib = bt; return;}
            FCRSTree<T>* tmp = rsib;
            while(tmp->rsib!=NULL){
                tmp = tmp->rsib;
            }
            tmp->rsib = bt;
        }
        void addNewSib(T x){ //add to last
            addNewSib(new FCRSTree<T>(x));
        }
        T getData(){
            return data;
        }
        void setData(T x){
            data = x;
        }
        FCRSTree<T>* getFirstChild(){
            return fchild;
        }
        FCRSTree<T>* getRightSib(){
            return rsib;
        }
        // print!
        void printPreOrderR(){
            cout << data << " ";
            if(fchild!=NULL) fchild->printPreOrderR();
            if(rsib!=NULL) rsib->printPreOrderR();
        }
        
        void printPostOrderR(){
            if(fchild!=NULL) fchild->printPostOrderR();
            cout << data << " ";
            if(rsib!=NULL) rsib->printPostOrderR();
        }
        
        void printLevelOrder(){ //question 2
            // TODO
        }
};

int test1(){
    FCRSTree<int>* tTree = new FCRSTree<int>(1);
    tTree->addNewChild(2);
    tTree->addNewChild(3);
    tTree->addNewChild(4);
    tTree->getFirstChild()->getRightSib()->getRightSib()->addFirstChild(8);
    tTree->getFirstChild()->addNewChild(5);
    tTree->getFirstChild()->getFirstChild()->addRightSib(6);
    tTree->getFirstChild()->getFirstChild()->addNewSib(7);
    tTree->getFirstChild()->getFirstChild()->getRightSib()->addNewChild(9);
    tTree->getFirstChild()->getFirstChild()->getRightSib()->addNewChild(10);
    
    tTree->printPreOrderR();
    cout << endl;
    tTree->printPostOrderR();
    cout << endl;
    tTree->printLevelOrder();
    cout << endl;
    return 0;
}

int main(){
    test1();
    return 0;
}