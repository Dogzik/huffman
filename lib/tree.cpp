#include "tree.h"
#include <cstring>
#include <set>
#include <utility>
#include <stdexcept>

using std::set;

tree::tree() {}

tree::tree(accumulator const &a): tree()
{
	set<pair<ull, uint16_t>> ver;
	uint16_t cnt = 0;
	for (uint16_t i = 0; i <= MAX_SYMB; i++)
	{
		if (a.get_cnt(i) > 0)
		{
			ver.insert({ a.get_cnt(i), cnt });
			tg.push_back(node(i));
			cnt++;
		}
	}
	if (tg.size() == 1) {
		ver.insert({ a.get_cnt(tg[0].sym), tg[0].sym + uint16_t(1) });
		tg.push_back(node(tg[0].sym + uint16_t(1)));
		cnt++;
	}
	else if (tg.size() == 0)
	{
		for (uint16_t i = 0; i < 2; i++)
		{
			ver.insert({ ull(i), i });
			tg.push_back(node(i));
			cnt++;
		}
	}
	while (ver.size() > 1)
	{
		ull sum = ver.begin()->first;
		uint16_t v1 = ver.begin()->second;
		ver.erase(ver.begin());

		sum += ver.begin()->first;
		uint16_t v2 = ver.begin()->second;
		ver.erase(ver.begin());

		tg.push_back(node(v1, v2));
		ver.insert({ sum, cnt++ });
	}
	g.resize(cnt);
	uint16_t temp = 0;
	renum_dfs(cnt - 1, temp);
	code_dfs(0, code_word());

	for (size_t i = 0; i < MAX_SYMB + 1; i++)
	{
		code_word t = codes[i];
		size_t ncode = 0;
		for (size_t i = 0; i < 64; i++)
		{
			size_t q = t.get_bit(i);
			ncode |= (q << (63 - i));
		}
		codes[i] = code_word(ncode, t.len);
	}

	tg.clear();
	tg.shrink_to_fit();
}

void tree::build_tree(vector<pair<uint16_t, uint16_t>> const &p, vector<symbol> const &syms)
{
	g.resize(2 * p.size() + 1);
	if (p[0].first != 0)
	{
		throw_bad_tree();
	}
	for (auto t : p)
	{
		if (t.first >= g.size() || t.second >= g.size())
		{
			throw_bad_tree();
		}
		if (t.first + 1 >= t.second)
		{
			throw_bad_tree();
		}
		g[t.first].sons.push_back(t.first + 1);
		g[t.first].sons.push_back(t.second);
	}
	size_t ind = 0;
	for (size_t i = 0; i < g.size(); i++)
	{
		if (g[i].sons.empty())
		{
			if (ind < syms.size())
			{
				g[i].sym = syms[ind++];
			}
			else
			{
				throw_bad_tree();
			}
		}
		else if (g[i].sons.size() != 2)
		{
			throw_bad_tree();
		}
	}
	if (ind != syms.size())
	{
		throw_bad_tree();
	}
	uint16_t temp = 0;
	check_dfs(0, temp);
	code_word t;
	code_dfs(0, t);
}

void tree::code_dfs(size_t v, code_word code)
{
	if (g[v].sym != NONE)
	{
		codes[g[v].sym] = code;
	}
	for (size_t i = 0; i < g[v].sons.size(); i++) {
		code.add_bit(static_cast<bool>(i));
		code_dfs(g[v].sons[i], code);
		code.erase_bit();
	}
}

void tree::renum_dfs(uint16_t v, uint16_t &num)
{
	uint16_t ind = num;
	g[ind].sym = tg[v].sym;
	if (!tg[v].sons.empty())
	{
		g[ind].sons.resize(2);
		g[ind].sons[0] = ++num;
		renum_dfs(tg[v].sons[0], num);
		g[ind].sons[1] = ++num;
		renum_dfs(tg[v].sons[1], num);
	}
}

void tree::check_dfs(uint16_t v, uint16_t &num)
{
	if (v != num)
	{
		throw_bad_tree();
	}
	if (!g[v].sons.empty())
	{
		num++;
		check_dfs(g[v].sons[0], num);
		num++;
		check_dfs(g[v].sons[1], num);
	}
}


void tree::throw_bad_tree() const
{
	throw std::runtime_error("Decomressed file is damaged");
}