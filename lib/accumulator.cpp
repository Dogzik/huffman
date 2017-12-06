#include "accumulator.h"

#include <cstring>

accumulator::accumulator() {
	memset(cnt, 0, (MAX_SYMB + 1) * sizeof(ull));
}

void accumulator::add_data(vector<symbol> const &a)
{
	for (auto x : a)
	{
		cnt[x]++;
	}
}

ull accumulator::get_cnt(size_t ind) const
{
	return cnt[ind];
}
