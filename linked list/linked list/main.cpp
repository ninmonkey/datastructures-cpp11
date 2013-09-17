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
*/

/*
class LinkedList {
		LinkedList() {}
	private:
	
}*/

struct Node {
	string data;
	std::shared_ptr<Node> next;

	Node() : data("default") { }
};

class LinkedList {
	std::shared_ptr<Node> head;
	int _size;
public:
	LinkedList() : _size(0) { }	

	int size() { return _size; }
};

int main() {
	//auto p = std::make_shared<string>();


	std::shared_ptr<Node> n0 = std::make_shared<Node>();
	auto n1 = std::make_shared<Node>();

	std::shared_ptr<Node> head(n0);

	n0->data = "1";
	n1->data = "2";

	cout << n0->data << endl;
	cout << n1->data << endl;







	cout << "Done." << endl;	
	cin.get();
	return 0;
}
