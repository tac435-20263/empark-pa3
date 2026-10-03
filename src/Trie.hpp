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
		Node * curr = mRoot;

		for (char c : word){
			size_t i = mLetterToIndex(c) + 1; // mapper function so i.e. 'A' = 0 + 1 = 1

			if (curr->mPtr[i] == nullptr){ // doesn't exist in the mPtr
				curr->mPtr[i] = new Node(); // create a new child: address of the child node
				curr->mPtr[i]->mLetter = c; // store each node's letter upon creation
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
		std::string best;
		std::string current;
		Node* curr = mRoot;

		for (char c : word)
		{
			// only need to traverse as long as the WORD we are searching for
			size_t i = mLetterToIndex(c) + 1; // account for $

			if (curr->mPtr[i] == nullptr){
				break; // return "" if no COMPLETE WORD match
			}

			current.push_back(c);

			curr = curr->mPtr[i]; // include c in current first before checking if mPtr[0] is null or not

			if (curr->mPtr[0] != nullptr) // check to see if '$' exists
			{
				best = current; // add current aka the c's into the best "holder" variable
			}
		}
		return best;
	}

	// Given a string, returns a vector of up to X shortest words that match the prefix
	// or an empty vector if there are no matches
	std::vector<std::string> CompleteFromPrefix(std::string_view prefix, size_t count = 3)
	{
		// TODO
		// basically a bfs
		// store the partial word
		// stop until reach count (3)
		std::queue<std::pair<std::string, Node*>> q;
		std::vector<std::string> res;
		Node* curr = mRoot;
		auto pref = std::string(prefix);


		for (char c : prefix)
		{
			size_t i = mLetterToIndex(c) + 1;
			if (curr->mPtr[i] == nullptr) // a char in prefix does NOT in the trie
			{
				return std::vector<std::string>{};
			}
			curr = curr->mPtr[i]; // go down the word letter
		}

		// curr is set to the last letter of prefix
		// pass in empty string, then append the prefix with the s string in results array
		q.push({"", curr});

		while (!q.empty())
		{
			auto [s, n] = q.front();
			q.pop();

			// check if the current node is the $ or not
			if (n->mPtr[0] != nullptr)
			{
				// found $
				res.push_back({pref + s});

				if (res.size() == count)
				{
					return res;
				}
			}

			// else, if it is not the $--then find the alphabet
			// and then append it to the string (in the queue)
			for (size_t i = 1; i < AlphabetSize + 1; ++i)
			{
				// any other letter append to the queue
				if (n->mPtr[i] != nullptr)
				{
					// push current characters in s + letter
					char letter = n->mPtr[i]->mLetter; // retrieve letter from Node
					q.push({s + letter, n->mPtr[i]});
				}
			}
		}
		return res;
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
		char mLetter = '\0';
	};
	// start of the trie
	Node* mRoot = new Node();

	LetterToIdxFunc mLetterToIndex;
};
