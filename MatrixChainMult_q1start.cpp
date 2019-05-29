#include <iostream>
#include <iomanip>
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
class BinTree{
    private:
        T data;
        BinTree<T> *left;
        BinTree<T> *right;
    public:
        BinTree(){
            left = NULL;
            right = NULL;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
        }
        
        // copy tree
        BinTree(const BinTree<T>& rhs){
            data = rhs.data;
            cout << data << endl;
            if(rhs.left!=NULL) addLChild(new BinTree<T>(*rhs.left));
            else left = NULL;
            if(rhs.right!=NULL) addRChild(new BinTree<T>(*rhs.right));
            else right = NULL;
        }
        ~BinTree(){
            // Destroy the tree using postorder.
            if(left!=NULL) delete left;
            if(right!=NULL) delete right;
        }
        bool isLeaf(){
            return (left==NULL && right==NULL);
        }
        void addLChild(BinTree<T> * bt){
            left = bt;
        }
        void addRChild(BinTree<T> * bt){
            right = bt;
        }
        void addLChild(T x){
            BinTree<T> * bt = new BinTree<T>(x);
            left = bt;
        }
        void addRChild(T x){
            BinTree<T> * bt = new BinTree<T>(x);
            right = bt;
        }
        T getData(){
            return data;
        }
        void setData(T x){
            data = x;
        }
        BinTree<T>* getLChild(){
            return left;
        }
        BinTree<T>* getRChild(){
            return right;
        }
        // print!
        void printPreOrderR(){
            cout << data << " ";
            if(left!=NULL) left->printPreOrderR();
            if(right!=NULL) right->printPreOrderR();
        }
        
        void printPostOrderR(){
            if(left!=NULL) left->printPostOrderR();
            if(right!=NULL) right->printPostOrderR();
            cout << data << " ";
        }
        
        void printInOrderR(){
            if(left!=NULL) left->printInOrderR();
            cout << data << " ";
            if(right!=NULL) right->printInOrderR();
        }
        
        //non-recursive version of PreOrderR
        void printPreOrderNR(){
            LinkStack<BinTree<T> *> s;
            BinTree<T> * tmp = this;
            while(tmp!=NULL || !s.IsEmpty()){
                if(tmp!=NULL){
                    cout << tmp->data << " ";
                    s.Push(tmp);
                    tmp = tmp->left;
                }
                else{
                    tmp = s.Pop()->right;
                }
            }
        }
        
        //non-recursive version of postorder
        // using special marker (NULL) to set for going to stack 2.
        void printPostOrderNR(){
            LinkStack<BinTree<T> *> s1, s2;
            BinTree<T> * tmp = this;
            while(tmp!=NULL || !s1.IsEmpty()){
                if(tmp!=NULL){
                    s1.Push(tmp);
                    tmp = tmp->left;
                }
                else{
                    tmp = s1.Pop();
                    if(tmp!=NULL){
                        s1.Push(NULL);
                        s2.Push(tmp);
                        tmp = tmp->right;
                    }
                    else{
                        tmp = s2.Pop();
                        cout << tmp->data << " ";
                        tmp = NULL;
                    }
                }
            }
        }
        
        void printPostOrderNR2(){
            LinkStack<BinTree<T> *> s;
            BinTree<T> * tmp = this;
            while(tmp!=NULL || !s.IsEmpty()){
                if(tmp!=NULL){
                    s.Push(NULL);
                    s.Push(tmp);
                    tmp = tmp->left;
                }
                else{
                    tmp = s.Pop();
                    if(tmp!=NULL && (!s.IsEmpty() && s.GetTop()==NULL)){
                        s.Pop();
                        s.Push(tmp);
                        tmp = tmp->right;
                    }
                    else{
                        cout << tmp->data << " ";
                        tmp = NULL;
                    }
                }
            }
        }
        
        //non-recursive version of In-order
        void printInOrderNR(){
            LinkStack<BinTree<T> *> s;
            BinTree<T> * tmp = this;
            while(tmp!=NULL || !s.IsEmpty()){
                if(tmp!=NULL){
                    s.Push(tmp);
                    tmp = tmp->left;
                }
                else{
                    tmp = s.Pop();
                    cout << tmp->data << " ";
                    tmp = tmp->right;
                }
            }
        }
        
        void printLevelOrder(){
            LinkQueue<BinTree<T> *> q;
            q.EnQueue(this);
            BinTree<T> * tmp;
            while(!q.IsEmpty()){
                tmp = q.DeQueue();
                cout << tmp->data << " ";
                if(tmp->left!=NULL) q.EnQueue(tmp->left);
                if(tmp->right!=NULL) q.EnQueue(tmp->right);
            }
        }
};

/* Solution here */

// matrix chain multiplication problem
void printResult(int **s,int i,int j){
    if(i==j){
        cout<<"("<<i-1<<")";
    }
    else{
        cout<<"(";
        printResult(s,i,s[i][j]);
        printResult(s,s[i][j]+1,j);
        cout<<")";
    }
}
int minOpMatrixMult(int* sizes, int n){
    // n represents number of matrices
    // 0th matrix has dimensions sizes[0] x sizes[1]
    // 1st matrix has dimensions sizes[1] x sizes[2]
    // ...
    // (n-1)-th matrix has dimensions sizes[n-1] x sizes[n]
    //
    // Goal: find minimum number of operations to multiply the whole set of matrices
    // also print the parenthesis to do it.
    
    // TODO
    int **m;
    m = new int*[n+1];
    for(int i=0;i<n+1;i++){
        m[i] = new int[n+1];
        //n+1是为了索引方便从1到n
    }
    for(int i=1;i<=n;i++){
        m[i][i] = 0;
    }
    int **s;
    s = new int*[n+1];
    for(int i=0;i<n+1;i++){
        s[i] = new int[n+1];
        //n+1是为了索引方便从1到n
    }
    for(int i=1;i<=n;i++){
        m[i][i] = 0;
    }
    for(int l=2;l<=n;l++){
        for(int i=1;i<=n-l+1;i++){
            int j=i+l-1;
            m[i][j]=100000000;
            for(int k=i;k<=j-1;k++){
                int q = m[i][k] + m[k+1][j] + sizes[i-1]*sizes[k]*sizes[j];
                if(q<m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    printResult(s,1,n);
    return m[1][n];
}

/* End solution */

void test1(){
    int case1[4] = {10,30,5,60};
    int case4[5] = {1,2,3,4,5};
    int case5[3] = {3,3,3};
    
    cout << "Case 1: " << endl;
    int x = minOpMatrixMult(case1,3);
    cout << "Total operations = " << x << endl << endl;
    
    cout << "Case 4: " << endl;
    x = minOpMatrixMult(case4,4);
    cout << "Total operations = " << x << endl << endl;
    
    cout << "Case 5: " << endl;
    x = minOpMatrixMult(case5,2);
    cout << "Total operations = " << x << endl << endl;
}

int main(){
    test1();
    return 0;
}
