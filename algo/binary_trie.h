#pragma once
#include <inttypes.h>

using namespace std;

// Bits <= 64
template <size_t Bits>
struct binary_trie
{
private:
	const int n = Bits;
	struct node
	{
		node* ptr[2];

		node()
		{
			ptr[0] = nullptr;
			ptr[1] = nullptr;
		}

		~node()
		{
			delete ptr[0];
			delete ptr[1];
		}
	};
	node* root;

public:

	binary_trie()
	{
		root = new node();
	}

	int sz()
	{
		return n;
	}

	void insert(uintmax_t x)
	{
		auto p = root;
		for (int i = n - 1; i >= 0; i--)
		{
			int bit = (x >> i) & 1;
			if (p->ptr[bit] == nullptr)
			{
				p->ptr[bit] = new node();
			}
			p = p->ptr[bit];
		}
	}

	bool contains(uintmax_t x)
	{
		auto p = root;
		for (int i = n - 1; i >= 0; i--)
		{
			int bit = (x >> i) & 1;
			if (p->ptr[bit] == nullptr)
			{
				return false;
			}
			p = p->ptr[bit];
		}
		return true;
	}
	
	void erase(uintmax_t x)
	{
		if (!contains(x))
			return;
		auto p = root;
		auto last = root;
		int last_bit = int(n) - 1;
		for (int i = n - 1; i >= 0; i--)
		{
			int bit = (x >> i) & 1;
			if (p->ptr[bit ^ 1] != nullptr)
			{
				last = p;
				last_bit = i;
			}
			p = p->ptr[bit];
		}
		delete last->ptr[(x >> last_bit) & 1];
		last->ptr[(x >> last_bit) & 1] = nullptr;
	}

	uintmax_t max_xor(uintmax_t x)
	{
		uintmax_t y = 0;
		auto p = root;
		for (int i = n - 1; i >= 0; i--)
		{
			int bit = (x >> i) & 1;
			if (p->ptr[bit ^ 1] != nullptr)
			{
				y |= 1ll << i;
				p = p->ptr[bit ^ 1];
			}
			else
				p = p->ptr[bit];
		}
		return y;
	}

	uintmax_t min_xor(uintmax_t x)
	{
		uintmax_t y = 0;
		auto p = root;
		for (int i = n - 1; i >= 0; i--)
		{
			int bit = (x >> i) & 1;
			if (p->ptr[bit] != nullptr)
			{
				p = p->ptr[bit];
			}
			else
			{
				y |= 1ll << i;
				p = p->ptr[bit ^ 1];
			}
		}
		return y;
	}
};
