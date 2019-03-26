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

    void Set(int i, T x){
        Node<T> *p = first;
        int count=-1;
        if(i<0) throw "Bad index";
        while(p!=NULL && count < i){ //seek (i-1)-th point
            p = p-> next;
            count++;
        }
        if(p==NULL) throw "Bad index";
        else{
            p->data = x;
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

// Maybe useful?
template <class T>
struct SNode{
    int row;
    int col;
    T data;
};

// In the class below, we assume it is meaningful to put 0 as a value for the type T.
template <class T>
class SparseMatrix{
    private:
        LinkList<SNode<T>*> *l=new LinkList<SNode<T>*>();
        int row,col;
    public:
        SparseMatrix(){
            row=10;
            col=10;
        }
        SparseMatrix(int r, int c){
            row=r;
            col=c;
        }
        ~SparseMatrix(){
            for(int i=0;i<l->Length();i++)
                l->Delete(0);
            delete l;
        }
        void setEntry(int rPos, int cPos, T x){
        	if(x==0) return;
            for(int i=0;i<l->Length();i++){
                if(l->Get(i)->row==rPos && l->Get(i)->col==cPos){
                    l->Get(i)->data = x;
                    return;
                }
            }
            SNode<T> *tmp;
            tmp=new SNode<T>;
            tmp->data=x;
            tmp->row=rPos;
            tmp->col=cPos;
            l->InsertLast(tmp);
        }
        T getEntry(int rPos, int cPos){
            for(int i=0;i<l->Length();i++){
                if(l->Get(i)->row==rPos && l->Get(i)->col==cPos){
                    return l->Get(i)->data;
                }
            }
            return 0;
        }
        int getCol(){
        	return col;
        }
        int getRow(){
        	return row;
        }
        LinkList<SNode<T>*> *getList(){
        	return l;
        }
        SparseMatrix<T> * add(SparseMatrix<T> * B){
        	SparseMatrix<T> * K=new SparseMatrix<T>(B->getRow(),B->getCol());
        	for(int i=0;i<B->getList()->Length();i++){
        		SNode<T> *nodeK=B->getList()->Get(i);
        		int colK=nodeK->col;
        		int rowK=nodeK->row;
        		T dataK=nodeK->data;
        		K->setEntry(rowK,colK,dataK);
        	}//deep copy
            if(row==B->getRow() && col==K->getCol()){
                SparseMatrix<T> *c=new SparseMatrix<T>(row,col);
                T dataC;
                int rowB,colB,rowC,colC;
                LinkList<SNode<T>*> *bList=K->getList();
                for(int i=0;i<l->Length();i++){
                    SNode<T>* tmpA;
                    tmpA=l->Get(i);
                    int rowA=tmpA->row,colA=tmpA->col;
                    
                    bool findPair=false;
                    for(int j=0;j<bList->Length();j++){
                        rowB=bList->Get(j)->row;
                        colB=bList->Get(j)->col;
                        if(rowA==rowB && colA==colB){
                            rowC=rowA;
                            colC=colA;
                            dataC=l->Get(i)->data+bList->Get(j)->data;
                            bList->Delete(j);
                            findPair=true;
                            break;
                        }
                    }
                    if(!findPair){
                        rowC=rowA;
                        colC=colA;
                        dataC=l->Get(i)->data;
                    }
                    c->setEntry(rowC,colC,dataC);
                }
                while(bList->Length()!=0){
                	SNode<T> *nodeC=bList->Delete(0);
                	rowC=nodeC->row;
                	colC=nodeC->col;
                	dataC=nodeC->data;
                	c->setEntry(rowC,colC,dataC);
                }
                return c;
            }
            else throw "Matrices have different sizes";
        }
        SparseMatrix<T> * subtract(SparseMatrix<T> * B){
        	SparseMatrix<T> * K=new SparseMatrix<T>(B->getRow(),B->getCol());
        	for(int i=0;i<B->getList()->Length();i++){
        		SNode<T> *nodeK=B->getList()->Get(i);
        		int colK=nodeK->col;
        		int rowK=nodeK->row;
        		T dataK=nodeK->data;
        		K->setEntry(rowK,colK,dataK);
        	}//deep copy
			if(row==K->getRow() && col==K->getCol()){
                SparseMatrix<T> *c=new SparseMatrix<T>(row,col);
                T dataC;
                int rowB,colB,rowC,colC;
                LinkList<SNode<T>*> *bList=K->getList();
                for(int i=0;i<l->Length();i++){
                    SNode<T>* tmpA;
                    tmpA=l->Get(i);
                    int rowA=tmpA->row,colA=tmpA->col;
                    bool findPair=false;
                    for(int j=0;j<bList->Length();j++){
                        rowB=bList->Get(j)->row;
                        colB=bList->Get(j)->col;
                        if(rowA==rowB && colA==colB){
                            rowC=rowA;
                            colC=colA;
                            dataC=(l->Get(i)->data)-(bList->Get(j)->data);
                            bList->Delete(j);
                            findPair=true;
                            break;
                        }
                    }
                    if(!findPair){
                        rowC=rowA;
                        colC=colA;
                        dataC=l->Get(i)->data;
                    }
                    c->setEntry(rowC,colC,dataC);
                }
                while(bList->Length()!=0){
                	SNode<T> *nodeC=bList->Delete(0);
                	rowC=nodeC->row;
                	colC=nodeC->col;
                	dataC=-(nodeC->data);
                	c->setEntry(rowC,colC,dataC);
                }
                return c;
            }
            else throw "Matrices have different sizes";
        }
        /*SparseMatrix<T> * multiply(SparseMatrix<T> * B){
            //perform multiplication if the sizes of the matrices are compatible.
        }

        SparseMatrix<T> * transpose(){
            // return the transpose of this matrix
            // If you have time, think about it.
            // There is the subtlety of entry duplication here.
        }
        */

        // Only call this function if you know the size of matrix is reasonable.
        void printMatrix(){
        	T a[row][col];
        	for(int i=0;i<row;i++){
        		for(int j=0;j<col;j++)
        			a[i][j]=0;
        	}
        	for(int i=0;i<l->Length();i++){
        		int dataCol=l->Get(i)->col,dataRow=l->Get(i)->row;
        		T this_data=l->Get(i)->data;
        		a[dataRow][dataCol]=this_data;
        	}
        	for(int i=0;i<row;i++){
        		for(int j=0;j<col;j++){
        			cout<<a[i][j]<<" ";
        		}
        		cout<<endl;
        	}
        }

        //This is for printing only non-zero entries
        void printNZMatrix(){
        	for(int i=0;i<l->Length();i++){
        		int dataCol=l->Get(i)->col,dataRow=l->Get(i)->row;
        		T this_data=l->Get(i)->data;
        		cout<<dataRow<<" "<<dataCol<<" "<<this_data<<endl;
        	}
        }
};

int main(){
    SparseMatrix<int> X, Y;
    X.setEntry(1,3,4);
    X.setEntry(7,8,2);
    Y.setEntry(1,6,4);
    Y.setEntry(1,3,4);
    Y.setEntry(7,7,2);
    X.printMatrix();
    cout << endl;
    Y.printMatrix();
    cout << endl;
    X.add(&Y)->printMatrix();
    cout << endl;
    X.subtract(&Y)->printMatrix();
    SparseMatrix<int> A(100000,100000), B(100000,100000);
    for(int i=0;i<3;i++){
        A.setEntry(30000*i,40000*i,i);
        B.setEntry(20000+10000*i,50000-10000*i,i);
    }
    cout<<"A"<<endl;
    A.printNZMatrix();
    cout<<"B"<<endl;
    B.printNZMatrix();
    cout<<"A+B"<<endl;
    A.add(&B)->printNZMatrix();
    cout<<"A-B"<<endl;
    A.subtract(&B)->printNZMatrix();
    cout<<X.getEntry(1,3)<<endl;
    SparseMatrix<int> C(2,3);
    C.setEntry(1,2,3);
    C.printMatrix();
    return 0;
}

