#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
class contact {
public:
	contact();
	string getName();
	string getNumber();
	void setName(string n);
	void setNumber(string s);
	void print();
private:
	string name, number;
};