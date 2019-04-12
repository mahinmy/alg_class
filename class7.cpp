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

        // ques 1
        // copy tree
        /*BinTree(const BinTree<T>& rhs){
            // TODO
           data=rhs.data;
           if(rhs.left!=NULL){
                left=new BinTree<T>(*(rhs.left));
           }
           else if(rhs.left==NULL) left=NULL;
           if(rhs.right!=NULL){
                right=new BinTree<T>(*(rhs.right));
           }
           else if(rhs.right==NULL) right=NULL;
        }*/


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

        // ques 2
        int leafNodeCount(){
            // TODO
            int count=0;
            if(left==NULL&&right==NULL){
                count++;
            }
            else if(left!=NULL&&right==NULL){
                count=left->leafNodeCount();
            }
            else if(left==NULL&&right!=NULL){
                count=right->leafNodeCount();
            }
            else if(left!=NULL&&right!=NULL){
                count=right->leafNodeCount()+left->leafNodeCount();
            }
            return count;
        }

        // ques 3
        T weightedPathLength(){
            LinkQueue<BinTree<T> *> q;
            int length = 0;
            q.EnQueue(this);
            length += 1;
            T sum=0;
            int height = 0;
            while(length != 0){
                int l = length;
                for(int i = 0;i < l;i++){
                    BinTree<T> *tmp = q.DeQueue();
                    length -= 1;
                    if(tmp->left == NULL && tmp->right == NULL){
                        sum = sum + height * tmp->data;
                    }
                    else if(tmp->left != NULL && tmp->right == NULL){
                        q.EnQueue(tmp->left);
                        length += 1;
                    }
                    else if(tmp->left == NULL && tmp->right != NULL){
                        q.EnQueue(tmp->right);
                        length += 1;
                    }
                    else if(tmp->left != NULL && tmp->right != NULL){
                        q.EnQueue(tmp->left);
                        q.EnQueue(tmp->right);
                        length += 2;
                    }
                }
                height++;
            }
            return sum;
            
        }

        // ques 4
        bool isComplete(){ //check if the tree is a complete binary tree
            LinkQueue<BinTree<T> *> q;
            q.EnQueue(this);
            bool nullOrNot = false;
            BinTree<T> * tmp;
            while(!q.IsEmpty()){
                tmp = q.DeQueue();
                if(nullOrNot){
                    if(tmp->left != NULL || tmp->right != NULL){
                        return false;
                    }
                }
                if((tmp->left == NULL || tmp->right == NULL) && !nullOrNot){
                    nullOrNot = true;
                    if(tmp->left == NULL && tmp->right != NULL){
                        return false;
                    }
                }
                if(tmp->left!=NULL) q.EnQueue(tmp->left);
                if(tmp->right!=NULL) q.EnQueue(tmp->right);
            }
            return true;
        }
};

template <class T>
BinTree<T>* buildFromPreIn(T* preArr, T* inArr, int n){
    //pre第一个节点是根节点
    T root = preArr[0];
    BinTree<T> *q = new BinTree<T>(root);
    //找到根结点在inarr出现的位置
    int posRoot;
    for(posRoot = 0;posRoot<n;posRoot++){
        if(inArr[posRoot] == root)
            break;
    }
    //中序根结点左边的东西就是左子树，如果为空，左子树不干活
    if(posRoot==0)
        ;
    else{
        T* leftIn = new T[posRoot];
        for(int i=0;i<posRoot;i++){
            leftIn[i]=inArr[i];
        }
        //前序的前同样多个位置就是左子树的前序数组，根结点除外
        T* leftPre = new T[posRoot];
        for(int i=0;i<posRoot;i++){
            leftPre[i]=preArr[i+1];
        }
        BinTree<T> *leftChild = buildFromPreIn(leftPre,leftIn,posRoot);
        q->addLChild(leftChild);
    }
    //右子树情况：根结点后面的就是右子树
    if(posRoot == n-1)
        ;
    else{
        T* rightIn = new T[n - posRoot - 1];
        for(int i=posRoot+1;i<n;i++){
            rightIn[i-posRoot-1]=inArr[i];
        }
        //前序的前同样多个位置就是左子树的前序数组，根结点除外
        T* rightPre = new T[n - posRoot - 1];
        for(int i=posRoot+1;i<n;i++){
            rightPre[i-posRoot-1]=preArr[i];
        }
        BinTree<T> *rightChild = buildFromPreIn(rightPre,rightIn,n-posRoot-1);
        q->addRChild(rightChild);
    }
    return q;
}
void test0(){
    BinTree<char> * treeA = new BinTree<char>('A');
    treeA->addLChild('B');
    treeA->addRChild('C');
    BinTree<char> *treeB, *treeC, *treeD;
    treeB = treeA->getLChild();
    treeC = treeA->getRChild();
    treeB->addLChild('D');
    treeD = treeB->getLChild();
    treeD->addRChild('G');
    treeC->addLChild('E');
    treeC->addRChild('F');

    treeA->printPreOrderR();
    cout << endl;
    treeA->printInOrderR();
    cout << endl;
    treeA->printPostOrderR();
    cout << endl;
    treeA->printLevelOrder();
    cout << endl;
}

