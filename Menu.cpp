
#include <iostream>
#include <string>
#include <sstream>
using namespace std;



void quickMenu() {                               //Prints Menu 
	cout << "---------------" << endl;
	cout << "1: Press 1 to input Polynomials" << endl;
	cout << "2. Press 0 to Quit" << endl;
	cout << "---------------" << endl;
}
int main()
{


	int Menu;                         //Stores the action the user wants the program to perform
	quickMenu();                            //Prints the menu to the screen
	cin >> Menu;

	while (Menu != 0) {                //Enter 0 to exit menu
		switch (Menu) {
		case 1:
			;  //enter polynomials
			break;
		}
		if (Menu == 0)
			break;

		//After a menu selection, ask the user what he/she 
		//would like to do next
		cin >> Menu;

	}
	system("pause");
	return 0;
}
