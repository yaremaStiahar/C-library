#include "trie.h"

using namespace std;

trie::trie()
{
	root = new TrieNode(false);
}

TrieNode* trie::find(const string& s)
{
	TrieNode* p = root;
	for (const char& c : s)
	{
		p = p->go(c);
		if (p == nullptr)
			return nullptr;
	}
	if (p->is_terminal())
		return p;
	else
		return nullptr;
}

bool trie::contains(const string& s)
{
	TrieNode* p = find(s);
	if (p == nullptr)
		return false;
	return true;
}

void trie::insert(const string& s)
{
	TrieNode* p = root;
	for (const char& c : s)
	{
		p = p->add(c, p);
	}
	p->set_terminal(1);
}

string trie::largest_prefix(const string& s)
{
	TrieNode* p = root;
	int last_terminal = 0;
	for (int i = 0; i < s.size(); i++)
	{
		p = p->go(s[i]);
		if (p == nullptr)
			return s.substr(0, last_terminal);
		if (p->is_terminal())
			last_terminal = i + 1;
	}
	return s.substr(0, last_terminal);
}

string trie::lcp(const string& s)
{
	TrieNode* p = root;
	for (int i = 0; i < s.size(); i++)
	{
		p = p->go(s[i]);
		if (p == nullptr)
			return s.substr(0, i);
	}
	return s;
}

void trie::erase(const string& s)
{
	TrieNode* p = find(s);
	if (p == nullptr)
		return;
	if (!p->is_leaf())
		return;
	p->set_terminal(0);
	p = p->get_parent();
	p->erase(s.back());
	for (int i = int(s.size()) - 2; i >= 0; i--)
	{
		if (p->is_terminal())
			return;
		p->erase(s[i]);
	}
}

void trie::pre_order(vector<string>& vec, string& s, TrieNode* p)
{
	if (p->is_terminal())
		vec.push_back(s);
	for (auto& x : p->edges)
	{
		s += x.first;
		pre_order(vec, s, x.second);
		s.pop_back();
	}
}

vector<string> trie::get_all()
{
	vector<string> vec;
	string s = "";
	pre_order(vec, s, root);
	return vec;
}

trie::~trie()
{
	delete root;
}