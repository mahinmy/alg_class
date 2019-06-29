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

// Jug problem
class JugsTest{
    private:
        int jug1_cap;
        int jug2_cap;
        int jug1_vol;
        int jug2_vol;
        int volumeUsed;
        int moveCount;
    public:
        JugsTest(){
            // do not use this.
            // but just defaulting to 5 and 3 as capacities.
            jug1_cap = 5;
            jug2_cap = 3;
            clearAll();
        }
        JugsTest(int jug1, int jug2){
            jug1_cap = jug1;
            jug2_cap = jug2;
            clearAll();
        }
        ~JugsTest(){
            // no memory to release.
        }
        void clearAll(){
            // reset the problem.
            jug1_vol = 0;
            jug2_vol = 0;
            volumeUsed = 0;
            moveCount = 0;
        }
        void emptyJugX(int x){
            // empty jug x
            // assumes that x= 1 or x=2 only.
            moveCount += 1;
            if(x==1){
                jug1_vol = 0;
            }
            else{
                jug2_vol = 0;
            }
        }
        void fillJugX(int x){
            // fill jug x to full
            // assumes that x = 1 or x=2 only.
            moveCount += 1;
            if(x==1){
                volumeUsed += (jug1_cap - jug1_vol);
                jug1_vol = jug1_cap;
            }
            else{
                volumeUsed += (jug2_cap - jug2_vol);
                jug2_vol = jug2_cap;
            }
        }
        void pourXintoY(int x, int y){
            // pour X into Y, until Y is full or X is empty.
            // x is one of 1 or 2, and y is one of 1 or 2 as well.
            // note x!=y.
            if(x==y) return;
            moveCount += 1;
            if(x==1){
                if(jug1_vol + jug2_vol <= jug2_cap){
                    jug2_vol += jug1_vol;
                    jug1_vol = 0;
                }
                else{
                    jug1_vol -= (jug2_cap-jug2_vol);
                    jug2_vol = jug2_cap;
                }
            }
            else{
                if(jug1_vol + jug2_vol <= jug1_cap){
                    jug1_vol += jug2_vol;
                    jug2_vol = 0;
                }
                else{
                    jug2_vol -= (jug1_cap-jug1_vol);
                    jug1_vol = jug1_cap;
                }
            }
        }
        int getJugXCap(int x){
            // assume x = 1 or x= 2
            // get capacity of Jug X.
            return (x==1 ? jug1_cap : jug2_cap);
        }
        int getJugXVol(int x){
            // assume x = 1 or x = 2
            // get current volume of Jug X.
            return (x==1 ? jug1_vol : jug2_vol);
        }
        int getVolumeUsed(){
            return volumeUsed;
        }
        int getMoveCount(){
            return moveCount;
        }
        bool isJugXFull(int x){
            // assume x = 1 or x = 2
            // check whether jug x is full or not.
            if(x==1){
                return jug1_vol==jug1_cap;
            }
            else
                return jug2_vol==jug2_cap;
        }
        bool isJugXEmpty(int x){
            // assume x = 1 or x = 2
            // check wheter jug x is empty or not.
            return ((x==1 && jug1_vol==0) || (x==2 && jug2_vol==0));
        }
        bool checkJugs(int vol){
            // check if the sum of the two jugs give vol.
            return (jug1_vol + jug2_vol == vol);
        }
};
struct Vec{
    int m;
    int n;
};
Vec* Func1(int a,int b,int c){
    Vec* v=new Vec();
    int i,j;
    bool change=false;
    bool isend=false;
    if(a<b){
        int tmp=a;
        a=b;
        b=tmp;
        change=true;
    }
    for(i=0;i<=c/a;i++){
        if((c-i*a)%b==0){
            j=(c-i*a)/b;
            if(change==true){
                v->m=j;
                v->n=i;
            }
            else{
                v->m=i;
                v->n=j;
            }
            /*cout<<"m,n"<<endl;
            cout<<v->m<<" "<<v->n<<endl;*/
            return v;
        }
    }
    int t;
    j=1;t=1;
    while(!isend){
        if(j*a>=t*b){
            if((c+b*t)%a==0){
                if(change==true){
                    v->m=-t;
                    v->n=(c+b*t)/a;
                }
                else{
                    v->m=(c+b*t)/a;
                    v->n=-t;
                }
                isend=true;
                /*cout<<"m,n"<<endl;
                cout<<v->m<<" "<<v->n<<endl;*/
                return v;
            }
            t++;
        }
        else if(j*a<t*b){
            if((c+a*j)%b==0){
                if(change==true){
                    v->m=(c+a*j)/b;
                    v->n=-j;
                }
                else{
                    v->m=-j;
                    v->n=(c+a*j)/b;
                }
                isend=true;
               /* cout<<"m,n"<<endl;
                cout<<v->m<<" "<<v->n<<endl;*/
                return v;
            }
            j++;
        }
    }
}
/* write your solution here */
void solve_minVol(JugsTest &jt, int target){
    // use the minimum amount of volume necessary to reach target
    // TODO
    Vec* v=new Vec();
    v=Func1(jt.getJugXCap(1),jt.getJugXCap(2),target);
    if(v->m>0&&v->n>0){
        jt.fillJugX(1);
        jt.fillJugX(2);
        return;
    }
    else if(v->m>0&&v->n==0){
        for(int i=0;i<v->m;i++){
            if(jt.isJugXEmpty(1)==false){
                jt.pourXintoY(1,2);
                jt.fillJugX(1);
            }
            else jt.fillJugX(1);
        }
        return;
    }
    else if(v->m==0&&v->n>0){
        for(int i=0;i<v->n;i++){
            if(jt.isJugXEmpty(2)==false){
                jt.pourXintoY(2,1);
                jt.fillJugX(2);
            }
            else jt.fillJugX(2);
        }
        return;
    }
     else if(v->m<0&&v->n>0){
        int tp=v->m;
        for(int i=0;i<v->n;i++){
            while(jt.isJugXEmpty(2)==false){
                if(jt.isJugXFull(1)&&tp<0){
                    jt.emptyJugX(1);
                    tp++;
                }
                jt.pourXintoY(2,1);
            }
            jt.fillJugX(2);
            while(i==v->n-1&&tp<0){
                if(jt.isJugXFull(1)){
                    jt.emptyJugX(1);
                    tp++;
                }
                if(tp<0)jt.pourXintoY(2,1);
            }
        }
        return;
    }
    else if(v->m>0&&v->n<0){
        int tp=v->n;
        for(int i=0;i<v->m;i++){
            while(jt.isJugXEmpty(1)==false){
                if(jt.isJugXFull(2)&&tp<0){
                    jt.emptyJugX(2);
                    tp++;
                }
                jt.pourXintoY(1,2);
            }
            jt.fillJugX(1);
            while(i==v->m-1&&tp<0){
                if(jt.isJugXFull(2)){
                    jt.emptyJugX(2);
                    tp++;
                }
                if(tp<0)jt.pourXintoY(1,2);
            }
        }
        return;
    }
}

