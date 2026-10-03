#include "SrcMain.h"

#include "Trie.hpp"

#include <string>
#include <fstream>

namespace
{
	// make a new mapper for DNA sequencing (ATGC)
	struct DNATextIdxFunc
	{
		size_t operator()(char c) const
		{
			switch (c)
			{
			case 'A':
				return 0;
			case 'T':
				return 1;
			case 'G':
				return 2;
			case 'C':
				return 3;
			default:
				return 0;
			}
		}
	};

	struct autoTextIdxFunction
	{
		size_t operator()(char c) const
		{
			return c - 'a';
		}
	};
} // namespace

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


	if (std::string (argv[1]) == "auto")
	{
		//alphabet is the lowercase letters a through z
		//argv[2] contains the name of the words file
		//argv[3] contains the name of the autocomplete stems file
		//argv[4] contains the value of the count parameter (in string form)
		std::string wordsFile = argv[2];
		std::string stemsFile = argv[3];
		std::string countParameter = argv[4];
		size_t count = std::stoul(countParameter);

		// open the words file
		std::ifstream words (wordsFile);
		if (!words.is_open())
		{
			throw std::runtime_error("couldnt open the words file");
		}

		// add each word to the trie
		Trie<26, autoTextIdxFunction> autoTrie;
		std::string w;
		while (std::getline(words, w))
		{
			autoTrie.Insert(w);
		}

		//read each line and use CompleteFromPrefix to find the matching autocompletions
		//making sure to use the number from argv[4] to get the correct count.
		std::ifstream stems (stemsFile);
		if (!stems.is_open())
		{
			throw std::runtime_error("couldnt open the stems file!");
		}

		// create the output file
		std::ofstream out ("auto.txt");
		if (!out.is_open())
		{
			throw std::runtime_error("couldnt open the output file");
		}

		std::string s;
		while (std::getline(stems, s))
		{
			std::vector<std::string> matchingAutoCom = autoTrie.CompleteFromPrefix(s, count);
			//For each stem you should output the stem,
			//followed by a : with each match separated with a | into an auto.txt output file
			out << s << ":";
			for (size_t i = 0; i < matchingAutoCom.size(); ++i)
			{
				if (i > 0)
				{
					out << '|';
				}
				out << matchingAutoCom[i];
			}
			out << "\n"; // do new line after we output the matches for a stem
		}

	}// end of auto
}
