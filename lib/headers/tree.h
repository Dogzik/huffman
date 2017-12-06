#ifndef TREE
#define TREE

#include <utility>
#include "my_consts.h"
#include "accumulator.h"
#include "code_word.h"
using std::pair;

struct tree 
{
protected:
	struct node
	{
		vector<uint16_t> sons;
		uint16_t sym;

		node() : sons(), sym(NONE) {}
		node(uint16_t x) : sons(), sym(x) {}
		node(uint16_t a, uint16_t b) : sons(2), sym(NONE)
		{
			sons[0] = a;
			sons[1] = b;
		}
	};

	tree();
	tree(accumulator const &a);

	vector<node> g, tg;
	code_word codes[MAX_SYMB + 1];
	

	void build_tree(vector<pair<uint16_t, uint16_t>> const &p, vector<symbol> const &syms);

private:
	void renum_dfs(uint16_t v, uint16_t &num);
	void check_dfs(uint16_t v, uint16_t &num);
	void code_dfs(size_t v, code_word code);
	void throw_bad_tree() const;
	
};

#endif // !TREE

