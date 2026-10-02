#include "SrcMain.h"

#include "Trie.hpp"

#include <string>
#include <fstream>

// make a new mapper for DNA sequencing (ATGC)
struct DNATextIdxFunc
{
	size_t operator()(char c) const
	{
		switch (c)
		{
		case 'A' : return 0;
		case 'T' : return 1;
		case 'G' : return 2;
		case 'C' : return 3;
		default: return 0;
		}
	}
};

void ProcessCommandArgs(int argc, const char* argv[])
{
	// TODO
	// part 2 -- dna
	// argv[1] == "dna"
	if (std::string(argv[1]) == "dna")
	{
		//argv[2] contains the name of the patterns file
		//argv[3] contains the name of the DNA sequence which will be matched
		std::string patternsFile = argv[2];
		std::string dnaSequenceFile = argv[3];

		//opening the DNA-patterns.txt file
		std::ifstream patterns(patternsFile);
		if (!patterns.is_open())
		{
			// error
			throw std::runtime_error("couldnt not open" + patternsFile);
		}

		// templated arguments
		Trie<4, DNATextIdxFunc> dnaTrie;

		// load the patterns into the trie
		std::string word;
		while (std::getline(patterns, word))
		{
			dnaTrie.Insert(word);
		}

		// load dnaSequence file
		std::ifstream sequences(dnaSequenceFile);
		if (!sequences.is_open())
		{
			throw std::runtime_error("couldnt not open" + dnaSequenceFile);
		}

		std::string sequence;// entire ATGC wo the header
		std::string seq;
		while (std::getline(sequences, seq))
		{
			if (!seq.empty() && seq[0] == '>')
			{
				continue; // skip header
			}

			sequence += seq; // adding to the current sequence
		}

		// starting from index 0, call findPrefix
		// get the patterns to find from DNA-patterns.txt and search trie
		// output it to patterns.txt

		std::ofstream out ("patterns.txt");
		if (!out.is_open())
		{
			throw std::runtime_error("couldnt open patterns.txt!");
		}
		size_t i = 0;
		std::string_view seqView = sequence;
		while (!seqView.empty())
		{
			if (std::string result = dnaTrie.FindPrefix(seqView); !result.empty()) // pattern / sequence was found in the trie
			{
				out << i << "," << result << "\n";
			}
			seqView.remove_prefix(1); // continuously removing the first character -- don't need to change seqView index
			++i;
		}
	} // end of dna
}
