#ifndef __LZ78_H__
#define __LZ78_H__

#include <string>
#include <map>

//#include "bit_string.h"

/**
 * a simple binary trie node.
 */
struct trie
{
	int value;
#ifdef __BIT_STRING_H__
	struct trie* children[2];
#else
	std::map<char,struct trie*> children;
#endif
};
typedef struct trie trie;

/**
 * create root trie node.
 */
trie* createTrie ()
{
	trie* root = new trie;
	root->value = 0;
#ifdef __BIT_STRING_H__
	root->children[0] = root->children[1] = NULL;
#endif

	return root;
}

/**
 * delete the entire tree.
 */
void deleteTrie (trie* root)
{
#ifdef __BIT_STRING_H__
	if (root->children[0])
	{
		deleteTrie (root->children[0]);
	}

	if (root->children[1])
	{
		deleteTrie (root->children[1]);
	}
#else
	for (auto it = root->children.begin (); it != root->children.end (); ++it)
	{
		deleteTrie (it->second);
	}
#endif
	delete root;
}



/**
 * lz78 compression algorithm
 */
std::string lz78_encode (std::string input)
{
	int idx = 0;
	int node_num = 1;
	std::string input_binary, output = "";
	trie* root = createTrie ();
	trie* current = root;

#ifdef __BIT_STRING_H__
	input_binary = convertStringToBinary (input);
#else
	input_binary = input;
#endif

	while (idx < input_binary.length())
	{
#ifdef __BIT_STRING_H__
		int key = input_binary[idx++] - '0';

		if (current->children[key] == NULL)
#else
		char key = input_binary[idx++];

		if (current->children.find (key) == current->children.end ())
#endif
		{
			/* put new node on trie */
			trie* child = new trie;
			child->value = node_num++;
#ifdef __BIT_STRING_H__
			child->children[0] = child->children[1] = NULL;
#endif
			current->children[key] = child;

			/* add to output */
			output += std::to_string(current->value);
			output += ' ';
#ifdef __BIT_STRING_H__
			output += std::to_string(key);
#else
			output += key;
#endif

			if (idx != input_binary.length())
			{
				output += '/';
			}

			/* reset current node */
			current = root;
		}
		else
		{
			/* move to next node */
			current = current->children[key];

			/* add to output if current index is at the end of string */
			if (idx == input_binary.length())
			{
				output += std::to_string(current->value);
			}
		}
	}

	deleteTrie (root);

	return output;
}

/**
 * lz78 decompression algorithm
 */
std::string lz78_decode (std::string input)
{
	int idx = 0, dict_idx = 1;
	std::string token, output_binary = "";
	std::stringstream input_stream (input);
	std::map<int,std::string> dictionary;

	dictionary[0] = "";

	while (std::getline (input_stream, token, '/'))
	{
		int node_num, output_num;
		std::stringstream token_stream (token);

		token_stream >> node_num;

		if (token_stream.eof ())
		{
			/* just add binary string to output */
			output_binary += dictionary[node_num];
		}
		else
		{
#ifdef __BIT_STRING_H__
			token_stream >> output_num;
			std::string decoded_binary = dictionary[node_num] + std::to_string(output_num);
#else
			char delim, ch;
			token_stream >> std::noskipws;
			token_stream >> delim >> ch;
			std::string decoded_binary = dictionary[node_num] + ch;
#endif

			/* add binary string to output */
			output_binary += decoded_binary;

			/* add new binary string to dictionary */
			dictionary[dict_idx++] = decoded_binary;
		}
	}

#ifdef __BIT_STRING_H__
	return convertBinaryToString (output_binary);
#else
	return output_binary;
#endif
}

#endif // __LZ78_H__
