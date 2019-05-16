//------------------------------------------------------------
//                      CS215-011 LAB 6
//------------------------------------------------------------
// Author: Drew Ratliff
// Date: 2/25/19
// Description: Sort an array from file input and calculate data
//------------------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	const int num_prices = 10;
	int time = 8;
	double prices[num_prices], sorting;
	string file_name, date, file_title;

	cout << "Enter stock data file name: ";
	cin >> file_name;

	ifstream fin; //declare input file handle
	fin.open(file_name); //open input file
	if (fin.fail()) { //if fails end program
		cout << "Failed to open file " << file_name << endl;
		system("pause");
		return 0;
	}

	fin >> file_title >> date; //get first two terms from file and declare them
	cout << "STOCK: " << file_title << "  DATE: " << date << endl;
	cout << "TIME     PRICE" << endl;
	cout << "_____    ________" << endl;

	//--------------------------------------
	// Time to Prices For-Loop
	//--------------------------------------
	for (int i = 0; i < num_prices; i++) {
		fin >> prices[i];
		cout << right << setw(2) << time << ":00    $" << fixed << setw(7) << setprecision(2) << prices[i] << endl;
		time++;
		if (time > 12){
			time = 1;
		}
	}
	fin.close(); //close the file

	double change = (prices[9] - prices[0]); //declaring change value before sorting
	cout << "\nCHANGE:  $" << setw(7) << change << endl;

	//--------------------------------------
	// Sorting For-Loop
	//--------------------------------------
	for (int i = 0; i < num_prices; i++) {
		for (int j = 0; j < num_prices; j++){
			if (prices[i] < prices[j]) {
				sorting = prices[i];
				prices[i] = prices[j];
				prices[j] = sorting;
			}
		}
	}

	//calculations and output for the highest price
	double high = prices[num_prices-1];
	cout << "HIGH:    $" << setw(7) << high << endl;

	//calculations and output for the lowest price
	double low = prices[0];
	cout << "LOW:     $" << setw(7) << low << endl;

	//calculations and output for the average price
	double sum = 0, average = 0;
	for (int i = 0; i < num_prices; i++) { //needed for loop to add up all of the prices
		sum = sum + prices[i];
	}
	average = sum / num_prices;
	cout << "AVERAGE: $" << setw(7) << average << endl;

	//calculations and output for the median price
	double median = (prices[num_prices/2]+prices[(num_prices/2)-1])/2;
	cout << "MEDIAN:  $" << setw(7) << median << endl;

	system("pause");
	return 0;
}
