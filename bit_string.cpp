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

	return 0;
}
