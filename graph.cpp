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
            // edges to be added later.
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
        void addEdge(Edge<T> e){
            int sIndex = verList.Locate(e.start);
            int eIndex = verList.Locate(e.end);
            if(adjMatrix[sIndex][eIndex]==0) numEdge++;
            adjMatrix[sIndex][eIndex] = 1;
            if(!directed) adjMatrix[eIndex][sIndex] = 1;
        }
        void addEdge(T st, T en){
            int sIndex = verList.Locate(st);
            int eIndex = verList.Locate(en);
            if(adjMatrix[sIndex][eIndex]==0) numEdge++;
            adjMatrix[sIndex][eIndex] = 1;
            if(!directed) adjMatrix[eIndex][sIndex] = 1;
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
                    if(adjMatrix[i][j] == 1) cout << sLeft << verList.Get(i) << "," << verList.Get(j) << sRight <<endl;
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] == 1) cout << sLeft << verList.Get(i) << "," << verList.Get(j) << sRight <<endl;
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

        // Question 1
        bool isStarShaped(){
            if(numEdge!=numVer-1){
                return false;
            }
            int count1=0;
            int count2=0;
            for(int i=0;i<numVer;i++){
                int next = 0;
                for(int j=0;j<numVer;j++){
                    if(adjMatrix[i][j]==1){
                        next += 1;
                    }
                }
                if(next==1){
                    count1 += 1;
                }
                else if(next==numVer-1){
                    count2 += 1;
                    if(count2>2){
                        return false;
                    }
                }
                else return false;
            }
            return true;
        }

        // Question 2
        bool isCycleGraph(){
            //degree of each point is 2
            for(int i=0;i<numVer;i++){
                int count2 = 0;
                for(int j=0;j<numVer;j++){
                    if(adjMatrix[i][j]==1){
                        count2 += 1;
                    }
                }
                if(count2!=2){
                    return false;
                }
            }
            //is connected
            bool* visited = new bool[numVer];
            for(int i=0;i<numVer;i++){
                visited[i]=false;
            }
            LinkQueue<int> q;
            q.EnQueue(0);
            visited[0] = true;
            while(!q.IsEmpty()){
                int tmp = q.DeQueue();
                for(int i=0;i<numVer;i++){
                    if(visited[i]==false && adjMatrix[tmp][i]==1){
                        q.EnQueue(i);
                        visited[i] = true;
                    }
                }
            }
            for(int i=0;i<numVer;i++){
                if(visited[i]==false){
                    return false;
                }
            }
            return true;
        }

        // Question 3
        bool loopTest(){ // returns whether there is a cycle or not
        }

        // Question 4
        bool existsEulerianPath(){
            // is connected?
            bool* visited = new bool[numVer];
            for(int i=0;i<numVer;i++){
                visited[i]=false;
            }
            LinkQueue<int> q;
            q.EnQueue(0);
            visited[0] = true;
            while(!q.IsEmpty()){
                int tmp = q.DeQueue();
                for(int i=0;i<numVer;i++){
                    if(visited[i]==false && adjMatrix[tmp][i]==1){
                        q.EnQueue(i);
                        visited[i] = true;
                    }
                }
            }
            for(int i=0;i<numVer;i++){
                if(visited[i]==false){
                    return false;
                }
            }
            int countodd = 0;
            for(int i=0;i<numVer;i++){
                int countDegree = 0;
                for(int j=0;j<numVer;j++){
                    if(adjMatrix[i][j]==1){
                        countDegree += 1;
                    }
                }
                if(countDegree%2==1){
                    countodd += 1;
                }
            }
            if(countodd==0 || countodd==2){
                return true;
            }
            else{
                return false;
            }
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

    AMGraph<int> amg1(ver,9,edges,10);
    AMGraph<int> amg2(ver,9,edges,10,true);

    //amg1.addEdge(7,3);
    //amg1.addEdge(7,4);

    //amg2.addEdge(3,7);
    //amg2.addEdge(7,9);
    //amg2.removeEdge(6,8);

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
    printMatrix(amg2.getMatrix(),9);
    cout << "BFS:" << endl;
    amg2.printBFS();
    cout << "DFS:" << endl;
    amg2.printDFS();

    cout << "Below is demonstration for powers of Adjacency matrix (for graph 1)" << endl;
    int** amg1_m1 = amg1.getMatrix();
    int** amg1_m2 = mulMatrix(amg1_m1,amg1_m1,9);
    int** amg1_m3 = mulMatrix(amg1_m1,amg1_m2,9);
    int** amg1_m4 = mulMatrix(amg1_m1,amg1_m3,9);
    int** amg1_m5 = mulMatrix(amg1_m1,amg1_m4,9);
    int** amg1_m6 = mulMatrix(amg1_m1,amg1_m5,9);
    int** amg1_m7 = mulMatrix(amg1_m1,amg1_m6,9);
    int** amg1_m8 = mulMatrix(amg1_m1,amg1_m7,9);
    int** amg1_m9 = mulMatrix(amg1_m1,amg1_m8,9);
    int** result = addMatrix(amg1_m1,amg1_m2,9);
    result = addMatrix(amg1_m3,result,9);
    result = addMatrix(amg1_m4,result,9);
    result = addMatrix(amg1_m5,result,9);
    result = addMatrix(amg1_m6,result,9);
    result = addMatrix(amg1_m7,result,9);
    result = addMatrix(amg1_m8,result,9);
    result = addMatrix(amg1_m9,result,9);
    printMatrix(result,9);
}

