#ifndef __BIT_STRING_H__
#define __BIT_STRING_H__

#include <string>
#include <cmath>

/**
 * binary string "01100001" => string "a"
 */
std::string convertBinaryToString (std::string binary_str)
{
	std::string output = "";
	char ch = 0;

	for (int i = 0; i < binary_str.length(); ++i)
	{
		if (binary_str[i] == '1')
		{
			ch |= (int) pow (2, 7 - (i % 8));
		}

		if (i % 8 == 7 || i == binary_str.length() - 1)
		{
			output += ch;
			ch = 0;
		}
	}

	return output;
}

/**
 * string "a" => binary string "01100001"
 */
std::string convertStringToBinary (std::string str)
{
	std::string binary_str = "";

	for (int i = 0; i < str.length(); ++i)
	{
		binary_str += (str[i] & 128 ? '1' : '0');
		binary_str += (str[i] & 64 ? '1' : '0');
		binary_str += (str[i] & 32 ? '1' : '0');
		binary_str += (str[i] & 16 ? '1' : '0');
		binary_str += (str[i] & 8 ? '1' : '0');
		binary_str += (str[i] & 4 ? '1' : '0');
		binary_str += (str[i] & 2 ? '1' : '0');
		binary_str += (str[i] & 1 ? '1' : '0');
	}

	return binary_str;
}

#endif // __BIT_STRING_H__
