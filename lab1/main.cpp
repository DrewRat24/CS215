//--------------------------------------------------------------------
//                       CS215-011 LAB 1
//--------------------------------------------------------------------
// Author: Drew Ratliff
// Date: 1/14/19
// Description: My first C++ program. It does arithmetic on two numbers.
//--------------------------------------------------------------------

#include <iostream>
using namespace std;

int main() {
	float num1;
	float num2;
	int numproduct;
	int sum;
	int difference;
	int product;
	int iquotient;
	float fquotient;

	cout << "+------------------------------+\n";
	cout << ":          Number Fun!         :\n";
	cout << ":       By: Drew Ratliff       :\n";
	cout << "+------------------------------+\n";


	cout << "Enter a number: ";
	cin >> num1;

	cout << "Enter another:  ";
	cin >> num2;

	sum = num1 + num2;
	cout << "\nSum:            " << sum << "\n";

	difference = num1 - num2;
	cout << "Difference:     " << difference << "\n";

	numproduct = num1*num2;
	cout << "Product:        " << numproduct << "\n";

	iquotient = num1 / num2;
	cout << "Int Quotient:   " << iquotient << "\n";

	fquotient = num1 / num2;
	cout << "Float Quotient: " << fquotient << "\n";

	system("pause");
	return 0;
}
