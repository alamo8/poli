#include <iostream>
using namespace std;

template <class T> class HashTable
{
public:
	virtual HashTable<T>* insertKey(T x) = 0;
	virtual int searchKey(T x) = 0;
	virtual HashTable<T>* deleteKey(T x) = 0;
};

template <class T> class OpenHashTable : public HashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;
	int tableSize;
	int keyCounter;
	T** table;
	T* deleted;

public:
	OpenHashTable<T>(int tableSize)
	{
		table = new T * [tableSize];
		for (int i = 0; i < tableSize; i++)
			table[i] = NULL;
		this->keyCounter = 0;
		this->tableSize = tableSize;
		deleted = new T();
	}

	int getTableSize() 
	{
		return tableSize;
	}		

	int getKeyCounter() 
	{
		return keyCounter; 
	}

	OpenHashTable<T>* insertKey(T x)
	{		
		if (keyCounter == tableSize)
			return this;
		int i = 0;		
		while (i < tableSize)
		{	
			int hash = computeHashFunction(x, i);	
			if (table[hash] == NULL || table[hash] == deleted)
			{
				table[hash] = new T(x);
				return this;
			}			
			i++;
		}
		return this;
	}


	int searchKey(T x)
	{
		int iterator = 0;		
		while (iterator < tableSize)
		{
			int hash = computeHashFunction(x, iterator);
			if (*table[hash] == x)
				return 1;			
			iterator++;
		}
		return 0;
	}


	OpenHashTable<T>* deleteKey(T x)
	{
		int iterator = 0;		
		while (iterator < tableSize)
		{
			int hash = computeHashFunction(x, iterator);
			if (*table[hash] == x)
			{
				delete table[hash];
				table[hash] = deleted;				
				return this;
			}
			iterator++;			
		}
		return this;
	}


	void print() 
	{
		for (int i = 0; i < tableSize; i++)
		{
			cout << i;
			if (table[i] && table[i] != deleted) 
			  cout<<"-> " << "[" << *table[i] <<"]";
			else 
			  cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};


template <class T> class LinearOpenHashTable : public OpenHashTable<T>
{
private:
	int computeHashFunction(T x, int i) 
	{
		return (((int)x % this->getTableSize()) + i) % this->getTableSize();
	}
public:
	LinearOpenHashTable(int tableSize) : OpenHashTable<T>(tableSize) {}
};