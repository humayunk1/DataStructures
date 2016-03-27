/* This file contains an implementation of a Queue - a first in first out (FIFO) data structure
 * This contains an iterator as well 
 * Code by: Humayun Kabir, humayun.k1@gmail.com */

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//a node structure 
template<class T>
struct Node {
   T val;
   Node *next;

   Node() {}
   Node(const T& t, Node *p) : val(t), next(p) {}
};

//Iterator class
template<class T>
class QueueIter;

//Queue class
template<class T>
class Queue {
	friend class QueueIter<T>;
private:
	Node<T> *head, *tail;
	int Size;

public:
	typedef QueueIter<T> iterator;
	
	//begin function
	iterator begin() { return iterator(head); }
	
	//end function
	iterator end() { return iterator(tail->next); }

	//Default constructor
	Queue() {
		head = tail = NULL;
		Size = 0;
	}

	//inserts a new element into the queue
	void Enqueue(T inVal) {
		Node<T>* newNode = new Node<T>();
		newNode->val = inVal;
		newNode->next = NULL;

		if( head == NULL )  {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		Size++;
	}

	//deletes and returns the oldest element from the queue
	T Dequeue() {
		try {
			if(head != NULL) {
				//There is only one element in the queue
				if( head == tail ) {
					T retVal = head->val;
					Node<T>* tempHead = head;
					head = tail = NULL;
					delete tempHead;
					Size--;
					return retVal;
				}
				else { //there are more than one element in the queue
					T retVal = head->val;
					Node<T>* tempHead = head;
					head = head->next;
					Size--;
					delete tempHead;
					return retVal;
				}
			}
			else {
				throw string("Queue: Underflow");
			}
		}
		catch(string s) {
			cout<<s<<endl;
		}
		catch(...) {
			cout<<"Undefined exception occurred"<<endl;
		}
	}

	//returns number of elements in the queue
	int size() { return Size; }

	//checks if the queue is empty
	bool isEmpty() { return Size == 0; }

	//Destructor
	~Queue() {
		while( head != NULL ) {
			delete head;
			head = head->next;
		}
	}
};


//Queue Iterator class
template<class T>
class QueueIter {
private:
	Node<T> *head;

public:
        typedef std::forward_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef T value_type;
        typedef T * pointer;
        typedef T & reference;

	//Constructor
        QueueIter(Node<T> *x = 0) : head(x) {}

	//Equality operator
        bool operator==(const QueueIter & rhs) {
            return head == rhs.head;
        }

	//not equal to operator
        bool operator != (const QueueIter & rhs) {
           return !(*this == rhs);
        }
	
	//dereference operator
        reference operator*() { return head->val; }

        //prefix increment operator-- ++iter
        QueueIter & operator++(){ head = head->next; return *this; }

        //Postfix increment operator-- iter++
        QueueIter operator++(int) {
		QueueIter clone(*this);
		head = head->next;
		return clone;
        }
};        



//Test the data structure
int main() {
	Queue<int> aQueue;

	srand( time(NULL) );

	int length = 5;
	
	//generate 5 random number and insert into queue
	for(int i = 0; i < length; i++) {
		aQueue.Enqueue( rand() % 100 );
	}	

	//Queue contains
	cout<<"The queue contains: \n";
	for(Queue<int>::iterator it = aQueue.begin(); it != aQueue.end(); it++)
		cout<<*it<<endl; 	
	

	//Delete an element from the queue
	cout<<"Dequeue an element: \n";
	cout<< aQueue.Dequeue() <<endl;		

        //Queue contains
        cout<<"Now the queue contains: \n";
        for(Queue<int>::iterator it = aQueue.begin(); it != aQueue.end(); it++)
        	cout<<*it<<endl;

	return 0;
}
