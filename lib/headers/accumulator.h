#ifndef ACCUMULATOR
#define ACCUMULATOR

#include <vector>
#include "my_consts.h"
using std::vector;

struct accumulator 
{
	accumulator();

	void add_data(vector<symbol> const &a);

	ull get_cnt(size_t ind) const;

private:
	ull cnt[MAX_SYMB + 1];
};
#endif // !ACCUMULATOR
