#include "TrieNode.h"

using namespace std;

TrieNode::TrieNode(bool is_term)
{
	parent = nullptr;
	edges = map<char, TrieNode*>();
	terminal = is_term;
}

TrieNode::TrieNode(bool is_term, TrieNode* par)
{
	parent = par;
	edges = map<char, TrieNode*>();
	terminal = is_term;
}

bool TrieNode::is_terminal()
{
	return terminal;
}

bool TrieNode::is_leaf()
{
	return edges.empty();
}

TrieNode* TrieNode::get_parent()
{
	return parent;
}

void TrieNode::set_terminal(bool is_term)
{
	terminal = is_term;
}

TrieNode* TrieNode::go(const char& c)
{
	return edges.count(c) ? edges[c] : nullptr;
}

TrieNode* TrieNode::add(const char& c, TrieNode* parent)
{
	if (edges.count(c))
		return edges[c];
	return edges[c] = new TrieNode(false, parent);
}

void TrieNode::erase(const char& c)
{
	delete go(c);
	edges.erase(c);
}

TrieNode::~TrieNode()
{
	for (auto& p : edges)
	{
		delete p.second;
	}
}