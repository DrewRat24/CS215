#include "contact.h"

contact::contact() { number = ""; name = "EMPTY"; }
string contact::getName(){ return name; }
string contact::getNumber() { return number; }

void contact::setName(string n) { name = n; }
void contact::setNumber(string s) { number = s; }
void contact::print() {
	cout << number << setw(12) << " " << name << endl;
}
