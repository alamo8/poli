#include <iostream>

using namespace std;

//template coda di priorità
template<class T> class PriorityQueue{
	public:
		virtual T* exstract()=0;
		virtual PriorityQueue<T>* enqueue(T x)=0;
		virtual double compare(T* x, T* y)=0;
		virtual void printkey(int i) const=0;
};

template<class T>class BinaryHeap: public PriorityQueue<T> {
	private:
		int heapsize, queuesize;
		T** hqueue;
		
		int left(int i){
			return (i << 1);
		}
		int right(int i){
			return (i << 1)| 1;
		}
		int parent(int i){
			return (i >> 1);
		}
		void swap(int i, int j){
			T* temp = hqueue[i];
			hqueue[i]= hqueue[j];
			hqueue[j]= temp;
		}
		void heapify(int index){
			int i=index;
			while(i<= heapsize){
				int l= left(i);
				int r= right(i);
				int v=i;
				if(l<= heapsize && compare(hqueue[v], hqueue[l])<= 0) v=l;
				if(r<= heapsize && compare(hqueue[v], hqueue[r])<= 0) v=r;
				if(v == i) return;
				swap(i,v);
				i=v;
			}
		}
	public:
		virtual double compare(T* a, T* b)=0;
		virtual void printkey(int i)const=0;
		
		void print()const{
			for(int i=1; i<=this->size(); i++)
				printkey(i);
			cout<<endl;
		}
		BinaryHeap(int size){
			hqueue= new T* [size+1];
			queuesize=size+1;
			heapsize=0;
		}
		BinaryHeap(T** h, int size){
			hqueue=h;
			queuesize=size+1;
			heapsize=size;
		}
		void buildHeap(){
			for(int i=heapsize/2; i<0; i--){
				heapify(i);
			}
		}
		T* exstract(){
			if(heapsize==0) return NULL;
			swap(1,heapsize);
			heapsize--;
			heapify(1);
			return hqueue[heapsize+1];
		}
		T** getPriorityQueue()const{
			return hqueue;
		}
		void modify(int key, T h){
			if(key< 1 || key> heapsize) return;
			if(compare(hqueue[key], &h)>=0) return;
			delete hqueue[key];
			hqueue[key] = new T(h);
			while(key > 1 && compare(hqueue[key], hqueue[parent(key)])>0){
				swap(key, parent(key));
				key=parent(key);
			}
		}
		BinaryHeap<T>* enqueue(T x){
			if(heapsize== queuesize-1) return this;
			heapsize++;
			hqueue[heapsize]= new T(x);
			int i=heapsize;
			while(i>1 && compare(hqueue[i], hqueue[parent(i)])>0){
				swap(i,parent(i));
				i=parent(i);
			}
			return this;
		}
		void sort(){
			buildHeap();
			int number_node=heapsize;
			for(int i=0; i<number_node; i++){
				exstract();
			}
			heapsize=number_node;
		}
		int size()const{
			return heapsize;
		}

};

template<class T> class MaxBinaryHeap: public BinaryHeap<T>{
	public:
		MaxBinaryHeap(int size): BinaryHeap<T>(size){}
		MaxBinaryHeap(T** a, int size): BinaryHeap<T>(a,size){}
		virtual double compare(T* a, T* b)=0;
		virtual void printkey(int i)const=0;
		
		T* estractMax(){return BinaryHeap<T>::exstract();}
		void incraseKey(int i, T k){return  BinaryHeap<T>::modify(i,k);}
};

template<class T> class MaxHeap: public MaxBinaryHeap<T>{
	public:
		double compare(T* a, T* b){
			return (double) *a - *b;
		}
		void printkey(int i)const{
			cout<< *(this->getPriorityQueue())[i]<< " ";
		}
		MaxHeap(int size):MaxBinaryHeap<T>(size){};
		MaxHeap(T** a, int size):MaxBinaryHeap<T>(a,size){}
};




int main(){
	 MaxHeap<int>* B = new MaxHeap<int>(100);
	 B->enqueue(6)->enqueue(9)->enqueue(2)->enqueue(7)->enqueue(12);
	 cout << "The queue is :" << endl;
	 B->print();
	 cout << "The max is: " << *(B->estractMax()) << endl;
	 cout << "The queue after the extact is:" << endl;
	 B->print(); 
	 cout << "The tree is:" << endl; 
	 cout << "Additional elements" << endl;
	 B->enqueue(4)->enqueue(1)->enqueue(5);
	 B->print();
	 cout << "Increase the second element" << endl;
	 B->incraseKey(6, 8);
	 B->print();
	 cout << "Sorting" << endl;
	 B->sort();
	 B->print();

	 cout << endl << endl;

	 /*int node_number = 100;
	 int** V = new int* [node_number + 1];
	 for (int i = 1; i <= node_number; i++) 
	   V[i] = new int(rand() % 100);
	 /*MinHeap<int>* C = new MinHeap<int>(V, node_number);
	 cout << "The initial array is:" << endl;
	 C->print();
	 cout << "Building the heap" << endl;
	 C->buildHeap();
	 cout << "The heap is:" << endl;
	 C->print();
	 cout << "The tree is:" << endl; 
	 cout << "Sorting..." << endl;
	 C->sort();
	 cout << "The sorted array is:" << endl;
	 C->print();*/
}
