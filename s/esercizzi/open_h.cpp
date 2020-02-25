#include <iostream>

using namespace std;

template<class T> class HashTable{
	virtual HashTable<T>* insertKey(T x)=0;
	//virtual HashTable<T>* deletekey(T x)=0;
	//virtual int searchkey(T x)=0;*/
};

template<class T> class OpenHashTable: public HashTable<T>{
	private:
		virtual int computeHash(T x, int i)=0;
		int tablesize, keycount;
		T** table;
		T* deleted;
	public:
		OpenHashTable(int size){
			tablesize=size;
			keycount=0;
			deleted= new T;
			table=new T* [tablesize];
			for(int i=0; i<tablesize; i++)
				table[i]=NULL;
		}
		int get_size(){
			return tablesize;
		}
		int get_keycount(){
			return keycount;
		}
		OpenHashTable<T>* insertKey(T x){
			if(keycount== tablesize) return this;
			int i=0;
			while(i<tablesize){			
				int key= computeHash(x,i);
				if(table[key]==NULL || table[key]== deleted){
					table[key]= new T(x);
					return this;
				}
				i++;
			}
			return this;
		}
		OpenHashTable<T>* deleteKey(T x){
			int iterator=0;
			while(iterator< tablesize){
				int hash= computeHash(x,iterator);
				if(*table[hash]== x){
					delete table[hash];
					table[hash]= deleted;
					return this;
				}
				iterator++;
			}
			return this;
		}		
		
		int searchKey(T x){
			int iterator=0;
			while(iterator < tablesize){
				int hash= computeHash(x,iterator);
				if(table[hash] && *table[hash]== x) return 1;
				iterator++;
			}
			return 0;
		}

		void print(){
			for (int i = 0; i < tablesize; i++){
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

template<class T> class LinearOpenHashTable: public OpenHashTable<T>{
	private:
		int computeHash(T x, int i){
			return (((int)x % this->get_size()) + i) % this->get_size();
		}
	public:
		LinearOpenHashTable(int size):OpenHashTable<T>(size){}
};

int main(){
	LinearOpenHashTable<int>* LOHtable = new LinearOpenHashTable<int>(11);
	LOHtable->insertKey(4)->insertKey(34)->insertKey(31)->insertKey(56)->insertKey(51)->insertKey(44)->insertKey(33)->insertKey(77)->insertKey(87)->insertKey(50)->insertKey(2);
	LOHtable->print();
	LOHtable->deleteKey(34)->deleteKey(77);
	LOHtable->print();
	LOHtable->insertKey(77)->insertKey(22);
	LOHtable->print();
	cout << "Key 44: " << LOHtable->searchKey(44) << endl;
	return 0;
}
































