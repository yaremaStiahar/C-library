#pragma once
#include <map>

using namespace std;

struct TrieNode
{
private:
	TrieNode* parent;
	bool terminal;

public:
	map<char, TrieNode*> edges;

	TrieNode(bool is_term);

	TrieNode(bool is_term, TrieNode* par);

	bool is_terminal();

	TrieNode* get_parent();

	void set_terminal(bool is_term);

	bool is_leaf();

	TrieNode* go(const char& c);
	
	TrieNode* add(const char& c, TrieNode* parent);

	void erase(const char& c);

	~TrieNode();
};