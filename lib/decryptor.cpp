#include "decryptor.h"

decryptor::decryptor() : tree(), ready(0) {}

void decryptor::initiate_decryption(vector<pair<uint16_t, uint16_t>> const &p, vector<symbol> const &syms) {
	build_tree(p, syms);
	ready = 1;
}

vector<symbol> decryptor::decrypt(code const &block) const
{
	if (!ready)
	{
		throw std::runtime_error("No decryption tree");
	}
	uint16_t cur = 0;

	vector<symbol> res;
	res.reserve(block.cnt);
	for (size_t i = 0; i < block.data.size(); i++)
	{

		symbol t = block.data[i];
		for (size_t j = 0; j < 8; j++)
		{
			cur = g[cur].sons[static_cast<bool>(t & (1 << (7 - j)))];
			if (g[cur].sym != NONE) {
				res.push_back(static_cast<symbol>(g[cur].sym));
				cur = 0;
			}
		}
	}
	res.erase(res.begin() + block.cnt, res.end());
	return res;
}
