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
struct Edge{
    T start;
    T end;
};

template <class T>
struct GraphNode{ // each vertex saves the outgoing edges and incoming edges
    T data;
    VecList<GraphNode<T> *>* outs;
    VecList<GraphNode<T> *>* ins;
};

template <class T>
class LGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    private:
        int numVer;
        VecList<GraphNode<T> *> verList; // list of vertices
        bool directed;

        GraphNode<T>* getVerNode(T x){
            for(int i=0;i<numVer;i++){
                if(verList.Get(i)->data==x)
                    return verList.Get(i);
            }
            return NULL;
        }

        //helper BFS
        void printBFShelp(int vInd, bool* visited){
            LinkQueue<int> q;
            q.EnQueue(vInd);
            cout << verList.Get(vInd)->data << " ";
            visited[vInd] = true;
            while(!q.IsEmpty()){
                int tmp = q.DeQueue();
                VecList<GraphNode<T> *>* vl = verList.Get(tmp)->outs;
                for(int i=0;i<vl->Length();i++){
                    int ttmp = verList.Locate(vl->Get(i));
                    if(!visited[ttmp]){
                        cout << vl->Get(i)->data << " ";
                        visited[ttmp] = true;
                        q.EnQueue(ttmp);
                    }
                }
            }
        }
        //helper DFS
        void printDFShelp(int vInd, bool* visited){
            cout << verList.Get(vInd)->data << " ";
            visited[vInd] = true;
            VecList<GraphNode<T> *>* vl = verList.Get(vInd)->outs;
            for(int i=0;i<vl->Length();i++){
                int ttmp = verList.Locate(vl->Get(i));
                if(!visited[ttmp]){
                    printDFShelp(ttmp,visited);
                }
            }
        }
    public:
        LGraph(){
            numVer = 0;
            directed = false;
        }
        LGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.
            for(int i=0;i<n;i++){
                GraphNode<T>* tmp = new GraphNode<T>;
                tmp->data = arr[i];
                tmp->outs = new VecList<GraphNode<T> *>;
                tmp->ins = new VecList<GraphNode<T> *>;
                verList.InsertLast(tmp);
            }
            directed = dir;
            numVer = n;
        }
        LGraph(T* arr, int n, Edge<T>** eArr, int e,bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.
            for(int i=0;i<n;i++){
                GraphNode<T>* tmp = new GraphNode<T>;
                tmp->data = arr[i];
                tmp->outs = new VecList<GraphNode<T> *>;
                tmp->ins = new VecList<GraphNode<T> *>;
                verList.InsertLast(tmp);
            }
            directed = dir;
            numVer = n;
            for(int i=0;i<e;i++){
                Edge<T>* e = eArr[i];
                GraphNode<T>* tmpS = getVerNode(e->start);
                GraphNode<T>* tmpE = getVerNode(e->end);
                tmpS->outs->InsertLast(tmpE);
                tmpE->ins->InsertLast(tmpS);
                if(!directed){
                    tmpE->outs->InsertLast(tmpS);
                    tmpS->ins->InsertLast(tmpE);
                }
            }
        }
        ~LGraph(){
            for(int i=numVer-1;i>=0;i--){
                GraphNode<T>* tmp = verList.Get(i);
                delete tmp->ins;
                delete tmp->outs;
                delete tmp;
            }
        }
        void addVertex(T x){
            numVer++;
            GraphNode<T>* tmp = new GraphNode<T>;
            tmp->data = x;
            tmp->outs = new VecList<GraphNode<T> *>;
            tmp->ins = new VecList<GraphNode<T> *>;
            verList.InsertLast(tmp);
        }
        void addEdge(Edge<T> e){
            GraphNode<T>* tmpS = getVerNode(e.start);
            GraphNode<T>* tmpE = getVerNode(e.end);
            if(tmpS->outs->Locate(tmpE)!=-1) return;
            tmpS->outs->InsertLast(tmpE);
            tmpE->ins->InsertLast(tmpS);
            if(!directed){
                tmpE->outs->InsertLast(tmpS);
                tmpS->ins->InsertLast(tmpE);
            }
        }
        void addEdge(T st, T en){
            GraphNode<T>* tmpS = getVerNode(st);
            GraphNode<T>* tmpE = getVerNode(en);
            if(tmpS->outs->Locate(tmpE)!=-1) return;
            tmpS->outs->InsertLast(tmpE);
            tmpE->ins->InsertLast(tmpS);
            if(!directed){
                tmpE->outs->InsertLast(tmpS);
                tmpS->ins->InsertLast(tmpE);
            }
        }
        void removeEdge(Edge<T> e){
            GraphNode<T>* tmpS = getVerNode(e.start);
            GraphNode<T>* tmpE = getVerNode(e.end);
            if(tmpS->outs->Locate(tmpE)==-1) return;
            tmpS->outs->Delete(tmpS->outs->Locate(tmpE));
            tmpE->ins->Delete(tmpE->ins->Locate(tmpS));
            if(!directed){
                tmpE->outs->Delete(tmpE->outs->Locate(tmpS));
                tmpS->ins->Delete(tmpS->ins->Locate(tmpE));
            }
        }
        void removeEdge(T st, T en){
            GraphNode<T>* tmpS = getVerNode(st);
            GraphNode<T>* tmpE = getVerNode(en);
            if(tmpS->outs->Locate(tmpE)==-1) return;
            tmpS->outs->Delete(tmpS->outs->Locate(tmpE));
            tmpE->ins->Delete(tmpE->ins->Locate(tmpS));
            if(!directed){
                tmpE->outs->Delete(tmpE->outs->Locate(tmpS));
                tmpS->ins->Delete(tmpS->ins->Locate(tmpE));
            }
        }
        void printGraph(){
            cout << "Vertices:" << endl;
            for(int i=0;i<numVer;i++)
                cout << verList.Get(i)->data << " ";
            cout << endl << "Edges:" << endl;
            for(int i=0;i<numVer;i++){
                VecList<GraphNode<T> *>* vl = verList.Get(i)->outs;
                if(!directed){
                    for(int j=0;j<vl->Length();j++){
                        if(verList.Locate(vl->Get(j)) <= i) continue;
                        else cout << "(" << verList.Get(i)->data << "," << vl->Get(j)->data << ")" << endl;
                    }
                }
                else{
                    for(int j=0;j<vl->Length();j++){
                        cout << "<" << verList.Get(i)->data << "," << vl->Get(j)->data << ">" << endl;
                    }
                }
            }
        }
        int** getMatrix(){
            int** tmp = new int*[numVer];
            for(int i=0;i<numVer;i++){
                tmp[i] = new int[numVer];
                for(int j=0;j<numVer;j++){
                    tmp[i][j]=0;
                    if(verList.Get(i)->outs->Locate(verList.Get(j))!=-1) tmp[i][j] = 1;
                }
            }
            return tmp;
        }
        //BFS
        void printBFS(){
            bool* visited = new bool[numVer];
            for(int i=0;i<numVer;i++){
                visited[i]=false;
            }
            for(int i=0;i<numVer;i++){
                if(!visited[i]) printBFShelp(i,visited);
            }
            cout << endl;
        }
        //DFS
        void printDFS(){
            bool* visited = new bool[numVer];
            for(int i=0;i<numVer;i++){
                visited[i]=false;
            }
            for(int i=0;i<numVer;i++){
                if(!visited[i]) printDFShelp(i,visited);
            }
            cout << endl;
        }

        bool Access(GraphNode<T>* st,GraphNode<T>* en){
            for(int i=0;i<st->outs->Length();i++){
                if(st->outs->Get(i)->data==en->data){
                    return true;
                }
            }
            for(int j=0;j<st->outs->Length();j++){
                if(Access(st->outs->Get(j),en)==true){
                    return true;
                }
            }
            return false;
        }
        // print strongly connected components
        void printStrongCC(){
            // assume directed graph.
            int i,j,count=0;
            bool* visited = new bool[numVer];
            for(i=0;i<numVer;i++){
                visited[i]=false;
            }
            for(i=0;i<numVer;i++){
                if(visited[i]==false){
                    if(verList.Get(i)->ins->Length()!=0&&verList.Get(i)->outs->Length()!=0){
                        LinkList<int> *L = new LinkList<int>();
                        L->InsertLast(i);
                        for(j=i+1;j<numVer;j++){
                            if(visited[j]==false&&Access(verList.Get(i),verList.Get(j))==true&&Access(verList.Get(j),verList.Get(i))==true){
                                L->InsertLast(j);
                            }
                        }
                        if(L->Length()!=0){
                            cout<<"Component "<<count<<" ";
                            count++;
                            for(int k=0;k<L->Length();k++){
                                visited[L->Get(k)]=true;
                                cout<<verList.Get(L->Get(k))->data<<" ";
                            }
                            cout<<endl;
                        }
                        delete L;
                    }
                    else {
                        cout<<"Component "<<count<<" "<<verList.Get(i)->data<<endl;
                        visited[i]=true;
                        count++;
                    }
                }
            }
            // TODO
        }
};

