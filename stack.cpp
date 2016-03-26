/* This file defines a generic Stack - a last in first out (LIFO) data structure.
 * This data structure supports the operations - (a) push, (b) pop, (c) peek 
 * Author: Humayun Kabir, humayun.k1@gmail.com */

#include <iostream>

using namespace std;

//A structure to represent a node of a LinkedList
template<class T>
struct Node {
	T val;
	Node *next;

	Node() {}
	Node(const T& t, Node *p) : val(t), next(p) {}
};


//Stack class
template<class T>
class Stack {

private:
	Node<T>* head;
	int Size; //Represents number of elements on the stack

public:
	Stack() {  //Default constructor
		head = NULL; 
		Size = 0; 
	}

	//Pushes a new element on to the stack
	void push(T val) {
		Node<T>* oldHead = head;
		head = new Node<T>();
		head->val = val;
		head->next = oldHead;
		Size ++;
	}

	//Pops an element from the top of the stack
	T pop() {
		try {
			if( Size >= 1 ) {
				T retVal = head->val;
				Node<T>* tempHead = head;
				head = head->next;
				delete tempHead;
				Size--;
				return retVal;
			}
			else 
				throw string("Stack underflow.\n");
		}
		catch(string s) {
			cout<<s<<endl;
		}
		catch(...) {
			cout<<"Unknown-exception occurred"<<endl;
		}
	}


	//Returns the element from the top of the stack
	T peek() {
		try {
			if( Size >= 1 ) {
				T retVal = head->val;
				return retVal;
			}
			else
				throw string("In peek() ::Stack underflow.\n");
		}
		catch(string s) {
			cout<<s<<endl;
		}
		catch(...) {
			cout<<"Unknown-exception occurred"<<endl;
		}
	}

	//Returns the size of the stack
	int size() { return Size; }

	//Checks if the stack is empty
	bool isEmpty() { return Size == 0; }

	//Prints all the elements on the stack
	void iterate() {
		Node<T>* tempHead = head;
		while( tempHead != NULL ) {
			cout<<tempHead->val<<endl;
			tempHead = tempHead->next;
		}
	}

	//Destructor
	~Stack() {
		while( head != NULL ) {
			delete head;
			head = head->next;
		}
	}
};



//Test the data structure
int main() {

	Stack<int> s;

	//push some values
	s.push(5);
	s.push(10);
	s.push(15);

	//Print the content
	cout<<"The stack contains: \n";
	s.iterate();

	//Pop an element
	cout<<"The top element is popped: " <<s.pop()<<endl;
	
	//Print the content
	cout<<"The stack contains: \n";
	s.iterate();

	return 0;
}
