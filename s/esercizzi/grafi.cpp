#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;

template<class H, class T> class Graph{
	private:
		int max_len, node_number, edge_number, rootindex;
		int** indexMatrix;
		H** keyMap;
		T** weightMatrix;
		
		Graph<H, T>* modifyEdge(H const& x, H const& y, T const& _weight, int ind){
			int i= find_index(x);
			int j= find_index(y);
			if(i< 0 || j< 0)
				return this;
			if(indexMatrix[i][j] == ind){
				if(ind){
					indexMatrix[i][j]=0;
					edge_number--;
				}else{
					indexMatrix[i][j]=1;
					edge_number++;
				}
				weightMatrix[i][j]=_weight;
			}
			return this;
		}
	
	public:
	
		Graph(int max_l){
			max_len=max_l;
			indexMatrix= new int* [max_len];
			
			weightMatrix= new T* [max_len];
			rootindex=-1;
			node_number=edge_number=0;
			for(int i=0; i<max_len; i++){
				indexMatrix[i]= new int[max_len];
				weightMatrix[i]= new T[max_len];
				for(int j=0; j<max_len; j++){
					indexMatrix[i][j]=0;
					weightMatrix[i][j]=NULL;
				}
			}
			keyMap= new H* [max_len];
			for(int i=0; i<max_len; i++){
				keyMap[i]=NULL;
			}
		}
		
		int find_index(H x){
			for(int i=0; i<node_number; i++){
				if(*keyMap[i]== x) return i;
			}
			return -1;
		}
		
		int get_rootindex(){
			return rootindex;
		}
		
		int get_matrixNodenumber(){
			return node_number;
		}
		
		int get_maxNode(){
			return max_len;
		}
		
		int get_edgeNumber(){
			return edge_number;
		}
		
		int get_maxedgeNumber(){
			return max_len;
		}
		
		H** get_keyMatrix(){
			return keyMap;
		}
		
		T** get_weightMatrix(){
			return weightMatrix;
		}
		
		int** get_indexMatrix(){
			return indexMatrix;
		}
		
		H* get_key(int index){
			if(index >= node_number || index< 0)return NULL;
			return keyMap[index];
		}
		
		Graph<H,T>* add_node(H const& k){
			if(node_number== max_len)return this;
			if(find_index(k)>=0) return this;
			keyMap[node_number]=new H(k);
			node_number++;
			return this;
		}
		
		Graph<H, T>* add_rootNode(H const& k){
			rootindex=node_number;
			return add_node(k);
		}
		
		Graph<H, T>* add_edge(H const& x, H const& y, T const& weight){
			return this->modifyEdge(x,y,weight,0);
		}
		
		Graph<H, T>* delete_edge(H const& x, H const& y){
			return this->modifyEdge(x,y,NULL,1);
		}
				
		Graph<H, T>* delete_node(H const &key){
			int index=find_index(key);
			if(index < 0 || node_number==0 || index==rootindex) return this;
			for(int i=index; i< node_number-1; i++){
				for(int j=0; j< node_number-1; j++){
					indexMatrix[j][i]=indexMatrix[j][i+1];
					weightMatrix[j][i]=weightMatrix[j][i+1];
				}
			}
			for(int i=index; i< node_number-2; i++){
				for(int j=0; j< node_number-2; j++){
					indexMatrix[j][i]=indexMatrix[i+1][j];
					weightMatrix[j][i]=weightMatrix[i+1][j];
				}
			}
			for(int i=0; i<node_number; i++){
				indexMatrix[i][node_number - 1] = 0;
				indexMatrix[node_number - 1][i] = 0;
				weightMatrix[i][node_number - 1] = NULL;
				weightMatrix[node_number - 1][i] = NULL;
			}
			for (int j = index; j < node_number - 1; j++)
				keyMap[j] = keyMap[j + 1];
			keyMap[node_number - 1] = NULL;

			node_number--;
			return this;
		}
		H const* getRootNode()
	{
		if (rootindex < 0)
			return NULL;
		return	keyMap[rootindex];
	}

	void setRootNode(H const& k)
	{
		int t = find_index(k);
		if (t < 0)
			return;
		else rootindex = t;
	}

	void print() const
	{
		for (int i = 0; i < node_number; i++)
		{
			cout << "(" << i << ", " << *keyMap[i] << ")" << " --> ";
			for (int j = 0; j < node_number; j++)
				if (indexMatrix[i][j])
				{
					cout << "{" << *keyMap[j] << "," << weightMatrix[i][j] << "}  ";

				}
			cout << endl;
		}
	}

	void printIndexMatrix() const
	{
		for (int i = 0; i < node_number; i++)
		{
			for (int j = 0; j < node_number; j++)
				cout << indexMatrix[i][j] << " ";
			cout << endl;
		}
	}

	void printWeightMatrix() const
	{
		for (int i = 0; i < node_number; i++)
		{
			for (int j = 0; j < node_number; j++)
				cout << weightMatrix[i][j] << " ";
			cout << endl;
		}
	}
};

int main(){
	int def = 0;
	Graph<char, int>* g = new Graph<char, int>(4);
	g->add_node('A')->add_rootNode('C')->add_rootNode('B')->add_node('D');
	g->add_edge('C', 'B', def)->add_edge('C', 'A', def)->add_edge('C', 'C', def)->add_edge('B', 'D', def)->add_edge('A', 'D', def);
	cout << "Max size of the graph: " << g->get_maxNode() << endl;
	cout << "Current node number: " << g->get_matrixNodenumber() << endl;
	cout << "Current edge number: " << g->get_edgeNumber() << endl;
	g->print();
	cout << "The root is " << *(g->getRootNode()) << " at index " << g->get_rootindex() << endl;
	cout << "We now change the root" << endl;
	g->setRootNode('C');
	cout << "The new root is " << *(g->getRootNode()) << " at index " << g->get_rootindex() << endl;
	cout << "We now delete some edges" << endl;
	g->delete_edge('C', 'A')->delete_edge('B', 'D');
	cout << "Current edge number: " << g->get_matrixNodenumber() << endl;
	g->print();
	cout << "Modifying graph" << endl;
	g->add_edge('C', 'A', def)->add_edge('B', 'D', def)->add_edge('A', 'C', def)->add_edge('B', 'C', def);
	g->print();
	cout << "Deleting node" << endl;
	//change the root node before deleting
	g->setRootNode('B');
	g->delete_node('C');
	g->print();
	return 0;
}
