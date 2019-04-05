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
class LTree{
    // List for storing children
    private:
        T data;
        LinkList<LTree<T> *> children;
        int numChild;
    public:
        LTree(){
            numChild = 0;
        }
        LTree(T x){
            data = x;
            numChild =  0;
        }
        ~LTree(){

        }
        void addChild(LTree<T>* lt){
            children.InsertLast(lt);
            numChild++;
        }
        void addChild(T x){
            LTree<T>* lt = new LTree<T>(x);
            children.InsertLast(lt);
            numChild++;
        }
        LTree<T>* getChild(T x){
            for(int i=0;i<numChild;i++){
                if(children.Get(i)->data == x)
                    return children.Get(i);
            }
            return NULL;
        }
        void setData(T x){
            data = x;
        }
        T getData(){
            return data;
        }
        void printPreOrder(){
            cout << data << " ";
            for(int i=0;i<numChild;i++){
                children.Get(i)->printPreOrder();
            }
        }
        void printPostOrder(){
            for(int i=0;i<numChild;i++){
                children.Get(i)->printPostOrder();
            }
            cout << data << " ";
        }
        void printLevelOrder(){
            LinkQueue<LTree<T> *> q;
            q.EnQueue(this);
            LTree<T>* tmp;
            while(!q.IsEmpty()){
                tmp = q.DeQueue();
                cout << tmp->data << " ";
                for(int i=0;i<tmp->numChild;i++){
                    q.EnQueue(tmp->children.Get(i));
                }
            }
        }

        // problem 2
        int height(){
            int h = 1,i,tmp = 0;
            if(numChild != 0){
                tmp = children.Get(0)->height();
            }
            for(i = 1; i < numChild; i++)
            {
                if (children.Get(i)->height() > tmp) {
                    tmp = children.Get(i)->height();
                }
            }
            h += tmp;
            return h;
        }
        int degree(){
            int i,tmp;
            tmp = numChild;
            for(i = 0; i < numChild; i++)
            {
                if (children.Get(i)->degree() > tmp) {
                    tmp = children.Get(i)->degree();
                }
            }
            return tmp;
        }

        int countNodeWithDeg(int x){
            LinkQueue<LTree<T> *> q;
            int count = 0;
            q.EnQueue(this);
            LTree<T>* tmp;
            while(!q.IsEmpty()){
                tmp = q.DeQueue();
                if(tmp->numChild == x){
                    count += 1;
                }
                for(int i=0;i<tmp->numChild;i++){
                    q.EnQueue(tmp->children.Get(i));
                }
            }
            return count;
        }


        // problem 3
        bool isDescendentOf(LTree<T> * lt){
            return lt->isAncestorOf(this);
        }

        bool isAncestorOf(LTree<T> * lt){
            if(lt == this) return false;
            LinkQueue<LTree<T> *> q;
            q.EnQueue(this);
            LTree<T>* tmp;
            while(!q.IsEmpty()){
                tmp = q.DeQueue();
                if(tmp == lt){
                    return true;
                }
                for(int i=0;i<tmp->numChild;i++){
                    q.EnQueue(tmp->children.Get(i));
                }
            }
            return false;
        }
};

// Question 1
LTree<int>* ques1(){
    // build the specified tree
    // TODO
    LTree<int> *q = new LTree<int>(25);
    LTree<int> *q15= new LTree<int>(15);
    LTree<int> *q50= new LTree<int>(50);
    LTree<int> *q10= new LTree<int>(10);
    LTree<int> *q70= new LTree<int>(70);
    q15->addChild(q10);
    q->addChild(q15);
    q->addChild(q50);
    q15->addChild(22);
    q10->addChild(12);
    q50->addChild(q70);
    q70->addChild(66);
    q70->addChild(90);
    return q;
}

void test1(){
    LTree<int>* r = ques1();
    r->printPreOrder();
    cout << endl;
    r->printPostOrder();
    cout << endl;
    r->printLevelOrder();
    cout << endl;
}

void test2(){
    LTree<char> testTree('A');
    testTree.addChild('B');
    LTree<char> testTree2('C');
    testTree2.addChild('G');
    testTree.addChild(&testTree2);
    LTree<char> * tmpTreeB = testTree.getChild('B');
    tmpTreeB->addChild('D');
    tmpTreeB->addChild('E');
    tmpTreeB->addChild('F');
    LTree<char> * tmpTreeE = tmpTreeB->getChild('E');
    tmpTreeE->addChild('H');
    tmpTreeE->addChild('I');
    //print trees now
    testTree.printPreOrder();
    cout << endl;
    testTree.printPostOrder();
    cout << endl;
    testTree.printLevelOrder();
    cout << endl;
    cout << "Height of the whole tree: " << testTree.height() << endl;
    cout << "Height of the B subtree: " << tmpTreeB->height() << endl;
    cout << "Degree of the whole tree: " << testTree.degree() << endl;
    cout << "Degree of the C subtree: " << testTree2.degree() << endl;
    cout << "Num of nodes with degree 0: " << testTree.countNodeWithDeg(0) << endl;
    cout << "Num of nodes with degree 1: " << testTree.countNodeWithDeg(1) << endl;
    cout << "Num of nodes with degree 2: " << testTree.countNodeWithDeg(2) << endl;
    cout << "Num of nodes with degree 3: " << testTree.countNodeWithDeg(3) << endl;
    cout << "Num of nodes with degree 4: " << testTree.countNodeWithDeg(4) << endl;
}

void test3(){
    LTree<char> testTree('A');
    testTree.addChild('B');
    LTree<char> testTree2('C');
    testTree2.addChild('G');
    testTree.addChild(&testTree2);
    LTree<char> * tmpTreeB = testTree.getChild('B');
    tmpTreeB->addChild('D');
    tmpTreeB->addChild('E');
    tmpTreeB->addChild('F');
    LTree<char> * tmpTreeE = tmpTreeB->getChild('E');
    tmpTreeE->addChild('H');
    tmpTreeE->addChild('I');
    //print tree now
    testTree.printPreOrder();
    cout << endl;
    testTree.printPostOrder();
    cout << endl;
    testTree.printLevelOrder();
    cout << endl;
    LTree<char> * tmpTreeI = tmpTreeE->getChild('I');
    cout << "Is I a descendent of B? " << (tmpTreeI->isDescendentOf(tmpTreeB) ? "Yes" : "No") << endl;
    cout << "Is I a descendent of C? " << (tmpTreeI->isDescendentOf(&testTree2) ? "Yes" : "No") << endl;
    cout << "Is I a descendent of A? " << (tmpTreeI->isDescendentOf(&testTree) ? "Yes" : "No") << endl;
    cout << "Is I a descendent of I? " << (tmpTreeI->isDescendentOf(tmpTreeI) ? "Yes" : "No") << endl;
    cout << "Is B a descendent of I? " << (tmpTreeB->isDescendentOf(tmpTreeI) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of B? " << (tmpTreeB->isAncestorOf(tmpTreeB) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of A? " << (tmpTreeB->isAncestorOf(&testTree) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of C? " << (tmpTreeB->isAncestorOf(&testTree2) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of I? " << (tmpTreeB->isAncestorOf(tmpTreeI) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of E? " << (tmpTreeB->isAncestorOf(tmpTreeE) ? "Yes" : "No") << endl;
}

int main(){
    //test1();
    /*test2();*/
    test3();
    return 0;
}
