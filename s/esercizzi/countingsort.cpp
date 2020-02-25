#include <iostream>

using namespace std;

void print_array(int* v, int size){
	for(int i=0; i<size; i++)
		cout<<v[i]<<" ";
	cout<<endl;
}

void countingSort(int* v, int size){
	//troviamo il range
	int min=0, max=0;
	for(int i=0; i<size; i++){
		if(max < v[i])max=v[i];
		if(min > v[i])min=v[i];
	}
	int range= max-min+1;
	int* temp= new int[size];
	int* freq= new int[range];
	for(int i=0; i<range; i++)
		freq[i]=0;
	for(int i=0; i<size; i++)
		freq[v[i]-min]++;
	for(int i=1; i<range; i++)
		freq[i]+=freq[i-1];
	for(int i=size-1; i>=0; i--){
		temp[freq[v[i]-min]-1]=v[i];
		freq[v[i]-min]--;
	}
	for(int i=0; i<size; i++)
		v[i]=temp[i];

	delete[] temp;
	delete[] freq;
}

void countingSortInPlace(int* v, int size){
	int min=0, max;
	for(int i=0; i<size; i++){
		if(max < v[i])max=v[i];
		if(min > v[i])min=v[i];
	}
	int range= max-min+1;
	int* freq= new int[range];
	for(int i=0; i<range; i++)
		freq[i]=0;
	for(int i=0; i<size; i++)
		freq[v[i]-min]++;
	int k=0, j=0;
	while(j<size){
		while(freq[k]>0){
			v[j++]=k+min;
			freq[k]--;
		}
		k++;
	}
	delete[] freq;
}

int main(){
	int size = 8;
	int input[] = {10, 5, 3, 0, 2, 3, 0, 3};  
	cout << "Input Array: ";
	print_array(input, size);
	cout << endl;
	//countingSort(input, size);
	cout << "Array sorted with Counting-Sort: ";
	print_array(input, size);
	cout << endl;
	cout << "Array sorted with Counting-SortInPlace: ";
	countingSortInPlace(input, size);
	print_array(input, size);
	cout << endl;
}




























