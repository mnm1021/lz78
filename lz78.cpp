#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "lz78.h"

using namespace std;

int main(int argc, char** argv)
{
	string input, encoded_string;
	ifstream input_file (argv[1]);
	ofstream encoded_file (argv[2]);
	ofstream decoded_file (argv[3]);
	stringstream str_stream;

	str_stream << input_file.rdbuf();
	input = str_stream.str();

	encoded_string = lz78_encode (input);

	encoded_file << encoded_string;

	decoded_file << lz78_decode (encoded_string);

	return 0;
}
