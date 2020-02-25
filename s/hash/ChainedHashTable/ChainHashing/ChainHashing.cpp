#include<iostream> 
#include <list> 
using namespace std;

template <class T> class HashTable
{  		 
  public:	     	
	     virtual HashTable<T>* insertKey(T x)=0;
	     virtual HashTable<T>* deleteKey(T key)=0;
		 virtual int searchKey(T key) = 0;
};


template <class T> class LinkedHashTable : public HashTable<T>
{
  private:
	       int slots;    // Number of slots 	
	       list<T> *table; 
		   int size;
		   virtual int computeHashFunction(T x) = 0;

  public:
	LinkedHashTable<T>(int x)
	{
		this->slots = x;
		table = new list<T>[slots];
		size = 0;		
	}

	LinkedHashTable<T>* insertKey(T key)
	{
		int index = computeHashFunction(key);
		table[index].push_back(key);
		size++;
		return this;
	}


	LinkedHashTable<T>* deleteKey(T key)
	{
		int index = computeHashFunction(key);
		list<T>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			if (*i == key)
			{
				table[index].erase(i);
				size--;
				break;
			}
		}		
		return this;
	}
	
	int searchKey(T key)
	{
		int index = computeHashFunction(key);
		list<T>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
		{
			if (*i == key)
				return index;
		}
		return -1;	
	}

	int getSlotNumber()
	{
		return slots;
	}

	int getSize()
	{
		return size;
	}

	void printHashTable()
	{
		for (int i = 0; i < this->getSlotNumber(); i++) 
		{
			cout << i;
			for (auto x : table[i])
				cout << " --> [" << x <<"]";
			cout << endl;
		}
	}

};


template <class T> class DivisionLinkedHashTable : public LinkedHashTable<T>
{
 private:
	int computeHashFunction(T x) 
	{
		int h = ((int)x % this->getSlotNumber());
		return h;
	}
 public:
	DivisionLinkedHashTable<T>(int edge_number) : LinkedHashTable<T>(edge_number) {}
};


template <class T> class MultiplicationLinkedHashTable : public LinkedHashTable<T>
{
private:
	double c;
	int computeHashFunction(T x) 
	{
		double y = (int)x * c;
		double a = y - (int)y;
		int h = (int)(a * this->getSlotNumber());
		return h;
	}
public:
	MultiplicationLinkedHashTable(int edge_number) : LinkedHashTable<T>(edge_number)
	{
		c = 0.7;
	}
};