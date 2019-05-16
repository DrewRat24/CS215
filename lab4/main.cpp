//------------------------------------------------------------
//                      CS215-011 LAB 4
//------------------------------------------------------------
// Author: Drew Ratliff
// Date: 2/11/19
// Description: Program that reads data from input file and
// writes a report
//------------------------------------------------------------

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
	int temp_amount, temp, max = 0, min = 0;
	string date;

	//input file opening
	ifstream fin;
	fin.open("tempsin.txt");
	//if statement for if the input file fails to open
	if (fin.fail()) {
		cout << "Unable to read input file.\n";
		return 0;
	}

	//output file opening 
	ofstream fout;
	fout.open("tempsout.txt");
	fout << setw(10) << "DATE       HIGH  LOW" << endl;
	fout << "---------- ---- ----" << endl;

	fin >> date >> temp_amount;

	//while loop for cycling between each line of data
	while (date != "ENDOFDATA") {
		fin >> temp;
		max = temp;
		min = temp;
		for (int i = 2; i <= temp_amount; i=i+1) {
			fin >> temp;
			
			//if statement for sorting min and max temps every cycle
			if (temp > max) {
				max = temp;
			}
			else if (temp < min){
				min = temp;
			}
			
		}

		fout << right << date << " " << setw(4) << max << " " << setw(4) << min << endl;
		//reset min and max at end of loop
		max = 0;
		min = 0;
		//gather the date and temp amount at end of loop for next cycle
		fin >> date >> temp_amount;
	}
	//closing both the input and output file after loop
	fout.close();
	fin.close();

	system("pause");
	return 0;
}
