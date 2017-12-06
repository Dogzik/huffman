#ifndef ENCRIPTOR
#define ENCRIPTOR

#include "tree.h"
#include "code.h"

struct encryptor: private tree
{
	encryptor() = delete;
	encryptor(accumulator const &acc);

	vector<symbol> get_symbols() const;
	vector<pair<uint16_t, uint16_t>> get_tree() const;

	code encrypt(vector<symbol> const &data) const;
private:
	void symbol_dfs(uint16_t v, vector<symbol> &a) const;
	void tree_dfs(uint16_t v, vector<pair<uint16_t, uint16_t>> &a) const;
};

#endif // !ENCRIPTOR
