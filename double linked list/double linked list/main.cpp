#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;
using std::string;

using std::shared_ptr;
using std::make_shared;


/* todo

	- best c++ naming cases is?
	- gcc =c++11/0x -Wall -Wextra or whatever else	
	- lint
	- ref: http://www.cplusplus.com/articles/Lw6AC542/


About:
	doubly linked list. For production code use something like std::forward_list or std::list

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
		- questions on new move semantics?
		- private: should I previx with _m or m_Foo etc? ( base: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml#Naming )
		- for single, use unique_ptr where double uses shared_ptr?
			( will not have cyclic so I won't need weak_ptr)
		- iter()? with std::next(begin) ?
		- typedef: http://stackoverflow.com/a/2697628/341744 c++0x http://stackoverflow.com/a/15989455/341744


== unit tests ==
	move datum private

	copy constructor
	assign operator

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
class DoubleList;

struct Node {
	string datum; 
	shared_ptr<Node> next;
	shared_ptr<Node> prev;

public:
	Node() : datum("default") {}
	Node( string const&, shared_ptr<Node> prev, shared_ptr<Node> next );
	~Node() {}

	// get/set data
	string data() const { return datum; }
	void data(string const& datum) { this->datum = datum; }

friend class DoubleList;
};

Node::Node(string const& datum, shared_ptr<Node> prev = nullptr, shared_ptr<Node> next = nullptr ) {
	this->prev = prev;
	this->next = next;
	this->datum = datum;
}

class DoubleList {
	int length;

	//head and tail start as nullptr
	shared_ptr<Node> head;
	shared_ptr<Node> tail;

	//void DoubleList::prepend( string const& datum ) {
	// Add node to start of list
	//void DoubleList::append( string const& datum ) {

	void freeNode(shared_ptr<Node> node);

public:
	DoubleList() : length(0) {}
	~DoubleList() {}

	// list size
	int size() const { return length; }
	bool empty() const { return size() == 0; }
	
	// erase all
	void clear();

	//todo:
	void erase(string const& datum); // or arg node vs datum?
	void erase(shared_ptr<Node> const& node);

	//todo: private?
	void addAtHead(string const& datum);
	void addAtTail(string const& datum);

	string removeAtHead();
	string removeAtTail();

	// ouptut for debug
	void print() const;
};

// free one node
void DoubleList::freeNode(shared_ptr<Node> node) {
	node->prev = nullptr;
	node->next = nullptr;
	
	// I think this causes the prev two lines to be redundant 
	node = nullptr; 
}

// free references
void DoubleList::clear() {
	auto cur = head;

	while(cur != nullptr) {
		auto last = cur;
		cur = cur->next;

		freeNode(last);			
	}

	head = nullptr;
	tail = nullptr;
	length = 0;
}

// remove from head
string DoubleList::removeAtHead() {
	length--;
	// todo: other code would return nullptr to shared_ptr<Node>
	if(head == nullptr)
		return "";

	string datum = head->data();

	head = head->next;
	if(head == nullptr)
		tail = nullptr;
	else
		head->prev = nullptr;

	return datum;
}

// remove from tail
string DoubleList::removeAtTail() {
	length--;
	// todo: decide since other code would return nullptr to shared_ptr<Node>
	if(tail == nullptr)
		return "";
	
	string datum = tail->data();

	tail = tail->prev;
	if(tail == nullptr)
		head = nullptr;
	else
		tail->next = nullptr;

	return datum;	
}

// append to tail
void DoubleList::addAtTail(string const& datum) {
	length += 1;

	auto node = make_shared<Node>(datum, tail, nullptr);

	if(tail != nullptr)
		tail->next = node;
	else
		head = node;

	tail = node;
}

// prepend head 
void DoubleList::addAtHead(string const& datum) {
	length += 1;

	auto node = make_shared<Node>(datum, nullptr, head);

	if(head != nullptr)
		head->prev = node;		
	else
		tail = node;	

	head = node;
}

// string for debug
void DoubleList::print() const {
	cout << "\nlist [" << size() << "] = \t";
	//todo: as c++11 for-each loop

	//todo: actual iter interface?	
	auto cur = head;
	while(cur != nullptr) {
		cout << cur->datum << ", ";
		cur = cur->next;
	}
	
	cout << endl;
	if(head != nullptr)
		cout << "head=" << head->datum;
	if(tail != nullptr)
		cout << " , tail=" << tail->datum << endl;
}

// generate basic list for test
DoubleList test_build5() {
	DoubleList list = DoubleList();

	list.addAtHead("fred");
	list.addAtHead("bob");
	list.addAtHead("hank");
	list.addAtTail("sally");
	list.addAtTail("jane");

	//todo: assertEquals: hank, bob, fred, sally, jane

	return list;
}
int main() {
	

	auto list1 = DoubleList();

	/* todo: convert to unit tests */

	auto list2 = test_build5();
	list2.print();

	auto n1 = list2.removeAtHead();
	auto n2 = list2.removeAtHead();

	cout << "removeAtHead() x2 = " << n1 << ", " << n2 << endl;
	list2.print();

	n1 = list2.removeAtTail();
	n2 = list2.removeAtTail();

	cout << "removeAtTail() x2 = " << n1 << ", " << n2 << endl;
	list2.print();

	
	list2 = test_build5();	

	cout << "Empty (should be no)= ";
	if(list2.empty()) cout << "yes";
	else cout << "no";
	cout << endl;	

	cout << "clear()" << endl;
	list2.clear();
	list2.print();

	// invalid removes
	n1 = list2.removeAtHead();
	n2 = list2.removeAtTail();

	cout << "Empty (should be yes) = ";
	list2.clear();
	if(list2.empty()) cout << "yes";
	else cout << "no";
	cout << endl;

	cout << "Done." << endl;	
	std::cin.get();
	return 0;
}
