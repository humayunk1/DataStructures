/* This file contains an implementation of a singly list
 * Code by: Humayun Kabir, humayun.k1@gmail.com */ 


#include <iostream> 

using namespace std;


//Node of a LinkedList
template<class T>
struct Node {
	T val;
	Node *next;

	Node() {}
	Node(const T& t, Node *p) : val(t), next(p) {}

	//destructor
	~Node() {
		delete next;
	}
};

//iterator classes for LinkedList
template<class T>
class ListIter;

template<class T>
class constListIter;


//class to represent linked list
template<class T>
class LinkedList {
	friend class ListIter<T>;
	friend class constListIter<T>;
private:
	Node<T> *head;
	int Size;
public:
	typedef ListIter<T> iterator;
	typedef constListIter<T> const_iterator;

        typedef std::forward_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef T value_type;
        typedef T * pointer;
        typedef T & reference;

	//default constructor
	LinkedList();

	//insert an element into the list
	void insert(T inVal);

	//adds an element into the list
	void add(T inVal) { insert(inVal); }

	//deletes the head and retuns the value it contains
	T delVal();

	//checks if the list is empty
	bool isEmpty();

	//returns the number of elements in the list
	int size() { return Size; }

	//returns iterator initializing to the beginning of the list
	iterator begin() { return iterator(head); }

	//returns iterator initializing to the end of the list
	iterator end() { return iterator(NULL); }

	//returns constant iterator initializing to the beginning of the list
	const_iterator begin() const { return const_iterator(head); }

	//returns constant iterator initializing to the end of the list
	const_iterator end() const { return const_iterator(NULL); }

	~LinkedList() {
		delete head;
	}
};


//default constructor
template<class T>
LinkedList<T>::LinkedList() {
	head = NULL;
	Size = 0;
}

//insert an element into the list
template<class T>
void LinkedList<T>::insert(T inVal) {
	Node<T> *oldHead = head;

	head = new Node<T>(inVal, oldHead);
	Size ++;
}

//deletes the head and retuns the value it contains
template<class T>
T LinkedList<T>::delVal() {

	try {
		if( head == NULL ) {
			throw string("Can't delete from empty list.");
		}
		else {
			T retVal = head->val;
			Node<T>* tempHead = head;
			head = head->next;

			tempHead->next = NULL;
			delete tempHead;
			Size--;
			return retVal;
		}
	}
	catch (string s) {
		cout<<s<<endl;
	}
	catch(...) {
		cout<<"Unhandled exception. \n";
	}
}

//checks if the list is empty
template<class T>
bool LinkedList<T>::isEmpty() {
	return head == NULL;
}



//ListIter class
template<class T>
class ListIter {

private:
//	Node<T>* head;

public:
	Node<T>* head;
	
	//constructor
	ListIter(Node<T>* x = 0) : head(x) {}

	//equality operator
	bool operator==(const ListIter<T> &rhs) {
		if( head == rhs.head )
			return true;
		else 
			return false;
	}

	//not equal to operator
	bool operator!=(const ListIter<T> &rhs) {
		return !(*this == rhs);
	}

	//dereference operator
	T & operator*() { return head->val; }

	//Prefix increment -- ++iter
	ListIter<T> & operator++() { 
		head = head->next; 
		return *this; 
	}	

	//Postfix increment -- iter++
	ListIter<T> operator++(int) {
		ListIter<T> clone(*this);
		head = head->next;
		return clone;	
	}
};

//constListIter class
template<class T>
class constListIter {
private:
	const Node<T>* head;
         typedef std::forward_iterator_tag iterator_category;
         typedef std::ptrdiff_t difference_type;
         typedef size_t size_type;
         typedef T value_type;
         typedef const T * pointer;
         typedef const T & reference;

public:
	//Constructor
	constListIter(Node<T>* x = 0) : head(x) { }
	
	//Copy constructor
        constListIter(const ListIter<T> & rhs) : head(rhs.head) { }

	//equality operator
	bool operator==(const constListIter<T> & rhs) {
		return head == rhs.head;
        }

	//not equal to operator
        bool operator!=(const constListIter<T> & rhs) {
		return !(*this == rhs);
	}

	//dereference operator
	reference operator * () const { return head->val; }

	pointer operator->() const { return &(head->val); }

	//Prefix increment -- ++iter
	constListIter& operator++() const { 
		head = head->next; 
		return *this;
	}

	//Postfix increment -- iter++
        constListIter operator++(int) {
		constListIter clone(*this);
		head = head->next;
		return clone;
	}
};	

//Test the data structure
int main() {

	LinkedList<int> lList;

	lList.insert(10);
	lList.insert(5);
	lList.insert(50);

	cout<<"Values in the list: \n";
	for(LinkedList<int>::iterator it = lList.begin(); it != lList.end(); it++)
		cout<<*it<<endl; 

	cout<<"Deleted a Value: "<<lList.delVal()<<endl;

	cout<<"Values in the list: \n";
	for(LinkedList<int>::const_iterator it = lList.begin(); it != lList.end(); it++)
		cout<<*it<<endl; 

	return 0; 
}