void test1(){
    int tmp1[8] = {1,2,3,4,5,6,7,8};
    AMGraph<int> amg1(tmp1,8);
    for(int i=1;i<8;i++){
        amg1.addEdge(i,8);
    }
    cout << "Graph 1 is " << (amg1.isStarShaped() ? "" : "not ") << "star-shaped" << endl;

    amg1.addEdge(5,6);
    cout << "Graph 3 is " << (amg1.isStarShaped() ? "" : "not ") << "star-shaped" << endl;
}

void test2(){
    int tmp[6] = {0,1,2,3,4,5};
    AMGraph<int> amg1(tmp,6);
    for(int i=0;i<6;i++){
        amg1.addEdge(i,((i+1) % 6));
    }
    cout << "Graph 1 is " << (amg1.isCycleGraph() ? "" : "not ") << "a cycle graph" << endl;

    amg1.removeEdge(4,5);
    amg1.addEdge(4,0);
    cout << "Graph 3 is " << (amg1.isCycleGraph() ? "" : "not ") << "a cycle graph" << endl;
}

void test3(){
    char ver2[5] = {'A','B','C','D','E'};
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A','B');
    amg2.addEdge('A','D');
    amg2.addEdge('A','E');
    amg2.addEdge('B','C');
    amg2.addEdge('C','E');
    amg2.addEdge('D','C');
    amg2.addEdge('D','E');

    cout << "Are there loops in this graph? " << (amg2.loopTest() ? "Yes" : "No") << endl;

    amg2.addEdge('E','A');
    cout << "Are there loops in this graph? " << (amg2.loopTest() ? "Yes" : "No") << endl;

    int ver[9] = {5,6,7,8,9,1,2,3,4};
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

    AMGraph<int> amg1(ver,9,edges,10);
    cout << "Are there loops in this graph? " << (amg1.loopTest() ? "Yes" : "No") << endl;

}

void test4(){
    int ver[9] = {5,6,7,8,9,1,2,3,4};
    AMGraph<int> amg0(ver,9);
    cout << "Eulerian path? " << (amg0.existsEulerianPath() ? "Yes" : "No") << endl;
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
    AMGraph<int> amg05(ver,9, edges, 5);
    cout << "Eulerian path? " << (amg05.existsEulerianPath() ? "Yes" : "No") << endl;

    AMGraph<int> amg1(ver,9,edges,10);
    cout << "Eulerian path? " << (amg1.existsEulerianPath() ? "Yes" : "No") << endl;
}

int main(){
    //test0();
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}