void test1(){
    BinTree<char> * treeA = new BinTree<char>('A');
    treeA->addLChild('B');
    treeA->addRChild('C');
    BinTree<char> *treeB, *treeC, *treeD;
    treeB = treeA->getLChild();
    treeC = treeA->getRChild();
    treeB->addLChild('D');
    treeD = treeB->getLChild();
    treeD->addRChild('G');
    treeC->addLChild('E');
    treeC->addRChild('F');

    treeA->printPreOrderR();
    cout << endl;
    treeA->printInOrderR();
    cout << endl;
    treeA->printPostOrderR();
    cout << endl;
    treeA->printLevelOrder();
    cout << endl;

    BinTree<char> * treeH = new BinTree<char>(*treeA);
    treeH->setData('H');
    treeA->printPreOrderR();
    cout << endl;
    treeA->printInOrderR();
    cout << endl;
    treeA->printPostOrderR();
    cout << endl;
    treeA->printLevelOrder();
    cout << endl;
    treeH->printPreOrderR();
    cout << endl;
    treeH->printInOrderR();
    cout << endl;
    treeH->printPostOrderR();
    cout << endl;
    treeH->printLevelOrder();
    cout << endl;
}

void test2(){
    BinTree<char> * treeA = new BinTree<char>('A');
    treeA->addLChild('B');
    treeA->addRChild('C');
    BinTree<char> *treeB, *treeC, *treeD;
    treeB = treeA->getLChild();
    treeC = treeA->getRChild();
    treeB->addLChild('D');
    treeD = treeB->getLChild();
    treeD->addRChild('G');
    treeC->addLChild('E');
    treeC->addRChild('F');
    cout << treeA->leafNodeCount() << endl;
}

void test3(){
    BinTree<int> *treeK = new BinTree<int>(1);
    treeK->addLChild(2);
    treeK->addRChild(3);
    treeK->getLChild()->addLChild(4);
    treeK->getLChild()->addRChild(5);
    treeK->getRChild()->addLChild(6);
    treeK->getRChild()->addRChild(7);
    treeK->getLChild()->getLChild()->addLChild(8);
    treeK->getLChild()->getLChild()->addRChild(9);
    cout << treeK->weightedPathLength() << endl;
}

void test4(){
    BinTree<int> *treeK = new BinTree<int>(1);
    treeK->addLChild(2);
    treeK->addRChild(3);
    treeK->getLChild()->addLChild(4);
    treeK->getLChild()->addRChild(5);
    treeK->getRChild()->addLChild(6);
    treeK->getRChild()->addRChild(7);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";

    treeK->getLChild()->getLChild()->addLChild(8);
    treeK->getLChild()->getLChild()->addRChild(9);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";

    treeK->getLChild()->getRChild()->addRChild(11);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";

    treeK->getLChild()->getLChild()->getLChild()->addLChild(16);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
}

void test5(){
    int pre[9]={1,2,3,4,5,6,7,8,9};
    int mid[9]={2,3,1,5,4,7,8,6,9};
    BinTree<int> *q = buildFromPreIn(pre,mid,9);
    q->printPreOrderR();
    cout<<endl;
    q->printInOrderR();
}
int main(){
    test5();
    return 0;
}

