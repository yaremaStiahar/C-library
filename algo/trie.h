#pragma once
#include "TrieNode.h"
#include <string>
#include <vector>

using namespace std;

struct trie
{
private:
	TrieNode* root;

	void pre_order(vector<string>& vec, string& s, TrieNode* p);
public:

	trie();

	TrieNode* find(const string& s);

	bool contains(const string& s);

	void insert(const string& s);

	string largest_prefix(const string& s);

	string lcp(const string& s);

	void erase(const string& s);

	vector<string> get_all();

	~trie();
};