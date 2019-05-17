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
        void printBFShelp(int vInd, bool* &visited){
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
        void printDFShelp(int vInd, bool* &visited){
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
        LGraph(bool dir){
            numVer = 0;
            directed = dir;
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

        //print result of Dijkstra's algorithm, but starting at vertex 'start'
        void printDijkstra(T start){
            bool* isInS = new bool[numVer];
            int* curDist = new int[numVer];
            int* prevNodeIndex = new int[numVer];
            int lastVisit = verList.Locate(start); //last thing we visited
            int count = 0; //number of nodes in set S
            for(int i=0;i<numVer;i++){
                isInS[i] = false;
                curDist[i] = -1; //negative distance to denote unreachable
                prevNodeIndex[i] = -1; //no previous node yet.
            }
            isInS[lastVisit] = true;
            curDist[lastVisit] = 0;
            count =1;
            
            while(count < numVer){
                //update the distances, and track the smallest at the same time
                int min = -1; //minimum distance
                int minNodeIndex = -1; //min Node
                cout << "Last visited node: " << verList.Get(lastVisit) << endl;
                for(int i=0;i<numVer;i++){
                    if(!isInS[i] && adjMatrix[lastVisit][i]>0){ //note that now the direction of edge is important!
                        if(curDist[i]==-1 || (curDist[i] > curDist[lastVisit] + adjMatrix[lastVisit][i])){
                            curDist[i] = curDist[lastVisit] + adjMatrix[lastVisit][i];
                            prevNodeIndex[i] = lastVisit;
                            cout << "Updated distance at node: " << verList.Get(i) << endl;
                        }
                        
                    }
                    if(!isInS[i] && curDist[i]!=-1 && (min==-1 || (curDist[i] < min))){
                        min = curDist[i];
                        minNodeIndex = i;
                    }
                }
                //at this moment, distances updated and minimum is ready.
                if(min==-1)
                    count = numVer; //this is to say we are done, since the rest of the nodes are not reachable
                else{
                    cout << "Selected node " << verList.Get(minNodeIndex) << endl;
                    isInS[minNodeIndex] = true; //put the min Node into the list, and go again.
                    lastVisit = minNodeIndex;
                    count++;
                }
            }
            
            //print the results
            cout << left << setw(18) << "Vertice name" << "Path" << endl;
            for(int i=0;i<numVer;i++){
                if(curDist[i]==-1){
                    cout << left << setw(18) << verList.Get(i) << "Unreachable" << endl;
                    continue;
                }
                LinkStack<int> pathStack;
                pathStack.Push(i);
                while(prevNodeIndex[pathStack.GetTop()]!=-1)
                    pathStack.Push(prevNodeIndex[pathStack.GetTop()]);
                cout << left << setw(18) << verList.Get(i);
                
                bool first = true;
                while(!pathStack.IsEmpty()){
                    if(first){
                        cout << verList.Get(pathStack.Pop());
                        first = false;
                    }
                    else{
                        cout << " -> " << verList.Get(pathStack.Pop());
                    }
                }
                cout << ", cost = " << curDist[i] << endl;
            }
        }
        
        int** distances(){ //tmpMat[i][j] = -1 if we can't reach from i to j
            int** tmpMat = new int*[numVer];
            for(int i=0;i<numVer;i++){
                tmpMat[i] = new int[numVer];
                for(int j=0;j<numVer;j++){
                    tmpMat[i][j] = (adjMatrix[i][j]!=0? adjMatrix[i][j] : -1);
                }
                tmpMat[i][i] = 0;
            }
            
            //above is when we use no intermediate points.
            //below is where we start to use intermediate points, expanding the set of intermediate points we use as we go.
            for(int k=0;k<numVer;k++)
                for(int i=0;i<numVer;i++){
                    if(tmpMat[i][k]==-1) continue;
                    for(int j=0;j<numVer;j++){
                        if(tmpMat[k][j]==-1) continue;
                        if(tmpMat[i][j]==-1 || tmpMat[i][j] > tmpMat[i][k] + tmpMat[k][j])
                            tmpMat[i][j] = tmpMat[i][k] + tmpMat[k][j];
                    }
                }
            
            return tmpMat;
        }
        
        T** preNodeDist(T bad){ //tmpMat[i][j] = -1 if we can't reach from i to j
            T** tmpT = new T*[numVer];
            int** tmpMat = new int*[numVer];
            for(int i=0;i<numVer;i++){
                tmpT[i] = new T[numVer];
                tmpMat[i] = new int[numVer];
                for(int j=0;j<numVer;j++){
                    tmpMat[i][j] = (adjMatrix[i][j]!=0? adjMatrix[i][j] : -1);
                    tmpT[i][j] = (adjMatrix[i][j]!=0? verList.Get(i) : bad);
                }
                tmpMat[i][i] = 0;
            }
            
            //above is when we use no intermediate points.
            //below is where we start to use intermediate points, expanding the set of intermediate points we use as we go.
            for(int k=0;k<numVer;k++)
                for(int i=0;i<numVer;i++){
                    if(tmpMat[i][k]==-1) continue;
                    for(int j=0;j<numVer;j++){
                        if(tmpMat[k][j]==-1) continue;
                        if(tmpMat[i][j]==-1 || tmpMat[i][j] > tmpMat[i][k] + tmpMat[k][j]){
                            tmpMat[i][j] = tmpMat[i][k] + tmpMat[k][j];
                            tmpT[i][j] = tmpT[k][j];
                        }
                    }
                }
                
            for(int i=0;i<numVer;i++){
                delete[] tmpMat[i];
            }
            delete[] tmpMat;
            
            return tmpT;
        }
        
        // Question 1:
        void distFromAllTo(T end){
            bool* isInS = new bool[numVer];
            int* curDist = new int[numVer];
            int* prevNodeIndex = new int[numVer];
            int lastVisit = verList.Locate(end); //last thing we visited
            int count = 0; //number of nodes in set S
            for(int i=0;i<numVer;i++){
                isInS[i] = false;
                curDist[i] = -1; //negative distance to denote unreachable
                prevNodeIndex[i] = -1; //no previous node yet.
            }
            isInS[lastVisit] = true;
            curDist[lastVisit] = 0;
            count =1;

            while(count < numVer){
                //update the distances, and track the smallest at the same time
                int min = -1; //minimum distance
                int minNodeIndex = -1; //min Node
                //cout << "Last visited node: " << verList.Get(lastVisit) << endl;
                for(int i=0;i<numVer;i++){
                    if(!isInS[i] && adjMatrix[i][lastVisit]>0){ //note that now the direction of edge is important!
                        if(curDist[i]==-1 || (curDist[i] > curDist[lastVisit] + adjMatrix[i][lastVisit])){
                            curDist[i] = curDist[lastVisit] + adjMatrix[i][lastVisit];
                            prevNodeIndex[i] = lastVisit;
                            //cout << "Updated distance at node: " << verList.Get(i) << endl;
                        }

                    }
                    if(!isInS[i] && curDist[i]!=-1 && (min==-1 || (curDist[i] < min))){
                        min = curDist[i];
                        minNodeIndex = i;
                    }
                }
                //at this moment, distances updated and minimum is ready.
                if(min==-1)
                    count = numVer; //this is to say we are done, since the rest of the nodes are not reachable
                else{
                    //cout << "Selected node " << verList.Get(minNodeIndex) << endl;
                    isInS[minNodeIndex] = true; //put the min Node into the list, and go again.
                    lastVisit = minNodeIndex;
                    count++;
                }
            }

            //print the results
            cout << left << setw(18) << "Vertice name" << "Path" << endl;
            for(int i=0;i<numVer;i++){
                if(curDist[i]==-1){
                    cout << left << setw(18) << verList.Get(i) << "Unreachable" << endl;
                    continue;
                }
                LinkStack<int> pathStack;
                pathStack.Push(i);
                while(prevNodeIndex[pathStack.GetTop()]!=-1)
                    pathStack.Push(prevNodeIndex[pathStack.GetTop()]);
                cout << left << setw(18) << verList.Get(i);

                bool first = true;
                LinkStack<int> pathStack2;
                while(!pathStack.IsEmpty()){
                    pathStack2.Push(pathStack.Pop());
                }
                while(!pathStack2.IsEmpty()){
                    if(first){
                        cout << verList.Get(pathStack2.Pop());
                        first = false;
                    }
                    else{
                        cout << " -> " << verList.Get(pathStack2.Pop());
                    }
                }
                cout << ", cost = " << curDist[i] << endl;
            }
        }
        
        // Question 2
        // Make an equivalent LGraph from current AMGraph:
        // assume unweighted graph
        LGraph<T>* getLGraph(){
            // TODO
            int i,j;
            LGraph<T>* lgr = new LGraph<T>(directed);
            for(i=0;i< numVer;i++){
                lgr->addVertex(verList.Get(i));
            }
            for(i=0;i<numVer;i++){
                for(j=0;j<numVer;j++){
                    if(adjMatrix[i][j]!=0){
                        lgr->addEdge(verList.Get(i),verList.Get(j));
                    }
                }
            }
            return lgr;
        }
        
        // Question 3
        // Make a line graph (aka vertex-to-edge dual) of the original graph
        // Assume undirected, unweighted.
        // Edges appear in the row-first order when viewed as element in adjacency matrix.
        // Label the edges just as 1,2,3,...
        AMGraph<int>* getLineGraph(){
            // TODO
            int *verArr = new int[numEdge];
            for(int i=1;i<=numEdge;i++){
                verArr[i-1]=i;
            }
            AMGraph<int>* g;
            g = new AMGraph<int>(verArr, numEdge);
            int point1 = 1, point2 = 2;
            for (int i1 = 0; i1 < numVer; i1++){
                for(int j1 = i1+1; j1 < numVer; j1++){
                    if(adjMatrix[i1][j1]==0) continue;
                    //find the next positions of adjMatrix[i1][j1] 
                    int next1, next2;
                    next1 = i1;
                    next2 = j1 + 1;
                    if(next2 == numVer){
                        next1 += 1;
                        next2 = next1 +1;
                    }
                    for(int i2 = next1; i2 < numVer; i2++){
                        bool flag = i2 == next1;
                        int j2index = flag ? next2 : i2 + 1;
                        for(int j2 = j2index; j2 < numVer; j2++){
                            if(adjMatrix[i2][j2]==0) continue;
                            if(i1 == i2 || i1 == j2 || j1 == i2 || j1 == j2){
                                g->addEdge(point1, point2);
                            }
                            point2 += 1;
                            if(point2 > numEdge){
                                point1 += 1;
                                point2 = point1 + 1;
                            }
                        }
                    }
                }
            }
            return g;
            
        }
        bool isConnected(){
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
        AMGraph<T>* criticalEdge(){
            T *dataArr = new T[numVer];
            for(int i = 0; i < numVer; i++){
                dataArr[i] = verList.Get(i);
            }
            AMGraph<T> *g = new AMGraph<T>(dataArr, numVer);
            for(int i = 0; i < numVer; i++){
                for(int j = i + 1; j < numVer; j++){
                    if(adjMatrix[i][j] != 0){
                        int w = adjMatrix[i][j];
                        this->removeEdge(verList.Get(i), verList.Get(j));
                        if(!this->isConnected()){
                            g->addEdge(verList.Get(i), verList.Get(j), w);
                        }
                        this->addEdge(verList.Get(i), verList.Get(j), w);
                    }
                }
            }
            return g;
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

void test0(){
    int ver[6] = {0,1,2,3,4,5};
    AMGraph<int> amg1(ver,6);
    amg1.addEdge(0,1,34);
    amg1.addEdge(0,5,19);
    amg1.addEdge(0,2,46);
    amg1.addEdge(5,2,25);
    amg1.addEdge(5,3,25);
    amg1.addEdge(5,4,26);
    amg1.addEdge(2,3,17);
    amg1.addEdge(3,4,38);
    amg1.addEdge(1,4,12);
    
    cout << endl << "Dijkstra starting at vertex 0: " << endl;
    amg1.printDijkstra(0);
    
    cout << endl << "All distances:" << endl;
    printMatrix(amg1.distances(),6);
    
    cout << endl << "All prev node:" << endl;
    printMatrix(amg1.preNodeDist(-1),6);
    
    char ver2[5] = {'A','B','C','D','E'};
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A','B',10);
    amg2.addEdge('A','D',30);
    amg2.addEdge('A','E',100);
    amg2.addEdge('B','C',50);
    amg2.addEdge('C','E',10);
    amg2.addEdge('D','C',20);
    amg2.addEdge('D','E',60);
    cout << endl << "Dijkstra starting at vertex A: " << endl;
    amg2.printDijkstra('A');
    
    cout << endl << "All distances:" << endl;
    printMatrix(amg2.distances(),5);
    
    cout << endl << "All prev node:" << endl;
    printMatrix(amg2.preNodeDist(' '),5);
}

void test1(){
    char ver2[5] = {'A','B','C','D','E'};
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A','B',10);
    amg2.addEdge('A','D',30);
    amg2.addEdge('A','E',100);
    amg2.addEdge('B','C',50);
    amg2.addEdge('C','E',10);
    amg2.addEdge('D','C',20);
    amg2.addEdge('D','E',60);
    cout << "Shortest paths to vertex E: " << endl;
    amg2.distFromAllTo('E');
    
    cout << endl;
}

void test2(){
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
    
    AMGraph<int> amga1(ver,9,edges,10);
    
    LGraph<int>* amg1 = amga1.getLGraph();
    
    cout << "Graph 1: " << endl;
    amg1->printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg1->getMatrix(),9);
    cout << "BFS:" << endl;
    amg1->printBFS();
    cout << "DFS:" << endl;
    amg1->printDFS();
}

void test3(){
    char ver[6] = {'A','B','C','D','E','F'};
    AMGraph<char> amg1(ver,6);
    
    amg1.addEdge('A','B');
    amg1.addEdge('B','C');
    amg1.addEdge('A','C');
    amg1.addEdge('C','D');
    amg1.addEdge('E','D');
    amg1.addEdge('F','D');
    amg1.addEdge('E','F');
    amg1.printGraph();
    amg1.criticalEdge()->printGraph();
    amg1.printGraph();
    cout << endl;
}

int main(){
    //test0();
    //test1();
    //test2();
    test3();
    return 0;
}
