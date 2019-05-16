//-------------------------------------------------------------------
//                      CS 215 - Spring 2019
//                            Lab 8 
//-------------------------------------------------------------------
// Name:        Drew Ratliff
// Section:     011
// Description: Test driver program for the contact and contactList
//              classes
//-------------------------------------------------------------------
#include <iostream>
#include "contact.h"
#include "contactList.h"

using namespace std;

const int EXIT_OPT = 7;

//------------------------------------------------------------
//							getOpt
//------------------------------------------------------------
int getOpt() {
	int opt = 0;
	cout << "\n1. Add contact\n";
	cout << "2. Get contact by index\n";
	cout << "3. Search by name\n";
	cout << "4. Print contact list\n";
	cout << "5. Name the list\n";
	cout << "6. Get contact list stats\n";
	cout << "7. Exit\n";
	cout << "Enter option: ";
	cin >> opt;
	cin.ignore();
	return opt;
}

//------------------------------------------------------------
//							testAddContact
//------------------------------------------------------------
void testAddContact(contactList & list) {
	string name, phone;
	contact c;
	cout << "Enter new contact name:  ";
	getline(cin, name);
	cout << "Enter new contact phone: ";
	getline(cin, phone);

	c.setName(name);
	c.setNumber(phone);
	list.addContact(c);
} // testAddContact()

//------------------------------------------------------------
//							testByIndex
//------------------------------------------------------------
void testByIndex(contactList & list) {
	int index;
	contact c;
	cout << "Enter index: ";
	cin >> index;
	cin.ignore();
	c = list.getContact(index);
	c.print();
} // testByIndex()

//------------------------------------------------------------
//							testSearch
//------------------------------------------------------------
void testSearch(contactList & list) {
	string name;
	contact c;
	cout << "Enter search name: ";
	getline(cin, name);
	if (list.searchByName(name) == -1)
		cout << "Not Found" << endl;
	else {
		c = list.getContact(list.searchByName(name));
		c.print();
	}
} // testSearch()

//------------------------------------------------------------
//							testSetName
//------------------------------------------------------------
void testSetName(contactList & list) {
	string name;
	cout << "Enter list name: ";
	getline(cin, name);
	list.setName(name);
} // testSetName()

//------------------------------------------------------------
//							testGetStats
//------------------------------------------------------------
void testGetStats(contactList & list) {
	cout << "Number of Contacts: " << list.getNumContacts()
		<< "\nName of List:       " << list.getName() << endl;;
} // testGetStats()

//------------------------------------------------------------
//							main
//------------------------------------------------------------
int main() {
	contactList list;
	int option = 0;
	while (option != EXIT_OPT) {
		option = getOpt();
		switch (option) {
		case 1: testAddContact(list); break;
		case 2: testByIndex(list);    break;
		case 3: testSearch(list);     break;
		case 4: list.print();		  break;
		case 5: testSetName(list);    break;
		case 6: testGetStats(list);   break;
		case EXIT_OPT: cout << "Thanks for playing!\n"; break;
		default: cout << "Invalid option, try again\n";
		} // end switch
	} // end while not EXIT option

	system("pause");
	return 0;
} // main()
