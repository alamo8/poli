#include <iostream>
#include <queue>

using namespace std;

template<class T> class Node{
	private:
		T key;
		int color;
		Node<T>* parent;
		Node<T>* left;
		Node<T>* right;
	public:
	
		Node(T k, int _color){
			parent= left= right=NULL;
			key=k;
			color=_color;
		}

		T get_key(){return key;}

		Node<T>* get_parent(){return parent;}

		Node<T>* get_left(){return left;}

		Node<T>* get_right(){return right;}

		int get_color(){return color;}

		void set_parent(Node<T>* p){parent=p;}

		void set_left(Node<T>* l){left=l;}

		void set_right(Node<T>* r){right=r;}

		void set_key(T x){key=x;}

		void set_colot(int _color){color=_color;}
};

template<class T> class RBTree{
	private:
		const int RED=1;
		const int BLACK=0;
		Node<T>* root;
	
		int is_left_child(Node<T>* n){return n== n->get_paretnt()->get_left();}

		void insert_nodeup(Node<T>* before, Node<T>* node){
			if(before->get_parent() != NULL){
				if(is_left_clild(before))
					before->get_parent()->set_left(node);
				else
					before->get_parent()->set_right(node);
			}else{
				root=node;
			}
			node->set_paret(before->get_parent());
			before->set_paret(node);
		}

		Node<T>* get_uncle(Node<T>* node){
			if(node->get_parent() == NULL || node->get_parent()->get_parent()== NULL) return NULL;
			if(is_left_child(node->get_parent())){
				return node->get_parent()->get_parent()->get_right();
			}else{
				return node->get_parent()->get_parent()->get_left();
			}
		}

		Node<T>* get_sibling(Node<T>* node){
			if(node->get_parent()== NULL) return NULL;
			if(is_left_child(node)) return node->get_parent()->get_right();
			return node->get_parent()->get_left();
		}

		bool has_colorchild(Node<T>* node, int _color){
			return ((node->get_left != NULL && node->get_left()->get_color()== _color) || (node->get_right()!= NULL && node->get_right()->get_color()== _color));
		}

		void print_leveorder(Node<T>* x){
			queue<Node<T>*> q;
			q.push(x);
			while(!q.empy()){
				Node<T>* curr= q.front();
				q.pop();
				if(curr == NULL){
					cout<<"(NIL) ";
				}else{
					cout << "(" << curr->get_key() << "," << printColorChar(curr->get_color()) << ") ";
					q.push(curr->get_left());
					q.push(curr->get_right());
				}
			}
		}


		void leftRotate(Node<T>* node){
			Node<T>* nParent = node->get_right(); // new parent will be node's right child 			
			insert_nodeup(node, nParent);		//if (node == root)	root = nParent;
			node->set_right(nParent->get_left());// connect x with new parent's left element 		
			if (nParent->get_left() != NULL) // connect new parent's left element with node  if it is not null 
				nParent->get_left()->set_parent(node);
			nParent->set_left(node); // connect new parent with x 
		}

		void rightRotate(Node<T>* node){
			Node<T>* nParent = node->get_left();// new parent will be node's left child 				
			insert_nodeup(node, nParent);// connect x with new parent's right element 		
			node->set_left(nParent->get_right());
			if (nParent->get_right() != NULL)// connect new parent's right element with node  if it is not null 		
				nParent->get_right()->set_parent(node);
			nParent->set_right(node);// connect new parent with x 
		}

		void swap_colors(Node<T>* node1, Node<T>* node2){
			int temp;
			temp = node1->get_color();
			node1->set_color(node2->get_color());
			node2->set_color(temp);
		}

		void swap_keys(Node<T>* node1, Node<T>* node2){
			T temp;
			temp = node1->get_key();
			node1->set_key(node2->get_key());
			node2->set_key(temp);
		}

		void insert_fixup(Node<T>* node){
			if(root== node){
				root->set_color=BLACK;
				return;
			}
			Node<T>* parent= node->get_parent();
			Node<T>* grandparent= parent->get_parent();
			Node<T>* uncle= get_uncle(node);
			if(parent->get_color== RED){
				if(uncle!= NULL && uncle->get_color== RED){
					parent->set_color(BLACK);
					uncle->set_color(BLACK);
					grandparent->set_color(RED);
					insert_fixup(grandparent);
				}else{ //rotations
					if(is_left_child(parent)){
						if(is_left_child(node)){
							swap_colors(parent, grandparent);
						}else{
							leftRotate(parent);
							swap_colors(node, grandparent);
						}
						rightRotate(grandparent);
					}else{
						if(is_left_child(node)){
							rightRotate(parent);
							swap_colors(node, grandparent);
						}else{
							swap_colors(parent, grandparent);
						}
						leftRotate(grandparent);
					}
				}
			}
		}

		Node<T>* cerca(T key){
			Node<T>* temp= root;
			while(temp != NULL && temp->get_key != key){
				if(key< temp->get_key()){				
					if(temp->get_left() !=NULL) temp=temp->get_left();
					else temp=NULL;
				}else{
					if(temp->get_right() != NULL) temp=temp->get_right();
					else temp=NULL;
				}
			}
			return temp;
		}			







































































































};

int main(){
}

