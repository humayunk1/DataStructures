/*This file contains an implementation of binary search tree
 * Code by: Humayun Kabir, humayun.k1@gmail.com */

#include <iostream>
#include "queue.cpp"

using namespace std;


//a struct to represent tree node
template <class Key, class Value>
struct treeNode {
	Key key;
	Value val;
	treeNode *left, *right;
	int count;

	//default constructor
	treeNode() : count(0), left(NULL), right(NULL) {
	}

	//constructor
	treeNode(Key key, Value val, int count) : key(key), val(val), count(count), left(NULL), right(NULL) {
	}

	//destructor
	~treeNode() {
		delete left;
		delete right;
	}
};

//a class to represent binry search tree
template<class Key, class Value>
class BST {
private:
	treeNode<Key,Value> *root;

	//returns the number of nodes in the tree rooted at x
	int size(treeNode<Key,Value> *x) {
		if(x == NULL) 
			return 0;
		return 	
			x->count;
	}

	//recursively inserts a node in the tree rooted at x
	treeNode<Key,Value> *insert(treeNode<Key,Value> *x, Key key, Value val) {
		if(x == NULL) 
			return new treeNode<Key,Value>(key, val, 1);

		if( key < x->key)
			x->left = insert(x->left, key, val);
		else if( key > x->key)
			x->right = insert(x->right, key, val);
		else 
			x->val = val;

		x->count = 1 + size(x->left) + size(x->right);

		return x;
	}	

	//inorder traversal of a tree rooted at x
        void inorder(treeNode<Key,Value> *x, Queue<Key> & q) {
		if(x == NULL) 
			return;

		inorder(x->left,q);
		q.Enqueue(x->key);
		inorder(x->right,q);
        }

	//preorder traversal of a tree rooted at x
        void preorder(treeNode<Key,Value> *x, Queue<Key> & q){
		if( x == NULL) 
			return;

		q.Enqueue(x->key);
		preorder(x->left, q);
		preorder(x->right, q);
        }

	//delete the minimum element from the tree rooted at x
        treeNode<Key,Value> *deleteMin(treeNode<Key,Value> *x, bool fromDel) {
		if( x == NULL)
			return NULL;
	
		if(x->left == NULL) {
			treeNode<Key,Value> *retNode = x->right;
			if( !fromDel ) { 
				x->right = NULL;
				delete x; 
			}
			return retNode;
		}
		x->left = deleteMin(x->left, fromDel);
		x->count = 1 + size(x->left) + size(x->right);

		return x;
        }

	//finds the key with minimum value in the tree rootted at x
        treeNode<Key,Value> *min(treeNode<Key,Value> *x) {
		if(x == NULL) 
			return NULL;
		while(x->left != NULL) {
			x = x->left;
		}
		return x;
        }
	
	//deletes a node with Key key from the tree rooted at x 
        treeNode<Key,Value> *Delete(treeNode<Key,Value> *x, Key key) {
		if(x == NULL)  
			return NULL;
		//delete the key from left subtree if it is less than the root
		if( key < x->key)
			x->left = Delete(x->left, key);
		//delete the key from right subtree if it is greater than the root
		else if(key > x->key)
			x->right = Delete(x->right, key);
		//if key is equal to the key of the root
		else {
			//if left subtree is empty return right subtree
			if(x->left == NULL) {
				treeNode<Key,Value> *retNode = x->right;
				x->right = NULL;
				delete x;
				return retNode; 
			}
			//if right subtree is empty return left subtree
			if(x->right == NULL) {
				treeNode<Key,Value> *retNode = x->left;
				x->left = NULL;
				delete x;
				return retNode; 
			}


			//if both the subtrees are non-empty
			treeNode<Key,Value> *t = x;

			//x is replaced by the minimum element of the right subtree
			x = min(t->right);
			x->right = deleteMin(t->right, true);
			x->left = t->left;
			t->left = NULL;
			t->right = NULL;
			delete t;
		}
		x->count = size(x->left) + size(x->right) + 1;
		return x;
	}

	//postorder traversal of the tree
        void postorder(treeNode<Key,Value> *x) {
		if(x == NULL) 
			return;
		postorder(x->left);
		postorder(x->right);
		cout<<"Key: "<<x->key<<"  Val: "<<x->val<<endl;
        }


	//inorder traversal of the tree
	void inorder(treeNode<Key, Value> *x) {
		if( x == NULL ) 
			return;
		inorder(x->left);
		cout<<"Key: "<<x->key<<"  Val: "<<x->val<<endl;
		inorder(x->right);
        }	

public:
	//default constructor 
        BST() {
		root = NULL;
        }

	//returns number of elements in the tree
	int size() {
		return size(root);
	}

	//insert a node in the BST with given key and value
	void insert(Key key, Value val) {
		root = insert( root, key, val);
	}

	//returns the keys in the tree
        Queue<Key> keys() {
		Queue<Key> q;
		inorder(root, q);
		return q;
        }

	//search for a node with given key in the tree
        treeNode<Key,Value> *search(Key key){
		treeNode<Key,Value> *x = root;

		while( x != NULL ) {
			if(key < x->key)
				x = x->left;
			else if(key > x->key)
				x = x->right;
			else
				return x;
		}
		return NULL;
        }

	//delets the minimum element in the tree
        void deleteMin() {
		root = deleteMin(root, true);
        }

	//deletes a given key from the tree
        void Delete(Key key) {
		root = Delete(root, key);
        }

	//postorder traversal of the tree
	void postorder() {
		this->postorder(root);
        }

	//inorder traversal of the tree
        void inorder() {
		this->inorder(root);
        }


	//destructor
	~BST() {
		delete root;
	}
};


//Test the data structure
int main(int argc, char *argv[]) {

	BST<int,string> bst;

	bst.insert(1, "hello1");
	bst.insert(10, "hello10");
	bst.insert(-4, "hello-4");
	bst.insert(40, "hello40");

	cout<<"Size of the tree: "<<bst.size()<<endl;
	cout<<"Inorder traversal."<<endl;
	bst.inorder();
	bst.Delete(1);
	cout<<"after deleting key: 1\n";
	cout<<"Size of the tree: "<<bst.size()<<endl;
	cout<<"Inorder traversal."<<endl;
	bst.inorder();

	return 0;
}
