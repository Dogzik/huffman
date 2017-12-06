#ifndef CODE_WORD
#define CODE_WORD

#include "my_consts.h"

struct code_word 
{
	code_word();

	code_word(size_t a, size_t b);

	void add_bit(bool f);

	void erase_bit();

	bool get_bit(size_t ind) const;

	void clear();

	ull code;
	size_t len;
};

#endif // !CODE_WORD

