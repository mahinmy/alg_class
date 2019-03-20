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

bool pBal(string S){
    // TODO
}

int main(){
    string s;
    cin >> s;
    cout << (pBal(s) ? "Balanced" : "Not balanced") << endl;
    return 0;
}