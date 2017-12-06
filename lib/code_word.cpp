#include "code_word.h"

code_word::code_word() : code(0), len(0){}

code_word::code_word(size_t a, size_t b) : code(a), len(b) {}

void code_word::add_bit(bool f)
{	
	//code &= ULLONG_MAX - (1 << len);
	code |= (static_cast<ull>(f)) << len;
	len++;
}

void code_word::erase_bit()
{
	len--;
}

bool code_word::get_bit(size_t ind) const
{
	return static_cast<bool>(code & (1ULL << ind));
}


void code_word::clear()
{
	code = 0;
	len = 0;
}