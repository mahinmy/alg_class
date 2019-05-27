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
int getMax(int* a,int x,int m,int **M){
    int max=0;
    for(int i=0;i<m;i++){
        if(M[i][x]!=0&&M[i][x]+a[i]>max){
            max=M[i][x]+a[i];
        }
    }
    return max;
}

template <class T>
struct Edge{
    T start;
    T end;
};

template <class T>
class AMGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    private:
        int numVer, numEdge;
        VecList<T> verList; // list of vertices
        int** adjMatrix;
        bool directed;

        //helper BFS
        void printBFShelp(int vInd, bool* visited){
            LinkQueue<int> q;
            q.EnQueue(vInd);
            cout << verList.Get(vInd) << " ";
            visited[vInd] = true;
            while(!q.IsEmpty()){
                int tmp = q.DeQueue();
                for(int i=0;i<numVer;i++){
                    if(adjMatrix[tmp][i]!=0 && !visited[i]){
                        cout << verList.Get(i) << " ";
                        visited[i] = true;
                        q.EnQueue(i);
                    }
                }
            }
        }
        //helper DFS
        void printDFShelp(int vInd, bool* visited){
            cout << verList.Get(vInd) << " ";
            visited[vInd] = true;
            for(int i=0;i<numVer;i++){
                if(adjMatrix[vInd][i]!=0 && !visited[i]){
                    printDFShelp(i,visited);
                }
            }
        }
    public:
        AMGraph(){ // we don't want this used.
        }
        AMGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.
            adjMatrix = new int*[n];
            for(int i=0;i<n;i++){
                adjMatrix[i] = new int[n];
            }
            directed = dir;
            numVer = n;
            numEdge = 0;
            for(int i=0;i<n;i++){
                verList.InsertLast(arr[i]);
                for(int j=0;j<n;j++){
                    adjMatrix[i][j] = 0;
                }
            }
        }
        AMGraph(T* arr, int n, Edge<T>** eArr, int e,bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edge weights are all set to 1 here.
            adjMatrix = new int*[n];
            for(int i=0;i<n;i++){
                adjMatrix[i] = new int[n];
            }
            directed = dir;
            numVer = n;
            numEdge = e;
            for(int i=0;i<n;i++){
                verList.InsertLast(arr[i]);
                for(int j=0;j<n;j++){
                    adjMatrix[i][j] = 0;
                }
            }
            for(int i=0;i<e;i++){
                int sIndex = verList.Locate(eArr[i]->start);
                int eIndex = verList.Locate(eArr[i]->end);
                adjMatrix[sIndex][eIndex] = 1;
                if(!directed) adjMatrix[eIndex][sIndex] = 1;
            }
        }
        ~AMGraph(){
            for(int i=0;i<numVer;i++){
                delete [] adjMatrix[i];
            }
            delete [] adjMatrix;
        }
        void addEdge(Edge<T> e, int weight=1){
            int sIndex = verList.Locate(e.start);
            int eIndex = verList.Locate(e.end);
            if(adjMatrix[sIndex][eIndex]==0) numEdge++;
            adjMatrix[sIndex][eIndex] = weight;
            if(!directed) adjMatrix[eIndex][sIndex] = weight;
        }
        void addEdge(T st, T en, int weight=1){
            int sIndex = verList.Locate(st);
            int eIndex = verList.Locate(en);
            if(adjMatrix[sIndex][eIndex]==0) numEdge++;
            adjMatrix[sIndex][eIndex] = weight;
            if(!directed) adjMatrix[eIndex][sIndex] = weight;
        }
        void removeEdge(Edge<T> e){
            int sIndex = verList.Locate(e.start);
            int eIndex = verList.Locate(e.end);
            if(adjMatrix[sIndex][eIndex]==1) numEdge--;
            adjMatrix[sIndex][eIndex] = 0;
            if(!directed) adjMatrix[eIndex][sIndex] = 0;

        }
        void removeEdge(T st, T en){
            int sIndex = verList.Locate(st);
            int eIndex = verList.Locate(en);
            if(adjMatrix[sIndex][eIndex]==1) numEdge--;
            adjMatrix[sIndex][eIndex] = 0;
            if(!directed) adjMatrix[eIndex][sIndex] = 0;
        }
        void printGraph(){
            cout << "Vertices:" << endl;
            for(int i=0;i<numVer;i++)
                cout << verList.Get(i) << " ";
            cout << endl << "Edges:" << endl;
            char sLeft = (directed ? '<' : '(');
            char sRight = (directed ? '>' : ')');
            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.Get(i) << "," << verList.Get(j) << sRight << ", weight = " << adjMatrix[i][j] <<endl;
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.Get(i) << "," << verList.Get(j) << sRight << ", weight = " << adjMatrix[i][j] <<endl;
                }
            }
        }
        int** getMatrix(){
            return adjMatrix;
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
        void printBonus(){
            int* arr=new int[numVer];
            for(int i=0;i<numVer;i++){
                arr[i]=0;
            }
            int* inDeg = new int[numVer];
            bool* printed = new bool[numVer];
            for(int i=0;i<numVer;i++){
                inDeg[i] = 0;
                printed[i] = false;
                for(int j=0;j<numVer;j++){
                    inDeg[i] += (adjMatrix[j][i] > 0 ? 1 : 0);
                }
            }

            bool newAdd = false;
            int nodeCount = 0;
            LinkQueue<T> q; //add the printables to the queue
            do{
                newAdd = false;
                for(int i=0;i<numVer;i++){
                    if(!printed[i] && inDeg[i]==0){ //found our next printable
                        q.EnQueue(verList.Get(i));
                        nodeCount++;
                        newAdd = true;
                        printed[i]= true;
                        //update the other in-degrees
                        for(int j=0;j<numVer;j++){
                            if(printed[j] || adjMatrix[i][j] == 0) continue;
                            inDeg[j]--;
                        }
                    }
                }
            }while(newAdd);
            if(nodeCount!=numVer){
                cout<<"No possible solution!"<<endl;
                return;
            }
            arr[verList.Locate(q.DeQueue())]=0;
            while(!q.IsEmpty()){
                int k=verList.Locate(q.DeQueue());
                arr[k]=getMax(arr,k,numVer,adjMatrix);
            }
            cout<<"Results:"<<endl;
            cout<<"Person    Pay"<<endl;
            for(int i=0;i<numVer;i++){
                cout<<left<<setw(10)<<i+1;
                cout<<arr[i];
                cout<<endl;
             }
        }
        //Topo
        void printTopo(){ //directed graphs only
            if(!directed){
                cout << "Directed graphs only!" << endl;
                return;
            }
            // for each node, get the in-degrees and print status.
            int* inDeg = new int[numVer];
            bool* printed = new bool[numVer];
            for(int i=0;i<numVer;i++){
                inDeg[i] = 0;
                printed[i] = false;
                for(int j=0;j<numVer;j++){
                    inDeg[i] += (adjMatrix[j][i] > 0 ? 1 : 0);
                }
            }

            bool newAdd = false;
            int nodeCount = 0;
            LinkQueue<T> q; //add the printables to the queue
            do{
                newAdd = false;
                for(int i=0;i<numVer;i++){
                    if(!printed[i] && inDeg[i]==0){ //found our next printable
                        q.EnQueue(verList.Get(i));
                        nodeCount++;
                        newAdd = true;
                        printed[i]= true;
                        //update the other in-degrees
                        for(int j=0;j<numVer;j++){
                            if(printed[j] || adjMatrix[i][j] == 0) continue;
                            inDeg[j]--;
                        }
                    }
                }
            }while(newAdd);
            if(nodeCount!=numVer){
                cout << "Loop detected" << endl;
                return;
            }
            cout << "Topo order: ";
            while(!q.IsEmpty())
                cout << q.DeQueue() << " ";
            cout << endl;
        }
};

// put something that multiplies matrix, just for demonstrating meaning of A^k
// another that multiplies matrix.
template <class T>
void printMatrix(T** mat, int n){
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



int main(){
    //testTopo();
    int n,m;
    int p,q,r;
    cin>>m>>n;
    int *arr=new int[m];
   // int *arr1=new int[m];
    for(int i=0;i<m;i++){
        arr[i]=i+1;
       // arr1[i]=0;
    }
    AMGraph<int> *Graph=new AMGraph<int>(arr,m,true);
    for(int j=0;j<n;j++){
        cin>>p>>q>>r;
        Graph->addEdge(p,q,r);
    }
    Graph->printBonus();
    return 0;
}


