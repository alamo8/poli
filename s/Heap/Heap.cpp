#include <iostream>

using namespace std;

//Template of the Priority Queue
template <class T> class PriorityQueue
{
  public:
	     virtual T* extract() = 0;
	     virtual PriorityQueue<T>* enqueue(T x) = 0;	
		 virtual double compare(T* a, T* b) = 0;		 
		 virtual void printKey(int i) const = 0;
};


//BinaryHeap template
template <class T> class BinaryHeap : public PriorityQueue<T>
{
  private:
	      T** hqueue;

	      int heapsize;

	      int queuesize;

	      int left(int i) 
		  { 
			  return i << 1; // 2i
		  }

	      int right(int i)
		  { 
			  return (i << 1) | 1;  //2i-1
		  }

	      int parent(int i)
		  { 
			  return i >> 1; // i/2
		  }

	      void swap(int i, int j)
		  {
		      T* tmp = hqueue[i];
		      hqueue[i] = hqueue[j];
		      hqueue[j] = tmp;
	      }

	     void heapify(int index) 
		 {
			 int i = index;
			 while (i <= heapsize)
			 {
				 int l = left(i);
				 int r = right(i);
				 int v = i;
				 if (l <= heapsize && compare(hqueue[v], hqueue[l]) < 0)
					 v = l;
				 if (r <= heapsize && compare(hqueue[v], hqueue[r]) < 0)
					 v = r;
				 if (v == i)
					 break;
				 swap(i, v);
				 i = v;
			 }
	     }

		 void recursiveHeapify(int i)
		 {
			 if (i > heapsize)
				 return;
			 int l = left(i);
			 int r = right(i);
			 int v = i;
			 if (l <= heapsize && compare(hqueue[v], hqueue[l]) < 0)
				 v = l;
			 if (r <= heapsize && compare(hqueue[v], hqueue[r]) < 0)
				 v = r;
			 if (v == i)
				 return;
			 swap(i, v);
			 recursiveHeapify(v);
		 }

 public:
	    virtual double compare(T* a, T* b) = 0;		
		virtual void printKey(int i) const = 0;	


		void print() const
		{
			for (int i = 1; i <= this->size(); i++)
				printKey(i);
			cout << endl;
		}

	    BinaryHeap(int size)
		{
		  hqueue = new T * [size+1];
		  queuesize = size+1;
		  heapsize = 0;
	    }

	    BinaryHeap(T** V, int size)
	    {
		  hqueue = V;
		  queuesize = size + 1;
		  heapsize = size;
	    }

	   void buildHeap()
	   {		  
		for (int i = heapsize / 2; i > 0; i--)
		  heapify(i);
	   }

	   T* extract()
	   {
		if (heapsize == 0) 
			return NULL;
		swap(1, heapsize);
		heapsize--;
		heapify(1);
		return hqueue[heapsize + 1];
	   }

	   T** getPriorityQueue() const
	   {
		   return hqueue;
	   }

	  void modify(int i, T k)  
	   {
		if (i<1 || i>heapsize)
			return;
		if (compare(hqueue[i], &k) >= 0)
			return;
		delete hqueue[i];
		hqueue[i] = new T(k);
		while (i > 1 && compare(hqueue[i], hqueue[parent(i)]) > 0)
		{
		  swap(i, parent(i));
		  i = parent(i);
		}
		return;
	  }

	BinaryHeap<T>* enqueue(T x) 
	{
		if (heapsize == queuesize - 1) 
		  return this;
		heapsize += 1;
		hqueue[heapsize] = new T(x);
		int i = heapsize;
		while (i > 1 && compare(hqueue[i], hqueue[parent(i)]) > 0)
		{
			swap(i, parent(i));
			i = parent(i);
		}
		return this;
	}

	void sort()
	{
	 buildHeap(); 
	 int node_number = heapsize;
	 for (int i = 0; i < node_number; i++) 
		 extract();
	  heapsize = node_number;
	}

	int size() const
	{
	  return heapsize;
	}
};


template <class T> class MaxBinaryHeap : public BinaryHeap<T>
{
public:	
	MaxBinaryHeap(int size) : BinaryHeap<T>(size) {}
	MaxBinaryHeap(T** A, int size) : BinaryHeap<T>(A, size) {}

	virtual double compare(T* a, T* b) = 0;	
	virtual void printKey(int i) const = 0;

	T* extractMax()
	{
		return BinaryHeap<T>::extract();
	}
	void increaseKey(int i, T k)
	{
		return BinaryHeap<T>::modify(i, k);
	}
};



template <class T> class MaxHeap : public MaxBinaryHeap<T>
{
  public:
	 double compare(T* a, T* b)
	 {
		return (double) (*a) - (*b);
	 }
	
	 void printKey(int i) const
	 {
		 cout << *(this->getPriorityQueue())[i] << " ";
	 }
	MaxHeap(int size) : MaxBinaryHeap<T>(size) {}
	MaxHeap(T** A, int size) : MaxBinaryHeap<T>(A, size) {}	
};



template <class T> class MinBinaryHeap : public BinaryHeap<T>
{
public:	
	MinBinaryHeap(int size) : BinaryHeap<T>(size) {}
	MinBinaryHeap(T** A, int size) : BinaryHeap<T>(A, size) {}
	virtual double compare(T* a, T* b) = 0;	
	virtual void printKey(int i) const = 0;
	T* extractMin()
	{
		return BinaryHeap<T>::extract();
	}
	void decreaseKey(int i, T k)
	{
		return BinaryHeap<T>::modify(i, k);
	}
	
};


template <class T> class MinHeap : public MinBinaryHeap<T>
{
  public:
	MinHeap(int size) : MinBinaryHeap<T>(size) {}
	MinHeap(T** A, int size) : MinBinaryHeap<T>(A, size) {}
	double compare(T* a, T* b)
	{
		return (double) (*b) - (*a);
	}	
	void printKey(int i) const
	{
		cout << *(this->getPriorityQueue())[i] << " ";
	}
};