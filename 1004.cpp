template <class A, class B>
class ABList{
    public:
        struct Type{
            A a;
            B b;
            bool t;
        };
        ABList(){
            length=0;
            capacity=10;
			data=new Type[10];
        }
        ~ABList(){
            delete[] data;
        }
        int Length(){
            return length;
        }
        A GetA(int i){
            if(i < 0 || i >= length) throw "Bad index";
            if(data[i].t==true) return data[i].a;
            else throw "Wrong type!";
        }
        B GetB(int i){
            if(i < 0 || i >= length) throw "Bad index";
            if(data[i].t==false) return data[i].b;
            else throw "Wrong type!";
        }
        int Locate(A x){
            for(int i=0;i<length;i++){
				if(data[i].a==x) return i;
			}
			return -1;
        }
        int Locate(B x){
            for(int i=0;i<length;i++){
				if(data[i].b==x) return i;
			}
			return -1;
        }
        void Insert(int i, A x){
            if(length >= capacity) expand();
            if(i < 0 || i > length) throw "Bad index";
            for(int j=length;j>i;j--){
                data[j]= data[j-1];
            }
            data[i].a = x;
            data[i].t=true;
            length++;
        }
		void Insert(int i, B x){
            if(length >= capacity) expand();
            if(i < 0 || i > length) throw "Bad index";
            for(int j=length;j>i;j--){
                data[j]= data[j-1];
            }
            data[i].b = x;
            data[i].t=false;
            length++;
        }
        void Delete(int i){
            if(i<0 || i>=length) throw "Bad index";
            for(int j=i;j<length-1;j++){
                data[j] = data[j+1];
            }
            length--;
        }
       void printList(){
             for(int i=0;i<length;i++){
                if(data[i].t==true)
                    cout << data[i].a << " ";
                else cout << data[i].b << " ";
            }
        }
    private:
        int length,capacity;
        Type* data;
        void expand(){
            Type *oldData=data;
			data=new Type[capacity<<1];
			for(int i=0;i<length;i++){
				data[i]=oldData[i];
			}
			capacity=capacity<<1;
			delete[] oldData;
        }
};