// struct status{
//     int lastOperate;//如何到达这个状态，1表示给A装满水，2表示给B装满水，3表示给A桶倒空，4表示B倒空，5表示A倒给B，6表示B倒给A
//     int JugA;//a有多少水
//     int JugB;//b有多少水
//     status* laststatus;
// };
// LinkStack<status*>* fun2(JugsTest &jt,int target){
//     int aCap = jt.getJugXCap(1);
//     int bCap = jt.getJugXCap(2);
//     //status s1 = {1,aCap,0},s2={2,0,bCap};
//     status *s1=new status;
//     status *s2=new status;
//     s1->lastOperate=1;s1->JugA=aCap;s1->JugB=0;s1->laststatus=NULL;
//     s2->lastOperate=2;s2->JugA=0;s2->JugB=bCap;s2->laststatus=NULL;
//     LinkQueue<status*>* q = new LinkQueue<status*>();
//     q->EnQueue(s1);
//     q->EnQueue(s2);
//     status* tmp = q->DeQueue();
//     while(tmp->JugA + tmp->JugB != target){
//         for(int i=1;i<=6;i++){
//             if(tmp->JugA==aCap&&(i==1||i==6))continue;
//             if(tmp->JugA==0&&(i==3||i==5))continue;
//             if(tmp->JugB==bCap&&(i==2||i==5))continue;
//             if(tmp->JugB==0&&(i==4||i==6))continue;
//             if(i==1){
//                 status *s0 = new status{1,aCap,tmp->JugB,tmp};
//                 q->EnQueue(s0);
//             }
//             else if(i==2){
//                 status *s0 = new status{2,tmp->JugA,bCap,tmp};
//                 q->EnQueue(s0);
//             }
//             else if(i==3){
//                 status *s0=new status{3,0,tmp->JugB,tmp};
//                 q->EnQueue(s0);
//             }
//             else if(i==4){
//                 status *s0=new status{4,tmp->JugA,0,tmp};
//                 q->EnQueue(s0);
//             }
//             else if(i==5){//a倒给b
//                 int a,b;
//                 b = tmp->JugA+tmp->JugB>bCap ? bCap : tmp->JugA+tmp->JugB;
//                 a = tmp->JugA+tmp->JugB-b;
//                 status *s0=new status{5,a,b,tmp};
//                 q->EnQueue(s0);
//             }
//             else if(i==6){//b倒给a
//                 int a,b;
//                 a = tmp->JugA+tmp->JugB>aCap ? aCap : tmp->JugA+tmp->JugB;
//                 b=tmp->JugA+tmp->JugB-a;
//                 status *s0=new status{6,a,b,tmp};
//                 q->EnQueue(s0);
//             }
//         }
//         tmp = q->DeQueue();
//     }
//     //用栈存路线
//     LinkStack<status*> *s=new LinkStack<status*>();
//     s->Push(tmp);
//     while(tmp->laststatus!=NULL){
//         s->Push(tmp->laststatus);
//         tmp=tmp->laststatus;
//     }
//     return s;
// }
int numOperate1(JugsTest&jt,int target){
    jt.clearAll();
    jt.fillJugX(1);
    jt.pourXintoY(1,2);
    while(jt.getJugXVol(1)+jt.getJugXVol(2)!=target){
        if(jt.isJugXEmpty(1)){
            jt.fillJugX(1);
        }
        else if(jt.isJugXFull(1)){
            jt.pourXintoY(1,2);
        }
        else if(jt.isJugXFull(2)){
            jt.emptyJugX(2);
        }
        else if(jt.isJugXEmpty(2)){
            jt.pourXintoY(1,2);
        }
    }
    return jt.getMoveCount();
}
int numOperate2(JugsTest&jt,int target){
    jt.clearAll();
    jt.fillJugX(2);
    jt.pourXintoY(2,1);
    while(jt.getJugXVol(1)+jt.getJugXVol(2)!=target){
        if(jt.isJugXEmpty(2)){
            jt.fillJugX(2);
        }
        else if(jt.isJugXFull(2)){
            jt.pourXintoY(2,1);
        }
        else if(jt.isJugXFull(1)){
            jt.emptyJugX(1);
        }
        else if(jt.isJugXEmpty(1)){
            jt.pourXintoY(2,1);
        }
    }
    return jt.getMoveCount();
}
void solve_minMoves(JugsTest &jt, int target){
    // use the minimum number of moves necessary to reach target
    // TODO
    // LinkStack<status*>*s=fun2(jt,target);
    // while(!s->IsEmpty()){
    //     status *tmp=s->Pop();
    //     if(tmp->lastOperate==1){
    //         jt.fillJugX(1);
    //     }
    //     else if(tmp->lastOperate==2){
    //         jt.fillJugX(2);
    //     }
    //     else if(tmp->lastOperate==3){
    //         jt.emptyJugX(1);
    //     }
    //     else if(tmp->lastOperate==4){
    //         jt.emptyJugX(2);
    //     }
    //     else if(tmp->lastOperate==5){
    //         jt.pourXintoY(1,2);
    //     }
    //     else if(tmp->lastOperate==6){
    //         jt.pourXintoY(2,1);
    //     }
    // }
    if(target==0){
        return;
    }
    if(target==jt.getJugXCap(1)){
        jt.fillJugX(1);
        return;
    }
    if(target==jt.getJugXCap(2)){
        jt.fillJugX(2);
        return;
    }
    else if(target==jt.getJugXCap(1)+jt.getJugXCap(2)){
        jt.fillJugX(1);
        jt.fillJugX(2);
        return;
    }
    else if(target==jt.getJugXCap(1)-jt.getJugXCap(2)){
        jt.fillJugX(1);
        jt.pourXintoY(1,2);
        jt.emptyJugX(2);
        return;
    }
    else if(target==jt.getJugXCap(2)-jt.getJugXCap(1)){
        jt.fillJugX(2);
        jt.pourXintoY(2,1);
        jt.emptyJugX(1);
        return;
    }
    else{
        if(numOperate1(jt,target)<numOperate2(jt,target)){
            jt.clearAll();
            jt.fillJugX(1);
            jt.pourXintoY(1,2);
            while(jt.getJugXVol(1)+jt.getJugXVol(2)!=target){
                if(jt.isJugXEmpty(1)){
                    jt.fillJugX(1);
                }
                else if(jt.isJugXFull(1)){
                    jt.pourXintoY(1,2);
                }
                else if(jt.isJugXFull(2)){
                    jt.emptyJugX(2);
                }
                else if(jt.isJugXEmpty(2)){
                    jt.pourXintoY(1,2);
                }
            }
        }
        else{
            jt.clearAll();
            jt.fillJugX(2);
            jt.pourXintoY(2,1);
            while(jt.getJugXVol(1)+jt.getJugXVol(2)!=target){
                if(jt.isJugXEmpty(2)){
                    jt.fillJugX(2);
                }
                else if(jt.isJugXFull(2)){
                    jt.pourXintoY(2,1);
                }
                else if(jt.isJugXFull(1)){
                    jt.emptyJugX(1);
                }
                else if(jt.isJugXEmpty(1)){
                    jt.pourXintoY(2,1);
                }
            }
        }
    }
}

