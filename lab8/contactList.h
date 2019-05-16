#pragma once
#include "contact.h"
using namespace std;
class contactList {
public:
	contactList();
	void setName(string n);
	string getName();
	int getNumContacts();
	void addContact(contact c);
	int searchByName(string b);
	contact getContact(int i);
	void print();
private:
	contact x[5];
	int numContacts;
	string name;
};