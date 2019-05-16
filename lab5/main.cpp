//------------------------------------------------------------
//                      CS215-011 LAB 5
//------------------------------------------------------------
// Author: Drew Ratliff
// Date: 2/18/19
// Description: Allow user to choose one of three games to play
//------------------------------------------------------------

#include <iostream>
#include <string>

using namespace std;

int main() {
	int num1 = 0, num2 = 0, sum=0, box_size, cap=0, row=0, counter=0;
	char option;

	//do while loop so it runs at least once
	do {
		cout << "S - Sum Between" << endl;
		cout << "B - Print Box  " << endl;
		cout << "X - Exit       " << endl;
		cout << "Enter option : ";
		cin >> option;

		switch (option){
		//case for start and stop number game
		case 'S':
		case 's':
			cout << "Enter start and stop numbers: ";
			cin >> num1 >> num2;
			for (int i = num1; i <= num2; i++) {
				sum = sum + (num1 + counter);
				counter++;
			}
			cout << "Sum of numbers between those is: " << sum << endl << endl;
			counter = 0;
			sum = 0;
			break;
		//case for the box sizes
		case 'B':
		case 'b':
			cout << "Enter box size: ";
			cin >> box_size;
			while (row < box_size*box_size) {
				if (cap >= box_size) {
					cout << endl;
					cap = 0;
				}
				cout << "* ";
				cap++;
				row++;
			}
			cout << endl << endl;
			break;
		//case for exiting the game
		case 'X':
		case 'x':
			cout << "Thanks for playing!" << endl;
			break;
		//default case for if there isn't a valid option entered
		default:
			cout << "Invalid option, try again!" << endl << endl;
			break;
		}
	} while (option != 'X' && option != 'x');

	system("pause");
	return 0;
}