/* end of solution */

void test1(){
    JugsTest jt(5,3);
    cout << "Jugs: 5 and 3" << endl;
    for(int i=0;i<=8;i++){
        jt.clearAll();
        solve_minVol(jt,i);
        if(!jt.checkJugs(i)) cout << "BAD" << endl;
        cout << "Target = " << i << ", volume used = " << jt.getVolumeUsed() << endl;
    }
    cout << endl;
    
    JugsTest jt2(200,3);
    cout << "Jugs: 200 and 3" << endl;
    solve_minVol(jt2,199);
    if(!jt2.checkJugs(199)) cout << "BAD" << endl;
    cout << "Target = 199, volume used = " << jt.getVolumeUsed() << endl;
    cout << endl;
}

void test2(){
    JugsTest jt(5,3);
    cout << "Jugs: 5 and 3" << endl;
    for(int i=0;i<=8;i++){
        jt.clearAll();
        solve_minMoves(jt,i);
        if(!jt.checkJugs(i)) cout << "BAD" << endl;
        cout << "Target = " << i << ", move count = " << jt.getMoveCount() << endl;
    }
    cout << endl;  
    JugsTest jt2(200,3);
    cout << "Jugs: 200 and 3" << endl;
    solve_minMoves(jt2,199);
    if(!jt2.checkJugs(199)) cout << "BAD" << endl;
    cout << "Target = 199, move count = " << jt2.getMoveCount() << endl;
    cout << endl;
}

int main(){
    //test1();
    test2();
    return 0;
}
