#pragma once
#include <memory>
#include <string_view>
#include <functional>
#include <queue>
#include <array>
#include <vector>
#include <string>

template <size_t AlphabetSize, typename LetterToIdxFunc>
class Trie
{
public:
	// Insert word into Trie
	void Insert(std::string_view word)
	{
		// TODO
	}

	// Do a Breadth-First-Search on the Trie, calling visitFunc on each node
	void BFS(std::function<void(char)> visitFunc)
	{
		// TODO
	}

	// Given a string, returns the longest matching prefix in the trie
	// or an empty string if there is no match
	std::string FindPrefix(std::string_view word)
	{
		// TODO
		return std::string{};
	}

	// Given a string, returns a vector of up to X shortest words that match the prefix
	// or an empty vector if there are no matches
	std::vector<std::string> CompleteFromPrefix(std::string_view prefix, size_t count = 3)
	{
		// TODO
		return std::vector<std::string>{};
	}

	// Need an empty default constructor due to deletes
	Trie() {}

	// Delete copy/move and assignments
	Trie(const Trie& other) = delete;
	Trie(Trie&& other) = delete;
	Trie& operator=(const Trie& other) = delete;
	Trie& operator=(Trie&& other) = delete;

private:
	// TODO: Add node struct and any member data
};
