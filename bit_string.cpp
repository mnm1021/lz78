#include <iostream>
#include <string>
#include <cstdio>

#include "bit_string.h"

using namespace std;

int main ()
{
	string input;

	cin >> input;

	cout << convertStringToBinary(input) << endl;
	cout << convertBinaryToString(convertStringToBinary(input)) << endl;

	cout << "1 : " << convertIntToBinary(1, 10) << endl;
	cout << "15 : " << convertIntToBinary(15, 10) << endl;
	cout << "233 : " << convertIntToBinary(233, 10) << endl;

	cout << convertBinaryToInt("1111") << endl;
	cout << convertBinaryToInt("111") << endl;
	cout << convertBinaryToInt("1011") << endl;
	cout << convertBinaryToInt("0") << endl;
	cout << convertBinaryToInt("1101") << endl;
	cout << convertBinaryToInt("110111") << endl;

	return 0;
}
