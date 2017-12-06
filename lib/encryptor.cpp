#include "encryptor.h"
#include <algorithm>

encryptor::encryptor(accumulator const &acc): tree(acc) {}

vector<symbol> encryptor::get_symbols() const
{
	vector<symbol> ans;
	symbol_dfs(0, ans);
	return ans;
}

vector<pair<uint16_t, uint16_t>> encryptor::get_tree() const
{
	vector<pair<uint16_t, uint16_t>> ans;
	tree_dfs(0, ans);
	return ans;
}

code encryptor::encrypt(vector<symbol> const &data) const
{
	vector<ull> tres(data.size(), 0);
	size_t cur_ind = 0;
	for (auto x : data)
	{
		code_word t = codes[x];
		tres[cur_ind >> 6] |= t.code >> (cur_ind & 63);
		size_t written = std::min(64 - (cur_ind & 63), t.len);
		cur_ind += written;

		tres[cur_ind >> 6] |= t.code << written;
		cur_ind += t.len - written;
	}

	vector<symbol> res(8 * tres.size());
	for (size_t i = 0; i < tres.size(); i++)
	{
		for (size_t j = 0; j < 8; j++) {
			res[i * 8 + j] = static_cast<symbol>(((tres[i] >> (8 * (7 - j))) << (56)) >> 56);
		}
	}
	res.resize((cur_ind >> 3) + static_cast<size_t>((cur_ind & 7) != 0));
	return code(res, data.size());

}

void encryptor::symbol_dfs(uint16_t v, vector<symbol> &a) const
{
	if (g[v].sym != NONE) {
		a.push_back(static_cast<symbol>(g[v].sym));
	}
	for (auto x : g[v].sons)
	{
		symbol_dfs(x, a);
	}
}

void encryptor::tree_dfs(uint16_t v, vector<pair<uint16_t, uint16_t>> &a) const
{
	if (!g[v].sons.empty()) {
		a.push_back({ v, g[v].sons.back() });
	}
	for (auto x : g[v].sons)
	{
		tree_dfs(x, a);
	}
}