//------------------------------------------------------------
//                      CS215-011 LAB 3
//------------------------------------------------------------
// Author: Drew Ratliff
// Date: 2/4/19
// Description: 
//------------------------------------------------------------

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main (){
const float HotDog=2.50, Small_Drink=1.50, Large_Drink=2.25, Deluxe_HotDog=3.50, tax=0.06;
float tax_total = 0.00, cash = 0.00, change = 0.00, Sub_Total = 0.00, total = 0.00;
string choice;

//outputs to two decimal points
cout << fixed;
cout << setprecision(2);

cout << "---- Drew's Hot Dogs & Drinks ----\n";

//do while loop
    do { 
		//if statement for title when finishing order and repeating loop
		if (choice[0] == 'F') {
			cout << "---- Drew's Hot Dogs & Drinks ----\n";
		}

    cout << "H - Hot Dog      $" << HotDog << "    D - Deluxe Hot Dog  $" << Deluxe_HotDog << "\n";
    cout << "S - Small Drink  $" << Small_Drink << "    L - Large Drink     $" << Large_Drink << "\n";
    cout << "F - Finish Order          X - Exit System\n";
    cout << "Enter option ====> ";
	
	//prevents skipping getline after finish order loops back
	if (cin.peek() == '\n') {
		cin.ignore();
	}
	getline(cin,choice);

	//capitalizes 1st letter in choice input
	choice = toupper(choice[0]);

	//switch statement for each option from menu
	switch (choice[0]){
		case 'H':
			Sub_Total = Sub_Total + HotDog;
			cout << "Current Sub Total: $" << Sub_Total << "\n";
			break;
		case 'D':
			Sub_Total = Sub_Total + Deluxe_HotDog;
			cout << "Current Sub Total: $" << Sub_Total << "\n";
			break;
		case 'S':
			Sub_Total = Sub_Total + Small_Drink;
			cout << "Current Sub Total: $" << Sub_Total << "\n";
			break;
		case 'L':
			Sub_Total = Sub_Total + Large_Drink;
			cout << "Current Sub Total: $" << Sub_Total << "\n";
			break;
		case 'F':
			//calculations for taxes
			tax_total = (Sub_Total*tax);
			total = tax_total + Sub_Total;

			cout << "\n";
			cout << "Sub Total:   $  " << Sub_Total << "\n";
			cout << "Tax:         $  " << tax_total << "\n";
			cout << "Total:       $  " << total << "\n";
			cout << "Enter cash:     ";
			cin >> cash;

			//while loop to ensure that you pay full amount
			while (cash < total) {
				cout << "Not enough money please pay more\n";
				cout << "Enter cash:  $  ";
				cin >> cash;
			}
			
			change = cash - total;
			cout << "Change:      $  " << change << "\n";
			Sub_Total = 0;
			total = 0;
			system("pause");
			cout << "\n";
			break;
	}
    } while (choice != "X");
    
    system("pause");
    return 0;
}
