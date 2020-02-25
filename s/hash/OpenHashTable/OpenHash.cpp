#include <iostream>
using namespace std;

template <class T> class HashTable
{
public:
	virtual HashTable<T>* insertKey(T x) = 0;
	virtual int searchKey(T x) = 0;
	virtual HashTable<T>* deleteKey(T x) = 0;
	virtual void print() = 0;
};

template <class T> class OpenHashTable : public HashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;	
	virtual OpenHashTable<T>* insertKey(T x) = 0;
	virtual OpenHashTable<T>* deleteKey(T x) = 0;
    virtual int searchKey(T x) = 0;
	int tableSize;
	int keyCounter;
	T** table;	

public:
	OpenHashTable<T>(int tableSize)
	{
		table = new T * [tableSize];
		for (int i = 0; i < tableSize; i++)
			table[i] = NULL;
		this->keyCounter = 0;
		this->tableSize = tableSize;		
	}

	int getTableSize() 
	{
		return tableSize;
	}		

	int getKeyCounter() 
	{
		return keyCounter; 
	}	

	T** getTable()
	{
		return table;
	}
};



template <class T> class NaiveOpenHashTable : public OpenHashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;
	T* deleted;
public:
	NaiveOpenHashTable<T>(int tableSize, T deleted) : OpenHashTable<T>(tableSize) 
	{ 
		this->deleted = new T(deleted);
	}	

	NaiveOpenHashTable<T>* insertKey(T x)
	{
		if (this->getKeyCounter() == this->getTableSize())
			return this;
		int i = 0;
		while (i < this->getTableSize())
		{
			int hash = computeHashFunction(x, i);
			if (this->getTable()[hash] == NULL || this->getTable()[hash] == deleted)
			{
				this->getTable()[hash] = new T(x);
				return this;
			}
			i++;
		}
		return this;
	}


	int searchKey(T x)
	{
		int iterator = 0;
		while (iterator < this->getTableSize())
		{
			int hash = computeHashFunction(x, iterator);
			if (*(this->getTable()[hash]) == x)
				return 1;
			iterator++;
		}
		return 0;
	}


	NaiveOpenHashTable<T>* deleteKey(T x)
	{
		int iterator = 0;
		while (iterator < this->getTableSize())
		{
			int hash = computeHashFunction(x, iterator);
			if (this->getTable()[hash] !=deleted && *(this->getTable()[hash]) == x)
			{
				delete this->getTable()[hash];
				this->getTable()[hash] = deleted;
				return this;
			}
			iterator++;
		}
		return this;
	}


	void print()
	{
		for (int i = 0; i < this->getTableSize(); i++)
		{
			cout << i;
			if (this->getTable()[i] != deleted && this->getTable()[i] )
				cout << "-> " << "[" << *(this->getTable()[i]) << "]";
			else
				cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};



template <class T> class EfficientOpenHashTable : public OpenHashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;
public:
	EfficientOpenHashTable<T>(int tableSize) : OpenHashTable<T>(tableSize) {}

	EfficientOpenHashTable<T>* insertKey(T x)
	{
		if (this->getKeyCounter() == this->getTableSize())
			return this;
		int i = 0;
		while (i < this->getTableSize())
		{
			int hash = computeHashFunction(x, i);
			if (this->getTable()[hash] == NULL)
			{
				this->getTable()[hash] = new T(x);
				return this;
			}
			i++;
		}
		return this;
	}

	int searchKey(T x)
	{
		int iterator = 0;
		while (iterator < this->getTableSize())
		{
			int hash = computeHashFunction(x, iterator);
			if (this->getTable()[hash] != NULL && *(this->getTable()[hash]) == x)
				return 1;
			iterator++;
		}
		return 0;
	}

	EfficientOpenHashTable<T>* deleteKey(T x)
	{
		int iterator = 0;
		int hash = 0;
		while (iterator < this->getTableSize())
		{
			hash = computeHashFunction(x, iterator);
			if (this->getTable()[hash] !=NULL && *(this->getTable()[hash]) == x)
			{
				delete this->getTable()[hash];	
				this->getTable()[hash] = NULL;
				iterator++;
				int hash2 = computeHashFunction(x, iterator);
				if (this->getTable()[hash2] == NULL)
					return this;					
				this->getTable()[hash] = (this->getTable()[hash2]);
				this->getTable()[hash2] = NULL;
				return this;				
			}
			iterator++;
		}	
		return this;		
	}


	void print()
	{
		for (int i = 0; i < this->getTableSize(); i++)
		{
			cout << i;
			if (this->getTable()[i])
				cout << "-> " << "[" << *(this->getTable()[i]) << "]";
			else
				cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};




template <class T> class LinearNaiveOpenHashTable : public NaiveOpenHashTable<T>
{
private:
	int computeHashFunction(T x, int i) 
	{
		return (((int)x % this->getTableSize()) + i) % this->getTableSize();
	}
public:
	LinearNaiveOpenHashTable(int tableSize, T deleted) : NaiveOpenHashTable<T>(tableSize, deleted) {}
};


template <class T> class LinearEfficientOpenHashTable : public EfficientOpenHashTable<T>
{
private:
	int computeHashFunction(T x, int i)
	{
		return (((int)x % this->getTableSize()) + i) % this->getTableSize();
	}
public:
	LinearEfficientOpenHashTable(int tableSize) : EfficientOpenHashTable<T>(tableSize) {}
};