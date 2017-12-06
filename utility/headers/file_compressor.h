#ifndef FILE_COMPRESSOR
#define FILE_COMPRESSOR

#include "file_reader.h"
#include "file_writer.h"
#include "encryptor.h"

accumulator get_count(string const &filename) noexcept;

void write_compressed_block(code const &block, file_writer &writer);

void compress(string const &src, string const &dst);

#endif // !FILE_COMPRESSOR

