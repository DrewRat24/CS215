//--------------------------------------------------------------------
//                         CS215-011 LAB 2 
//--------------------------------------------------------------------
// Author: Drew Ratliff
// Date: 1/21/18
// Description: ...
//--------------------------------------------------------------------

#include <iostream>
#include <string>
using namespace std;

int main () {

//assign variables and set = 0
int num1=0,num2=0,num3=0;
int smallest=0,middle=0,biggest=0;

//display input for each number
cout << "Enter number 1: ";
cin >> num1;
cout << "Enter number 2: ";
cin >> num2;
cout << "Enter number 3: ";
cin >> num3;

//if statement for sorting 3 numbers
if (num1 >= num2 && num2 >= num3){ //checks out
    biggest = num1;
    middle = num2;
    smallest = num3;
}
else if (num1 >= num2 && num1 <= num3){ //checks out
    middle = num1;
    smallest = num2;
    biggest = num3;
}
else if (num1 <= num2 && num1 >= num3){ //checks out
    middle = num1;
    biggest = num2;
    smallest = num3;
}
else if (num1 <= num3 && num2 >= num3){ //checks out
    smallest = num1;
    biggest = num2;
    middle = num3;
}
else if (num1 <= num2 && num2 <= num3){ //checks out
    smallest = num1;
    middle = num2;
    biggest = num3;
}
else if (num2 <= num3 && num2 <= num1){ //good
    biggest = num1;
    smallest = num2;
    middle = num3;
}
cout << "Sorted they are " << smallest << " " << middle << " " << biggest << "\n\n";

//list pepper options
string pepper;
cout << "A. Aleppo Pepper\n";
cout << "B. Banana Pepper\n";
cout << "C. Cayenne Pepper\n";
cout << "D. Dragon's Breath\n";

//display option to choose a pepper
cout << "Enter a letter to choose a pepper: ";
cin >> pepper;

//assign variables for pepper scovilles
int Alepo=30000,Banana=1000,Cayenne=40000,Dragon=2480000;

//if statement for displaying each peppers scovilles by letter
if (pepper == "A" || pepper == "a"){
    cout << "That's " << Alepo << " Scovilles of heat!\n";
}
else if (pepper == "B" || pepper == "b"){
    cout << "That's " << Banana << " Scovilles of heat!\n";
}
else if (pepper == "C" || pepper == "c"){
    cout << "That's " << Cayenne << " Scovilles of heat!\n";
}
else if (pepper == "D" || pepper == "d"){
    cout << "That's " << Dragon << " Scovilles of heat!\n";
}
else {
    cout << "That pepper is not on the list\n";
}

    system("pause");
    return 0;
}
