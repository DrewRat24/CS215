//-----------------------------------------------------------
// CS 215-011 – Project 1            Section 11
//-----------------------------------------------------------
// Author: Drew Ratliff
// Date: 2/5/2019
// Description: Create a gas pump reader.
// Assistance: I received help from no one.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

int main() {
	double hi_tank, med_tank, low_tank, hi_price, med_price, low_price, discount;
	double octane, gallons, sensor, gallons_pumped, last_number, hi_discount=0, med_discount, low_discount;
	int rewards;
	string option, octane_selection, octane_name;

	//connection to input file for gas prices and tank levels
	ifstream fin;
	fin.open("pumpin.txt");
	if (fin.fail()) {
		cout << "Unable to read input file.\n";
		return 0;
	}
	fin >> hi_tank >> med_tank >> low_tank
		>> hi_price >> med_price >> low_price;
	fin.close();

	cout << fixed << setprecision(2) << "Tank Readings: Hi=" << hi_tank << "    Med=" << med_tank << "    Low=" << low_tank << endl;
	cout << fixed << setprecision(2) << "Today's PPG:   Hi=$ " << hi_price << "  Med=$ " << med_price << "    Low=$ " << low_price << endl;
	cout << endl;

	//while loop for whole program to loop until shutdown
	while (option != "Shutdown") {
		cout << "+-------------------------------------------------------+" << endl;
		cout << "|          WELCOME TO HUCKABILLY'S SELF SERVE!          |" << endl;
		cout << "|                  Drew Ratliff, Owner                  |" << endl;
		cout << "+-------------------------------------------------------+" << endl;
		cout << "Are you a rewards customer? (Y/N): ";
		cin >> option;

		//new variable for prices after discount so there are consistent prices
		hi_discount = hi_price;
		med_discount = med_price;
		low_discount = low_price;

		//capitalize first letter
		option[0] = toupper(option[0]);

		//shutdown/option if statement
		if (option == "Shutdown") {
			break;
		}
		else if (option != "Y" && option != "N") {
			cout << "Please enter Y or N" << endl;
		}

		//while loop for incorrect variable input from user
		while (option != "Y" && option != "N") {
			cout << "Are you a rewards customer? (Y/N): ";
			cin >> option;
			option[0] = toupper(option[0]);
			if (option == "Y" || option == "N") {
				break;
			}
			else if (option != "Y" && option != "N") {
				cout << "Please enter Y or N." << endl;
			}
		}

		//if statement for customer discount
		if (option == "Y") {
			cout << "Enter customer rewards number:     ";
			cin >> rewards;
			rewards = rewards % 10;
			discount = rewards;
			discount = (discount + 1) / 100;
			cout << "Price Per Gallon Discount:         $" << discount << endl;
			cout << endl;
			hi_discount = hi_price - discount;
			med_discount = med_price - discount;
			low_discount = low_price - discount;
		}
		else if (option == "N") {
			discount = 0.00;
			cout << "Price Per Gallon Discount:         $" << discount << endl;
			cout << endl;
		}

		cout << "Prices Per Gallon:" << endl;
		cout << "High Octane:   $ " << hi_discount << endl;
		cout << "Medium Octane: $ " << med_discount << endl;
		cout << "Low Octane:    $ " << low_discount << "\n\n";

		cout << "Select octane (H/M/L): ";
		cin >> octane_selection;
		octane_selection[0] = toupper(octane_selection[0]);

		//while loop for octane selections
		while (octane_selection != "H" && octane_selection != "M" && octane_selection != "L") {
			cout << "Please enter H, M, or L." << endl;
			cout << "Select octane (H/M/L): ";
			cin >> octane_selection;
			octane_selection[0] = toupper(octane_selection[0]);
		}

		cout << endl;
		cout << "Enter number of gallons (-1 to Fill it up): ";
		cin >> gallons;

		//if statement to link the octane selection to the proper tank
		if (octane_selection == "H") {
			octane = hi_tank;
		}
		else if (octane_selection == "M") {
			octane = med_tank;
		}
		else {
			octane = low_tank;
		}

		//if statement for empty tank
		if (gallons > octane) {
			cout << "Sorry, our tank is nearly empty. We only have " << octane << " gallons available." << endl;
			gallons = octane;
		}
		else if (gallons < 0) {
			sensor = rand() % 7;
			sensor = sensor + 1;
			cout << "Sensor reports " << sensor << " gallons needed to fill up." << endl;
			gallons = sensor;
		}

		cout << endl;
		cout << "Pumping gas..." << endl;
		gallons_pumped = 0;

		//for loop to run requested amount of gas
		for (double i = 0.5; i <= gallons; i = i + 0.5) {
			cout << i << " gallons pumped..." << endl;
			last_number = i;
			Sleep(2000);
		}

		//prints last number if the for loop doesn't reach it evenly
		if (last_number != gallons) {
			cout << gallons << " gallons pumped..." << endl;
		}

		double ppgallon, total;

		//if statement for calculating price of gas depending on octane
		if (octane_selection == "H") {
			hi_tank = hi_tank - gallons;
			octane_name = "High";
			ppgallon = hi_discount;
		}
		else if (octane_selection == "M") {
			med_tank = med_tank - gallons;
			octane_name = "Medium";
			ppgallon = med_discount;
		}
		else {
			low_tank = low_tank - gallons;
			octane_name = "Low";
			ppgallon = low_discount;
		}
		total = ppgallon * gallons;

		//receipt lines
		cout << endl;
		cout << "----------- Your Receipt -----------" << endl;
		cout << "Octane:            " << octane_name << endl;
		cout << "Price per gallon:  $  " << ppgallon << endl;
		cout << "Total:             $  " << total << endl;
		cout << "Thank you for visiting Huckabilly's!!" << endl;
		cout << endl;
		cout << "------------------------------------" << endl;

		//pause for end of pump cycle
		system("pause");
		cout << endl;
	}
	//display tank readings after shutdown
	cout << "Tank Readings: Hi=" << hi_tank << "  Med=" << med_tank << "  Low=" << low_tank << endl;
	cout << "Pump shut down." << endl;

	//write tank readings to pumpout file
	ofstream fout;
	fout.open("pumpout.txt");
	if (fout.fail()) {
		cout << "Unable to open output file" << endl;
	}
	fout << hi_tank << " " << med_tank << " " << low_tank;
	fout.close();

	system("pause");
	return 0;
}
