#include <iostream>
using namespace std;

const int MaxSize = 100;

template <class T>
class SeqList{
    private:
        int count;
        T data[MaxSize];
    public:
        SeqList(){
            count =0;
        }
        SeqList(T a[], int n){
            if(n > MaxSize) throw "Too many items";
            for(int i=0;i<n;i++){
                data[i] = a[i];
            }
            count = n;
        }

        ~SeqList(){
        }

        int Length(){
            return count;
        }

        T Get(int i){
            if(i < 0 || i >= count) throw "Bad index";
            return data[i];
        }

        int Locate(T x){
            for(int i=0;i<count;i++){
                if(data[i] == x) return i;
            }
            return -1;
        }

        void Insert(int i, T x){
            if(count >= MaxSize) throw "List full";
            if(i < 0 || i > count) throw "Bad index";
            for(int j=count;j>i;j--){
                data[j] = data[j-1];
            }
            data[i] = x;
            count++;
        }

        void Set(int i, T x){
            if(i < 0 || i >= count) throw "Bad index";
            data[i] = x;
        }

        T Delete(int i){
            if(i<0 || i>=count) throw "Bad index";
            T x = data[i];
            for(int j=i;j<count-1;j++){
                data[j] = data[j+1];
            }
            count--;
            return x;
        }
        void printList(){
            for(int i=0;i<count;i++){
                cout << data[i] << " ";
            }
        }
};

class IntPolynomial{
    private:
        int degree;
		SeqList<int> *S;
    public:
		void insertData(int i,int j){
			S->Insert(i,j);
		}
		void setDegree(int i){
			degree=i;
		}
        IntPolynomial(){
            degree=0;
			S=new SeqList<int>();
        }
        IntPolynomial(int* a, int n){
            degree=n;
            S=new SeqList<int>(a,n+1);
        }
        ~IntPolynomial(){
            delete S;
        }
		int getData(int i){
			return S->Get(i);
		}

        int getDegree(){
            return degree;
        }

        IntPolynomial* Add(IntPolynomial* b){
            int i,j,k;
            IntPolynomial* p ;
			p= new IntPolynomial();
			j=b->getDegree();
            if(j>degree){
                 for(i=0;i<=degree;i++)
                     p->insertData(i,S->Get(i)+b->getData(i));
				 for(i=degree+1;i<=j;i++)
					 p->insertData(i,b->getData(i));
				 k=j;
			}
			else{
				 for(i=0;i<=j;i++)
                      p->insertData(i,S->Get(i)+b->getData(i));
				 for(i=j+1;i<=degree;i++)
					 p->insertData(i,S->Get(i));
				 k=degree;
			}
			p->setDegree(k);
			return p;
        }
       IntPolynomial* Subtract(IntPolynomial* b){
            int i,j,k;
            IntPolynomial* p ;
			p= new IntPolynomial();
			j=b->getDegree();
            if(j>degree){
                 for(i=0;i<=degree;i++)
                     p->insertData(i,S->Get(i)-b->getData(i));
				 for(i=degree+1;i<=j;i++)
					 p->insertData(i,-(b->getData(i)));
				 k=j;
			}
			else{
				 for(i=0;i<=j;i++)
                      p->insertData(i,S->Get(i)-b->getData(i));
				 for(i=j+1;i<=degree;i++)
					 p->insertData(i,S->Get(i));
				 k=degree;
			}
			p->setDegree(k);
			return p;
        }
        IntPolynomial* Multiply(IntPolynomial* b){
            int i,j,n,sum=0,a;
	    	IntPolynomial* p = new IntPolynomial();
			a=b->getDegree()+degree;
			for(n=0;n<=a;n++){
                for(i=0;i<=degree;i++){
				    for(j=0;j<=b->getDegree();j++){
						if(n==i+j){
							sum=sum+S->Get(i)*b->S->Get(j);
						}
					}
				}
                p->insertData(n,sum);
                p->setDegree(a);
				sum=0;
			}
			return p;
        }
        void printPolynomial(){
			int i,x,t=0;
            for(i=0;i<=degree;i++){
				x=S->Get(i);
				while(x!=0){
					if(i==0){
				    	cout<<x;
						t=1;
					}
					else if(i>0){
				  	    if(x>0){
						   if(t==0){
						       if(x==1) cout<<"x";
						       else cout<<x<<"x";
						       t=1;
						   }
					    	else  {
						       if(x==1) cout<<"+x";
						       else cout<<"+"<<x<<"x";
					     	   t=1;
							}
						}
						else if(x<0){
					    	if(x==-1) cout<<"-x";
					    	else cout<<x<<"x";
						    t=1;
						}
					}
					if(i>1){
						cout<<"^"<<i;
					}
					x=0;
				}
			}
		}
};

int main(){
    int a[3] = {1,1,1};
    int b[3] = {1,-1,1};
    IntPolynomial* ip5 = new IntPolynomial(a,2);
    IntPolynomial* ip6 = new IntPolynomial(b,2);
    ip5->Add(ip6)->printPolynomial();
    cout << endl;
    ip5->Subtract(ip6)->printPolynomial();
    cout << endl;
    ip5->Multiply(ip6)->printPolynomial();
    cout << endl;
    return 0;
}