#ifndef __BIT_STRING_H__
#define __BIT_STRING_H__

#include <string>
#include <cmath>

/**
 * integer 15, digit 8 => string "00001111"
 * integer 15, digit 4 => string "1111"
 */
std::string convertIntToBinary (int num, int digit)
{
	std::string output = "";

	for (int i = digit - 1; i >= 0; --i)
	{
		output += (num & (int)pow (2, i) ? '1' : '0');
	}

	return output;
}

/**
 * string "1111" => integer 15
 */
int convertBinaryToInt (std::string str)
{
	int output = 0;

	for (int i = 0; i < str.length(); ++i)
	{
		output += (str[i] - '0') * pow (2, str.length() - i - 1);
	}

	return output;
}

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
 * string "aa" => binary string "0110000101100001"
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

/**
 * char 'a' => binary string "1100001": 1bit reduced version
 */
std::string convertCharToBinary (char ch)
{
	std::string binary_char = "";

	binary_char += (ch & 64 ? '1' : '0');
	binary_char += (ch & 32 ? '1' : '0');
	binary_char += (ch & 16 ? '1' : '0');
	binary_char += (ch & 8 ? '1' : '0');
	binary_char += (ch & 4 ? '1' : '0');
	binary_char += (ch & 2 ? '1' : '0');
	binary_char += (ch & 1 ? '1' : '0');

	return binary_char;
}

/**
 * binary string "1100001' => char 'a'
 */
char convertBinaryToChar (std::string binary_char)
{
	char ch = 0;

	for (int i = 0; i < binary_char.length(); ++i)
	{
		if (binary_char[i] == '1')
		{
			ch |= (int) pow (2, 6 - i);
		}
	}

	return ch;
}

#endif // __BIT_STRING_H__
