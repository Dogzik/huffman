#ifndef FILE_DECOMPRESSOR
#define FILE_DECOMPRESSOR

#include "file_reader.h"
#include "file_writer.h"
#include "decryptor.h"

vector<symbol> get_chars(size_t cnt, file_reader &reader);

vector<pair<uint16_t, uint16_t>> get_tree(size_t sz, file_reader &reader);

void write_decompressed_block(vector<symbol> const &block, file_writer &writer);

void decompress(string const &src, string const &dst);


#endif // !FILE_DECOMPRESSOR
