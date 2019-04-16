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
        
        ~BinTree(){
            // Destroy the tree using postorder.
            if(left!=NULL) delete left;
            if(right!=NULL) delete right;
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
        bool isLeaf(){
            return (left==NULL && right==NULL);
        }
        // print!
        void printPreOrderR(){
            cout << data << " ";
            if(left!=NULL) left->printPreOrderR();
            if(right!=NULL) right->printPreOrderR();
        }
        
        void printPreOrderNR(){
            LinkStack<BinTree<T> *> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.IsEmpty()){
                if(tmp!=NULL){
                    cout << tmp->data << " ";
                    s.Push(tmp);
                    tmp = tmp->left;
                }
                else{ // tmp == NULL, meaning we pop.
                    tmp = s.Pop()->right;
                }
            }
        }
        
        void printPostOrderR(){
            if(left!=NULL) left->printPostOrderR();
            if(right!=NULL) right->printPostOrderR();
            cout << data << " ";
        }
        
        void printPostOrderNR(){
            LinkStack<BinTree<T> *> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.IsEmpty()){
                if(tmp!=NULL){
                    s.Push(tmp);
                    tmp = tmp->left;
                }
                else{ // tmp == NULL, meaning we pop.
                    tmp = s.Pop();
                    if(s.IsEmpty() || s.GetTop()!=tmp){ // first pop only
                        s.Push(tmp);
                        s.Push(tmp);
                        tmp = tmp->right;
                    }
                    else{ // second pop
                        s.Pop();
                        cout << tmp->data << " ";
                        tmp = NULL;
                    }
                }
            }
        }
        
        void printInOrderR(){
            if(left!=NULL) left->printInOrderR();
            cout << data << " ";
            if(right!=NULL) right->printInOrderR();
        }
        
        void printInOrderNR(){
            LinkStack<BinTree<T> *> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.IsEmpty()){
                if(tmp!=NULL){
                    s.Push(tmp);
                    tmp = tmp->left;
                }
                else{ // tmp == NULL, meaning we pop.
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
bool isPrefixCode(string* codes, int numCodes){
    // codes[0], codes[1], ..., codes[numCodes-1] are all the codes
    // each code is a string of 0's and 1's.
    // the job is to determine whether the given code is a prefix code.

    // TODO
    //whether codes only contain 0 and 1
    for(int i=0;i<numCodes;i++){
        for(int j=0;j<codes[i].length();j++){
            if(codes[i][j] != '0' && codes[i][j] != '1'){
                return false;
            }
        }
    }
    //bubble sort
    bool swapped = true;
    while(swapped){
        swapped = false;
        for(int i=0;i<numCodes-1;i++){
            if(codes[i].length()>codes[i+1].length()){
               string tmp = codes[i];
               codes[i] = codes[i+1];
               codes[i+1] = tmp;
               swapped = true;
            }
        }
    }
    for(int i=0;i<numCodes-1;i++){
        for(int j=i+1;j<numCodes;j++){
            if(codes[i] == codes[j].substr(0,codes[i].length())){
                return false;
            }
        }
    }
    return true;
}

void printDecode(char* charSet, string* codeSet, int numCodes, string encodedStr){
    // if given coding is invalid, cout << "Bad code" << endl;
    // TODO
    bool newcode = true;
    string tmp="";
    for(int i=0;i<encodedStr.length();i++){
        if(newcode){
            tmp="";
            tmp = tmp + encodedStr[i];
            newcode = false;
        }
        else{
            tmp = tmp + encodedStr[i];
        }
        for(int j=0;j<numCodes;j++){
            if(tmp == codeSet[j]){
                cout<<charSet[j];
                newcode = true;
            }
        }
    }
}

void test1p1(){ // test for validity of isPrefixCode
    string codeSet1[4] = {"000","1","001","01"};
    string codeSet2[4] = {"00","01","10","11"};
    string codeSet3[4] = {"01","00","0","1"};
    
    cout << "For code set 1, it is " << (isPrefixCode(codeSet1,4) ? "" : "not ") << "prefix code." << endl;
    cout << "For code set 2, it is " << (isPrefixCode(codeSet2,4) ? "" : "not ") << "prefix code." << endl;
    cout << "For code set 3, it is " << (isPrefixCode(codeSet3,4) ? "" : "not ") << "prefix code." << endl;
}

void test1p2(){
    string codeSet[7] = {"001","0000","0001","010","011","10","11"};
    char nameSet[7] = {'S','I','M','P','L','E','T'};
    
    // test for decode
    printDecode(nameSet,codeSet,7,"0010000000101001110");
    cout << " ";
    printDecode(nameSet,codeSet,7,"111000111");
    cout << endl;
}

int main(){
    int x;
    cin >> x;
    if(x==0)
        test1p1();
    else{
        test1p2();
    }
    return 0;
}