#include <iostream>
#include <iomanip>

using namespace std;

struct fraction {
	int numer=0;
	int denom=0;
	double decimal=0.0;
};

const int MAX=10, MIN=1;


//----------------------------------------------------------
//						askFraction
//----------------------------------------------------------
fraction askFraction() {
	fraction fractions;
	cout << "Enter numerator:   ";
	cin >> fractions.numer;
	cout << "Enter denominator: ";
	do {
		cin >> fractions.denom;
	} while (fractions.denom == 0);
	return fractions;
} // askFraction();

//----------------------------------------------------------
//						calcDecimal
//----------------------------------------------------------
void calcDecimal(fraction & fractions) {
	fractions.decimal = (fractions.numer / (double)fractions.denom);
	if (fractions.denom == 0)
		fractions.decimal = 0.0;
} // calcDecimal();

//----------------------------------------------------------
//						printFraction
//----------------------------------------------------------
void printFraction(fraction fractions) {
	cout << fractions.numer << " / " << fractions.denom << " <";
	cout << fractions.decimal << ">" << endl;
} // printFraction();

//----------------------------------------------------------
//						askFractionList
//----------------------------------------------------------
int askFractionList(fraction fractions[]) {
	int index;
	cout << "How many fractions in your list? ";
	cin >> index;
	while (index > MAX || index < MIN) {
		cout << "Enter a number between 1 and 10" << endl;
		cout << "How many fractions in your list? ";
		cin >> index;
	}
	for (int i = 0; i < index; i++) {
		cout << "For fraction " << (i + 1) << ":" << endl;
		fractions[i] = askFraction();
		calcDecimal(fractions[i]);
	}
	return index;
} // askFractionList();

//----------------------------------------------------------
//						printFractionList
//----------------------------------------------------------
void printFractionList(fraction fractions[], int & numFractions) {
	for (int i = 0; i < numFractions; i++)
		printFraction(fractions[i]);
} // printFractionList();

//----------------------------------------------------------
//						findMaxFraction
//----------------------------------------------------------
int findMaxFraction(fraction fractions[], int & numFractions) {
	double max = 0;
	int maxIndex=0;
	for (int i = 0; i < numFractions; i++) {
		if (fractions[i].decimal > max) {
			max = fractions[i].decimal;
			maxIndex = i;
		}
	}
	if (numFractions == 0)
		return -1;
	else
		return maxIndex;

} // findMaxFraction();


int main() {
	int index,max;
	fraction fractions[MAX];
	index = askFractionList(fractions);
	printFractionList(fractions, index);
	cout << "The highest value fraction is: ";
	max = findMaxFraction(fractions, index);
	printFraction(fractions[max]);

	system("pause");
	return 0;
}
