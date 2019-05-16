//-------------------------------------------------------------------
//                      CS 215 - Spring 2019
//                            Lab 9 
//-------------------------------------------------------------------
// Name:        Drew Ratliff
// Section:     011
// Description: Implementation of a dynamic stack class
//-------------------------------------------------------------------

#include <iostream>
using namespace std;

// CLASS NODE INTERFACE
class node {
public:
	friend class stack; // allow methods of class stack to access private members
	node();			    // give initial values to data members
private:
	int  data;			// data for this node
	node * next;		// pointer to the next node in the list
};
node::node() { data = 0; next = NULL; }


// CLASS STACK INTERFACE
class stack {
public:
	stack();			// init stack to empty stack
	void push(int x);	// allocate a new node, copy x into it, put it on the top of the stack
	int  pop();			// deallocate the top node and return the data that was in it.
						// print "Stack empty" and return 0 when the stack is empty.
	void print();		// print the data of all nodes, left to right, starting with the top.
private:
	node * top;			// pointer to top node of the stack, or NULL when stack is empty
};

stack::stack() { top = NULL; }
void stack::push(int x) {
	node * p = new node;
	p->data = x;
	p->next = top;
	top = p;
} // push()

int stack::pop() {
	if (top == NULL) {
		cout << "Stack empty" << endl;
		return 0;
	}

	int oldData = top->data;
	node * p = top;
	top = top->next;
	delete p;
	return oldData;
} // pop()

void stack::print() {
	cout << "STACK <top first>: ";
	node * p = top;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
} // print()


// MAIN
int main() {
	stack s;
	int data, opt = 0;
	const int exit = 4;
	while (opt != exit) {
		cout << "\n1. Push\n2. Pop\n3. Print\n4. Exit\n===> ";
		cin >> opt;
		switch (opt) {
		case 1: cout << "Enter data to push: ";
			cin >> data;
			s.push(data);
			break;
		case 2: data = s.pop();
			cout << "Popped: " << data << endl;
			break;
		case 3: s.print(); break;
		case exit: cout << "Bye!\n"; break;
		default:   cout << "Invalid option, try again\n";
		}
	}
	system("pause");
	return 1;
}
