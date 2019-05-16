#include "contactList.h"
#include <iostream>

contactList::contactList() { name = "NONE"; numContacts = 0; }
void contactList::setName(string n) { name = n; }
string contactList::getName() { return name; }
int contactList::getNumContacts() { return numContacts; }

void contactList::addContact(contact c) {
	if (numContacts < 5) {
		x[numContacts] = c;
		numContacts++;
	}
	else {
		cout << "contactList::addContact(): max contacts exceeded!" << endl;
		cout << c.getName() << " not added" << endl;
	}
} // addContact()

int contactList::searchByName(string b) { 
	for (int i = 0; i < numContacts; i++) {
		if (b == x[i].getName())
			return i;
	}
	return -1; 
} // searchByContact()

contact contactList::getContact(int i) {
	if (i <= numContacts-1)
		return x[i];
	else {

	}

} // getContact()

void contactList::print() {
	cout << "List: " << getName() << " (" << numContacts << " contacts)" << endl;
	for (int i = 0; i < numContacts; i++) {
		x[i].print();
	}
} // print()

