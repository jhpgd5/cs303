#include<iostream>
#include<string>
#include<list>
#include"Term.h"

#define DEG 100	//make max degree = 99
using namespace std;


Term::Term(int ex, double co){ //set varibles 
	exponent = ex;
	coefficient = co;
}

ostream &operator<<(ostream &output, const Term term)//output stream
{
	if (term.coefficient<0)
		output << term.coefficient << "x^" << term.exponent;
	else if (term.coefficient>0)
		output << "+" << term.coefficient << "x^" << term.exponent ;
	return output;
}

bool operator < (const Term& lhs, const Term& rhs){ // < bool
	return lhs.exponent<rhs.exponent;
}


bool operator >(const Term lhs, const Term rhs){ // > bool
	return lhs.exponent>rhs.exponent;
}
bool operator == (const Term lhs, const Term rhs){ // == bool
	return lhs.exponent == rhs.exponent;
}
Term operator + (const Term lhs, const Term rhs){ 
	Term newterm(lhs.exponent, lhs.coefficient + rhs.coefficient);
	return newterm;
}

list<Term> addPolynomial(list<Term> a, list<Term> b){ //function to add polynomials
	list<Term> result;
	list<Term>::iterator iter_a = a.begin();
	list<Term>::iterator iter_b = b.begin();
	while (iter_a != a.end() && iter_b != b.end()){ //interate to end and push in values
		if (iter_a == a.end()){
			result.push_back(*iter_b);
			iter_b++;
			continue;
		}
		if (iter_b == b.end()){
			result.push_back(*iter_a);
			iter_a++;
			continue;
		}
		if (*iter_a > *iter_b){
			result.push_back(*iter_a);
			iter_a++;
		}
		else if (*iter_a < *iter_b){
			result.push_back(*iter_b);
			iter_b++;
		}
		else{
			result.push_back(*iter_a + *iter_b);
			iter_a++;
			iter_b++;
		}
	}

	return result;
};

list<Term> enterPolynomial(){
	string polynomial;
	cin >> polynomial;  
	int polynomialSize = polynomial.size();
	
	int monomial = 1; //number of monimials
	for (int i = 1; i < polynomialSize; ++i)
		if (polynomial[i] == '+' || polynomial[i] == '-')
			monomial++;
	
	if (isdigit(polynomial[0])) polynomial.insert(0, "+"); //append positive for parsing
	if (polynomial[0] == 'x') polynomial.insert(0, "+");
	polynomial.append("+");
	polynomialSize = polynomial.size();
	
	int k = 0; //extract monimials into string
	int j = 0;
	string monomialStr[DEG];
	for (int i = 1; i < polynomialSize; ++i)
		if (polynomial[i] == '+' || polynomial[i] == '-')
		{
		monomialStr[k++] = polynomial.substr(j, i - j);
		j = i;
		}
	
	for (int i = 0; i < monomial; ++i) //Formatting monomials coeffcientX^exponent
	{
		if (monomialStr[i][1] == 'x')	//place x after sign
			monomialStr[i].insert(1, "1");	//make 1 coeffcient
		bool flag = false;	// if no x is present
		int len = monomialStr[i].size();
		for (int j = 1; j < len; ++j)
			if (monomialStr[i][j] == 'x')	
			{
			flag = true;	//if x is present
			if (j == len - 1)	
				monomialStr[i].append("^1");	//gets exponent 1
			break;	//exit j loop
			}
		if (!flag)	//if x is not present then term is constant
			monomialStr[i].append("x^0");	
	}
	
	list<Term> li;  //	convert coeffients and exponents to int
	int expon[DEG] = { 0 };
	double coeff[DEG] = { 0. };
	for (int i = 0; i < monomial; ++i)
	{
		int monomialSize = monomialStr[i].size();
		for (int j = 0; j < monomialSize; ++j)
		{
			if (monomialStr[i][j] == '^')
			{
				expon[i] = stoi(monomialStr[i].substr(j + 1, monomialSize - j));
				coeff[i] = stod(monomialStr[i].substr(0, j));
				break;
			}
		}
	}
	
	int maxExponent = 0; //	Find largest exponent
	for (int k : expon)
		if (k >= maxExponent) maxExponent = k;

	string newMonomial[DEG]; 	//	make degree max exponent
	for (int i = maxExponent; i >= 0; i--)
		newMonomial[i] = "+0x^" + std::to_string(i);
	
	for (int i = monomial; i >= 0; i--) //	Mixing the two polynomials - given & null	
		newMonomial[expon[i]] = monomialStr[i];

	string finalPolynomial;//	final string
	for (int i = maxExponent; i >= 0; i--)
		finalPolynomial += newMonomial[i];
	;

	int finalSize = finalPolynomial.size(); //	Extracting the coefficients & exponents	to form polynomial
	int start[DEG] = { 0 };
	int stop[DEG] = { 0 };
	k = 0;
	for (int i = 0; i < finalSize; ++i)
	{
		if (finalPolynomial.substr(i, 1) == "+" || finalPolynomial.substr(i, 1) == "-")
			start[k] = i;
		if (finalPolynomial.substr(i, 1) == "x")
			stop[k++] = i;
	}

	for (int i = 0; i < k; ++i)
	{
		coeff[i] = stod(finalPolynomial.substr(start[i], stop[i] - start[i]));
		expon[i] = maxExponent - i;
		Term temp(expon[i], coeff[i]);
		li.push_back(temp);
	}
	//display(li);
	return li;
};
void display(list<Term> result){  //display result
	cout << "\nFirst Polynomial + Second Polynomial equals" << endl;
	for (list<Term>::iterator itr = result.begin(); itr != result.end(); itr++){
		cout << *itr;
	}
	cout << "\n " <<endl;
};
