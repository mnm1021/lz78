#ifndef __LZ78_H__
#define __LZ78_H__

#include <string>
#include <map>

#include "bit_string.h"

/**
 * a simple binary trie node.
 */
struct trie
{
	int value;
	std::map<char,struct trie*> children;
};
typedef struct trie trie;

/**
 * create root trie node.
 */
trie* createTrie ()
{
	trie* root = new trie;
	root->value = 0;

	return root;
}

/**
 * delete the entire tree.
 */
void deleteTrie (trie* root)
{
	for (std::map<char, trie*>::iterator it = root->children.begin ();
			it != root->children.end ();
			++it)
	{
		deleteTrie (it->second);
	}

	delete root;
}


/**
 * get appropriate bit length for convert
 */
int get_bit_length (int idx)
{
	return (idx != 1) ? ceil (log2 (idx)) : 1;
}

/**
 * lz78 compression algorithm
 */
std::string lz78_encode (std::string input)
{
	int idx = 0;
	int node_num = 1;
	std::string output_binary = "";
	trie* root = createTrie ();
	trie* current = root;

	while (idx < input.length ())
	{
		char key = input[idx++];

		if (current->children.find (key) == current->children.end ())
		{
			/* put new node on trie */
			trie* child = new trie;
			child->value = node_num;
			current->children[key] = child;

			/* add to binary output */
			int num_bits = get_bit_length (node_num);
			output_binary += convertIntToBinary (current->value, num_bits);
//			output_binary += convertStringToBinary (std::string (1, key));
			output_binary += convertCharToBinary (key);

			/* reset current node */
			current = root;
			++node_num;
		}
		else
		{
			/* move to next node */
			current = current->children[key];

			/* add to output if current index is at the end of string */
			if (idx == input.length ())
			{
				int num_bits = get_bit_length (node_num);
				output_binary += convertIntToBinary (current->value, num_bits);
			}
		}
	}

	deleteTrie (root);

	return convertBinaryToString (output_binary);
}

/**
 * lz78 decompression algorithm
 */
std::string lz78_decode (std::string input)
{
	int idx = 0, dict_idx = 1;
	std::string token, output = "";
	std::string input_binary = convertStringToBinary (input);
	std::map<int,std::string> dictionary;
	int input_length = input_binary.length ();

	dictionary[0] = "";

	while (idx < input_length)
	{
		/* read code number */
		int num_bits = get_bit_length (dict_idx);
		int node_num = convertBinaryToInt (input_binary.substr (idx, num_bits));

		idx += num_bits;

		/* add the string on dictionary to output */
		output += dictionary[node_num];

		if (idx + 6 <= input_length)
		{
			/* get output character and add to output */
			char out_ch = convertBinaryToChar (input_binary.substr (idx, 7));
			if (out_ch != 0)
			{
				output += out_ch;

				/* add new binary string to dictionary */
				dictionary[dict_idx++] = dictionary[node_num] + out_ch;
			}

			idx += 7;
		}
	}

	return output;
}

#endif // __LZ78_H__
