#include "OpenHash.cpp"

int main()
{
	LinearOpenHashTable<int>* LOHtable = new LinearOpenHashTable<int>(11);
	LOHtable->insertKey(4)->insertKey(34)->insertKey(31)->insertKey(56)->insertKey(51)->insertKey(44)->insertKey(33)->insertKey(77)->insertKey(87)->insertKey(50)->insertKey(2);
	LOHtable->deleteKey(34)->deleteKey(77);
	LOHtable->insertKey(77)->insertKey(22);
	LOHtable->print();
	cout << "Key 44: " << LOHtable->searchKey(44) << endl;
	return 0;
}