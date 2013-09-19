#include <iostream>
#include <memory>
#include <string>

using namespace std;
/* todo

	- best c++ naming cases is?
	- gcc =c++11/0x -Wall -Wextra or whatever else
	- use `std::make_shared` vs shared_ptr ?
	- lint

	- I could have : singly list use unique_ptr but doubly use shared_ptr

About:
	Singly linked list. For production code use something like std::forward_list


make_shared

	rather than:
		std::shared<string> foo(new string("foo"));

	consider: ( http://stackoverflow.com/questions/14836691/is-it-better-to-use-shared-ptr-reset-or-operator/14837300#14837300 )
		std::shared<string> foo = std::make_shared<string>("foo");
		
	therefore, an assignment using `make_shared<>` is preferable (or even a statement such as
		reset(make_shared<T>())
			// or? make_shared<T>(args...).swap(mysharedptr);

	ref :
		started with, tried to improve: http://www.brpreiss.com/books/opus4/html/page89.html


	crit'q questions:
		- private: should I previx with _m or m_Foo etc? ( base: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml#Naming )
		- for single, use unique_ptr where double uses shared_ptr?
			( will not have cyclic so I won't need weak_ptr)
		- iter()? with std::next(begin) ?
		- typedef: http://stackoverflow.com/a/2697628/341744 c++0x http://stackoverflow.com/a/15989455/341744


== unit tests ==
	move datum private

	a) addToHead() called on empty list
	b) addToHead() called on non-empty list
	c) removeFromHead() called with list containing 0 elements;
	d) removeFromHead() called with list containing exactly 1 element;
	e) removeFromHead() called with list containing >1 element.
	f) addNode() called on empty list;
	g) addNode() called with list containing 1 element less than the value to insert;
	h) addNode() called with list containing 1 element greater than value to insert;
	i) addNode() called with list containing 1 element equal to value to insert;
	j) g, h, and i with list containing > 1 element;
	k) deleteNode() called on empty list;
	l) deleteNode() called on list with 1 element, target element does not exist;
	m) deleteNode() called on list with 1 element, target element exists;
	n) l and m with list containing >1 element;
	o) deleteAllNodes() called on empty list;
	p) deleteAllNodes() called on non-empty list;
	q) isEmpty() called on empty list;
	r) isEmpty() called on non-empty list;
	s) getNoOfNodes() called on initially empty list;
	t) getNoOfNodes() called on non-empty list;
	u) getNoOfNodes() called after addNode();
	v) getNoOfNodes() called after addToHead();
	w) getNoOfNodes() called after removeFromHead();
	x) getNoOfNodes() called after deleteNode();
	y) displayAllNodes() called on empty list;
	z) displayAllNodes() called on non-empty list.

*/


/*

struct Node {
	string data;
	std::shared_ptr<Node> next;

	Node() : data("default") { }
};

class LinkedList {
	std::shared_ptr<Node> head;
	int size_;

public:	
	LinkedList() : size_(0) { }	
	int size() { return size_; }
};
*/

///typedef NodePtr as std::shared_ptr<Node<T>> ?


template <class T>
class LinkedList;

template <class T> 
class Node
{
	std::shared_ptr<Node<T>> next;
	int size_;
public:
	typedef std::shared_ptr<Node<T>> PtrType;
	

	Node() : size_(0) {}

	Node(T const&, std::shared_ptr<Node<T>>);
//public:
	// should be private
	T datum_;

	int size() const { return size_; }
	T const& Datum () const;
	
	
	//todo: right type?	// his was:
		// ListElement const* Next () const;
	//std::shared_ptr<Node> const Next() const; 



	// he does:
	friend LinkedList<T>;
};

/* right typename def for c++0x, but not implemented in vs2012? 
template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;
*/

template <class T>
class LinkedList
{
	//Node::PtrType<T> head;
	//Node<string>::PtrType d1;

	// todo: use decl here?
	//auto d1 = std::make_shared<Node<string> >();
	//stNode<string> d1;
	
	//Node<T>::PtrType d1;
	std::shared_ptr<Node<T>> d1;

public:	
	LinkedList() {
		d1 = std::make_shared<Node<T>>();
		cout << "ll = ", d1->size(); << endl;
	}
};


/*
template <class T>
class LinkedList
{
	//Node::PtrType<T> head;
public:
	
	LinkedList();
	~LinkedList();

	LinkedList(LinkedList const&);
	LinkedList& operator=(LinkedList const&);

	Node::PtrType<T> const head() const;
	Node::PtrType<T> const tail() const;

	bool empty() const;
	Node::PtrType<T> first() const;
	Node::PtrType<T> last() const;

	void prepend(T const&);
	void append(T const&);
	//void extract(T const&);
	void clear();
//	void insert_after(Node::PtrType<T> const, T const& );
//	void insert_before(Node::PtrType<T> const, T const&);
};
*/






/*
template <class T>
void test_print(std::shared_ptr<Node<T>> list) {
	cout << "list len[" << list.size() << "] = \n\t" << endl;
	//auto head = list.head;
}
*/


int main() {
	//auto p = std::make_shared<string>();
	/*

	std::shared_ptr<Node> n0 = std::make_shared<Node>();
	auto n1 = std::make_shared<Node>();

	std::shared_ptr<Node> head(n0);

	n0->data = "1";
	n1->data = "2";

	cout << n0->data << endl;
	cout << n1->data << endl;
	*/

	auto p = std::make_shared<Node<string> >();
	//std::shared_ptr<Node <string>> n0 = std::make_shared<Node<string>>();
	auto n0 = std::make_shared<Node<string>>();

	//..
	//Node<string>::Type n1 = std::make_shared<Node<string>::Type>();
	/*
	std::shared_ptr<Node<string>> head(n0);
	*/
	n0->datum_ = "fred";
	//LinkedList<Node<string>> l = LinkedList<Node<string>::PtrType>();
	//test_print<Node<string>::PtrType>( l );


	LinkedList<string> l = LinkedList<string>();


	cout << "Done." << endl;	
	cin.get();
	return 0;
}
