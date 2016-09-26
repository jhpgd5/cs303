#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <string>
#include <list>
#include"Term.h"

using namespace std;

void quickMenu() {                     //Prints Menu 
	cout << "---------------" << endl;
	cout << "1: Press 1 to Input Polynomials" << endl;  //input polynomials
	cout << "2: Press 2 to Quit" << endl; //Quit
	cout << "---------------" << endl;
}

void wait(int sec) //time delay before program exits
{
	clock_t wait;
	wait = clock() + sec * CLOCKS_PER_SEC;
	while (clock() < wait) {}
}


int main() {


	int timetowait = 4;
	char Answer;
	int Menu;                         //Stores the action the user wants the program to perform
	quickMenu();                            //Prints the menu to the screen
	cin >> Menu;
	list<Term>first;
	list<Term>second;

		while (Menu !=0) {

			switch (Menu)
			{
			case 1: {


				cout << "\nEnter First Polynomial, use the letter x for Ex: 3x^3+7x^2-6x+3 \n";//enter polynomials
				first = enterPolynomial();
				cout << "\nEnter Second Polynomial\n";
				second = enterPolynomial();
				list<Term> result;
				result = addPolynomial(first, second);  //add polynomials
				display(result); //display result
				std::cout << "Would you like to quit Y / N" << std::endl;
				std::cin >> Answer;

				Answer = std::toupper(Answer);
				if (Answer == 'Y') {
					break;
				}
				else if (Answer == 'N') {
					std::cout << "\nThank you for playing!" << std::endl;
					wait(timetowait);
					exit(0);

				}
			}

			case 2: {
				std::cout << "\nThank you for playing!" << std::endl;
				wait(timetowait);
				exit(0);
				break;
			}

		}
		
	}
	return 0;
}