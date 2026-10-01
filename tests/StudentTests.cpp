#include "catch.hpp"
#include "SrcMain.h"
#include "Trie.hpp"

// Helper function declarations (don't change these)
extern bool CheckFileMD5(const std::string& fileName, const std::string& expected);
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

namespace {
	struct BasicTextIdx
	{
		size_t operator()(char c) const
		{
			switch (c)
			{
			case 'A': return 0;
			case 'B': return 1;
			case 'C': return 2;
			default: return 0;
			}
		}
	};

	struct EnglishTextIdx
	{
		size_t operator()(char c) const
		{
			return c - 'A';
		}
	};
}

// Test cases for Trie implementation
TEST_CASE("Student Trie tests", "[student]")
{
	SECTION("Basic insertion + BFS")
	{
		Trie<3, BasicTextIdx> t;
		t.Insert("AAB");
		t.Insert("A");
		t.Insert("BBCA");
		t.Insert("CA");

		std::string result;
		t.BFS([&result](char c) {
			result += c;
			});
		REQUIRE(result == "*ABC$ABABC$$A$");
	}

	SECTION("Basic insertion + BFS 2")
	{
		Trie<3, BasicTextIdx> t;
		t.Insert("BCB");
		t.Insert("BCA");
		t.Insert("ABA");
		t.Insert("BAA");

		std::string result;
		t.BFS([&result](char c) {
			result += c;
			});
		REQUIRE(result == "*ABBACAAAB$$$$");
	}

	SECTION("English insertion + BFS")
	{
		Trie<26, EnglishTextIdx> t;
		t.Insert("BANANAS");
		t.Insert("BANANA");
		t.Insert("BREAD");
		t.Insert("ZEBRA");
		t.Insert("PLATYPUS");

		std::string result;
		t.BFS([&result](char c) {
			result += c;
			});
		REQUIRE(result == "*BPZARLENEABAATRNDYAA$P$$SU$S$");
	}

	SECTION("English insertion + FindPrefix")
	{
		Trie<26, EnglishTextIdx> t;
		t.Insert("BAN");
		t.Insert("BANANA");

		REQUIRE(t.FindPrefix("BAN") == "BAN");
		REQUIRE(t.FindPrefix("BAND") == "BAN");
		REQUIRE(t.FindPrefix("BANDANA") == "BAN");
		REQUIRE(t.FindPrefix("BANANA") == "BANANA");
		REQUIRE(t.FindPrefix("BANANAS") == "BANANA");
		REQUIRE(t.FindPrefix("ZEBRA").empty());
		REQUIRE(t.FindPrefix("BAR").empty());
		REQUIRE(t.FindPrefix("BANAN") == "BAN");
	}

	SECTION("English insertion + CompleteFromPrefix")
	{
		Trie<26, EnglishTextIdx> t;
		t.Insert("BAR");
		t.Insert("BAND");
		t.Insert("BANK");
		t.Insert("BANKING");
		t.Insert("BANANA");

		std::vector<std::string> results;
		results = t.CompleteFromPrefix("BAN");
		REQUIRE(results == std::vector<std::string>{"BAND", "BANK", "BANANA"});

		results = t.CompleteFromPrefix("BAN", 2);
		REQUIRE(results == std::vector<std::string>{"BAND", "BANK"});

		results = t.CompleteFromPrefix("BAR");
		REQUIRE(results == std::vector<std::string>{"BAR"});

		results = t.CompleteFromPrefix("BANK");
		REQUIRE(results == std::vector<std::string>{"BANK", "BANKING"});

		results = t.CompleteFromPrefix("BANK", 1);
		REQUIRE(results == std::vector<std::string>{"BANK"});

		results = t.CompleteFromPrefix("BAY");
		REQUIRE(results.empty());
	}
}

// DNA pattern matching tests
// TEST_CASE("Student DNA pattern matching tests", "[student]")
// {
// 	SECTION("COVID pattern matching")
// 	{
// 		const char* argv[] = {
// 			"tests/tests",
// 			"dna",
// 			"input/DNA-patterns.txt",
// 			"input/COVID-reference.txt"
// 		};
// 		ProcessCommandArgs(4, argv);
// 		bool result = CheckTextFilesSame("patterns.txt", "expected/COVID-patterns.txt");
// 		REQUIRE(result);
// 	}
// 	SECTION("DMD pattern matching (correctness)")
// 	{
// 		const char* argv[] = {
// 			"tests/tests",
// 			"dna",
// 			"input/DNA-patterns.txt",
// 			"input/DMD.txt"
// 		};
// 		ProcessCommandArgs(4, argv);
// 		bool result = CheckTextFilesSame("patterns.txt", "expected/DMD-patterns.txt");
// 		REQUIRE(result);
// 	}
// 	SECTION("DMD pattern matching (timed)")
// 	{
// 		const char* argv[] = {
// 			"tests/tests",
// 			"dna",
// 			"input/DNA-patterns.txt",
// 			"input/DMD.txt"
// 		};
// 
// 		auto start = std::chrono::high_resolution_clock::now();
// 		ProcessCommandArgs(4, argv);
// 		auto end = std::chrono::high_resolution_clock::now();
// 		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
// 		float seconds = duration / 1000000000.0f;
// 
// 		bool result = CheckTextFilesSame("patterns.txt", "expected/DMD-patterns.txt");
// 		REQUIRE(result);
// 
// 		WARN("****DMD pattern matching (timed) test took: " << seconds << "s****");
// 		REQUIRE(seconds < 0.15f);
// 	}
// }
// 
// // Graded autocomplete tests
// TEST_CASE("Student autocomplete tests", "[student]")
// {
// 	SECTION("Top 1000 words autocomplete")
// 	{
// 		const char* argv[] = {
// 			"tests/tests",
// 			"auto",
// 			"input/words-1000.txt",
// 			"input/auto-1000.txt",
// 			"3"
// 		};
// 		ProcessCommandArgs(5, argv);
// 		bool result = CheckTextFilesSame("auto.txt", "expected/1000-auto.txt");
// 		REQUIRE(result);
// 	}
// 
// 	SECTION("All words autocomplete (correctness)")
// 	{
// 		const char* argv[] = {
// 			"tests/tests",
// 			"auto",
// 			"input/words-all.txt",
// 			"input/auto-all.txt",
// 			"10"
// 		};
// 
// 		ProcessCommandArgs(5, argv);
// 		bool result = CheckTextFilesSame("auto.txt", "expected/all-auto.txt");
// 		REQUIRE(result);
// 	}
// 
// 	SECTION("All words autocomplete (timed)")
// 	{
// 		const char* argv[] = {
// 			"tests/tests",
// 			"auto",
// 			"input/words-all.txt",
// 			"input/auto-all.txt",
// 			"10"
// 		};
// 
// 		auto start = std::chrono::high_resolution_clock::now();
// 		ProcessCommandArgs(5, argv);
// 		auto end = std::chrono::high_resolution_clock::now();
// 		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
// 		float seconds = duration / 1000000000.0f;
// 
// 		bool result = CheckTextFilesSame("auto.txt", "expected/all-auto.txt");
// 		REQUIRE(result);
// 
// 		WARN("****All words autocomplete (timed) test took: " << seconds << "s****");
// 		REQUIRE(seconds < 0.35f);
// 	}
// }
