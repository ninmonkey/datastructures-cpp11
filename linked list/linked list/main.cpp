#include <iostream>
using namespace std;
/* todo

	- best c++ naming cases is?
	- gcc -Wall -Wextra or whatever else
	- use MAKE_SHARED vs shared_ptr ?
	- lint


About:
	Singly linked list. For production code use something like std::forward_list
*/

/*
class LinkedList {
		LinkedList() {}
	private:
	
}*/

struct Node {
	string data;
	Node *next;

	Node() : data("default"), next(nullptr) { }
};

int main() {
	
	Node * head = nullptr;
	Node n = Node();
	head = &n;

	if(head)
		cout << "yes" << endl;	
	
	cout << "Done." << endl;	
	cin.get();
	return 0;
}