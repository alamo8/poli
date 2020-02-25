#include "OpenHash.cpp"

int main()
{
	LinearNaiveOpenHashTable<int>* LOHtable = new LinearNaiveOpenHashTable<int>(11, -1);
	LOHtable->insertKey(4)->insertKey(34)->insertKey(31)->insertKey(56)->insertKey(51)->insertKey(44)->insertKey(33)->insertKey(77)->insertKey(87)->insertKey(50)->insertKey(2);
	LOHtable->deleteKey(34)->deleteKey(77);
	LOHtable->insertKey(77)->insertKey(22);
	LOHtable->print();
	cout << "Key 44: " << LOHtable->searchKey(44) << endl;

	cout << "Efficient Version" << endl;

	LinearEfficientOpenHashTable<int>* LEOHtable = new LinearEfficientOpenHashTable<int>(11);
	LEOHtable->insertKey(4)->insertKey(44)->insertKey(33)->insertKey(77)->insertKey(87)->insertKey(50)->insertKey(2);
	LEOHtable->print();
	cout << "Delete key: 34" << endl;
	LEOHtable->deleteKey(34);
	LEOHtable->print();
	cout << "Delete key: 77 " << endl;
	LEOHtable->deleteKey(77);
	LEOHtable->print();
	cout << "Delete key: 44 " << endl;
	LEOHtable->deleteKey(44);
	LEOHtable->print();
	cout << "Delete key: 87 " << endl;
	LEOHtable->deleteKey(87);
	LEOHtable->print();
	LEOHtable->insertKey(77)->insertKey(22);
	LEOHtable->print();
	cout << "Key 44: " << LEOHtable->searchKey(44) << endl;

	return 0;
}