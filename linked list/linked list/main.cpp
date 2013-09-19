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
class LinkedList;

struct Node {
	//todo:move private: string datum;
	std::shared_ptr<Node> next;

	Node() : datum("default") {}
	Node( string const&, std::shared_ptr<Node>);
public:
	string datum;
	//todo: move public: string const& datum() const { return datum_; }

	friend LinkedList;
};

class LinkedList {
	int size_;

public:
	LinkedList() : size_(0) {}
	int const size() const { return size_; }
};

void test_print(LinkedList const& list) {
	cout << "list [" << list.size() << "] = \n\t" << endl;
}

int main() {
	auto n1 = make_shared<Node>();
	auto n2 = make_shared<Node>();

	LinkedList list = LinkedList();

	test_print(list);
	

	cout << "Done." << endl;	
	cin.get();
	return 0;
}
