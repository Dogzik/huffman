#ifndef MY_CONSTS 
#define MY_CONSTS

#include <stdexcept>
#include <cstdlib>
#include <cstdint>

typedef unsigned char symbol;
typedef unsigned long long ull;
typedef unsigned int ui;

const size_t BUFF_SIZE = static_cast<size_t>(1e4);
const size_t BLOCK_SIZE = static_cast<size_t>(1e4);
const size_t MAX_SYMB = 255;
const uint16_t NONE = 600;

#endif // !MY_CONSTS 
