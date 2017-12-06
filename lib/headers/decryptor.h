#ifndef DECRIPTOR
#define DECRIPTOR

#include "tree.h"
#include "code.h"

struct decryptor: private tree 
{
	decryptor();

	void initiate_decryption(vector<pair<uint16_t, uint16_t>> const &p, vector<symbol> const &syms);

	vector<symbol> decrypt(code const &block) const;
private:
	bool ready;
};

#endif // !DECRIPTOR
