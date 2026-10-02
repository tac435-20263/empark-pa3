#pragma once
#include <memory>
#include <string_view>
#include <functional>
#include <queue>
#include <array>
#include <vector>
#include <string>
#include <utility>

// different letters in alphabet trie
// function: map letter to a specific index of the array of children we store in each node
template <size_t AlphabetSize, typename LetterToIdxFunc>
class Trie
{
public:
	// Insert word into Trie
	void Insert(std::string_view word)
	{
		// TODO
		// recursively go down the tree and check to see if exists or need to create new 
		Node * curr = mRoot;

		for (char c : word){
			size_t i = mLetterToIndex(c) + 1; // mapper function so i.e. 'A' = 0 + 1 = 1

			if (curr->mPtr[i] == nullptr){ // doesn't exist in the mPtr
				curr->mPtr[i] = new Node(); // address of the child node
			}
			curr = curr->mPtr[i]; // moving it down into the new Node we just created -- keep going
		}

		if (curr->mPtr[0] == nullptr){
			// end of the word
			curr->mPtr[0] = new Node();

		}

	}

	// Do a Breadth-First-Search on the Trie, calling visitFunc on each node
	void BFS(std::function<void(char)> visitFunc)
	{
		// TODO
		std::queue<std::pair<Node*, char>> queue;
		queue.push({mRoot, '*'}); // root has no letter

		while (!queue.empty()){ // while it is not empty
			// remove first element
			auto [node, c] = queue.front();
			queue.pop();
			visitFunc(c); // call visitFunc on every node except for root


			// append the children to the end of the queue
			for (size_t i = 0; i < AlphabetSize + 1; ++i){
				if (node->mPtr[i] != nullptr){
					size_t letter = '$';
					if (i != 0){
						letter = 'A' + (i - 1); // undo the + 1 by subtracting
					}
					queue.push({node->mPtr[i], letter});
				}
			}
		}
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

	struct Node{
		Node* mPtr[AlphabetSize + 1] = {}; // +1 for $
	};
	// start of the trie
	Node* mRoot = new Node();

	LetterToIdxFunc mLetterToIndex;
};