// put something that multiplies matrix, just for demonstrating meaning of A^k
// another that multiplies matrix.
void printMatrix(int ** mat, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << setw(7) << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// multiply 2 square matrices
int** mulMatrix(int ** mat1, int ** mat2, int n){
    int** tmp = new int*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new int[n];
        for(int j=0;j<n;j++){
            tmp[i][j] = 0;
            for(int k=0;k<n;k++){
                tmp[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return tmp;
}

int** addMatrix(int ** mat1, int ** mat2, int n){
    int** tmp = new int*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new int[n];
        for(int j=0;j<n;j++){
            tmp[i][j] = mat1[i][j]+mat2[i][j];
        }
    }
    return tmp;
}

void test0(){
    int ver[9] = {1,2,3,4,5,6,7,8,9};
    Edge<int>* edges[10];
    edges[0] = new Edge<int>{1,2};
    edges[1] = new Edge<int>{1,3};
    edges[2] = new Edge<int>{1,4};
    edges[3] = new Edge<int>{2,3};
    edges[4] = new Edge<int>{2,4};
    edges[5] = new Edge<int>{3,4};
    edges[6] = new Edge<int>{5,8};
    edges[7] = new Edge<int>{5,9};
    edges[8] = new Edge<int>{6,8};
    edges[9] = new Edge<int>{9,6};

    LGraph<int> amg1(ver,9,edges,10);
    LGraph<int> amg2(ver,9,edges,10,true);

    amg1.addEdge(7,3);
    amg1.addEdge(7,4);

    amg2.addEdge(3,7);
    amg2.addEdge(7,9);
    amg2.removeEdge(6,8);
    amg2.addVertex(10);
    amg2.addEdge(10,5);
    amg2.addVertex(11);
    amg2.addEdge(5,11);

    cout << "Graph 1: " << endl;
    amg1.printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg1.getMatrix(),9);
    cout << "BFS:" << endl;
    amg1.printBFS();
    cout << "DFS:" << endl;
    amg1.printDFS();

    cout << "Graph 2: " << endl;
    amg2.printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg2.getMatrix(),11);
    cout << "BFS:" << endl;
    amg2.printBFS();
    cout << "DFS:" << endl;
    amg2.printDFS();

}

void test1(){
    int ver[6] = {1,2,3,4,5,6};

    LGraph<int> lg1(ver,6,true);
    lg1.addEdge(1,2);
    lg1.addEdge(2,3);
    lg1.addEdge(3,4);
    lg1.addEdge(4,5);
    lg1.addEdge(5,6);

    lg1.printStrongCC();
    cout << endl;

    lg1.addEdge(3,1);
    lg1.addEdge(6,4);

    lg1.printStrongCC();
    cout << endl;
}

int main(){
    // test0();
    test1();
    return 0;
}
