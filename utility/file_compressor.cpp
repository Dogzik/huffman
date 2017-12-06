#include <iostream>
#include "file_compressor.h"
#include "decryptor.h"

accumulator get_count(string const &filename) noexcept
{
	accumulator res;
	file_reader reader(filename);
	vector<symbol> block;
	while (!reader.eof()) {
		if (block.size() == BLOCK_SIZE)
		{
			res.add_data(block);
			block.clear();
		}
		block.push_back(reader.get());
	}
	res.add_data(block);
	return res;
}

void write_compressed_block(code const &block, file_writer &writer)
{
	writer.put_short(static_cast<uint16_t>(block.data.size()));
	writer.put_short(static_cast<uint16_t>(block.cnt));
	for (auto t : block.data)
	{
		writer.put(t);
	}
}

void compress(string const &src, string const &dst)
{
	try 
	{
		file_reader check(src);
	}
	catch (...)
	{
		throw std::runtime_error("Try another file for compression, this one is unavaliable or doesn't exist\n");
	}

	encryptor compressor(get_count(src));
	file_reader reader(src);
	file_writer writer(dst);

	vector<symbol> chars(compressor.get_symbols());
	vector<pair<uint16_t, uint16_t>> tree(compressor.get_tree());

	writer.put_short(static_cast<uint16_t>(chars.size()));
	for (auto x : chars)
	{
		writer.put(x);
	}
	for (auto t : tree)
	{
		writer.put_short(t.first);
		writer.put_short(t.second);
	}

	vector<symbol> block;
	block.reserve(BLOCK_SIZE);
	while (!reader.eof()) {
		if (block.size() == BLOCK_SIZE)
		{
			write_compressed_block(compressor.encrypt(block), writer);
			block.clear();
			block.reserve(BLOCK_SIZE);
		}
		block.push_back(reader.get());
	}
	if (!block.empty())
	{
		write_compressed_block(compressor.encrypt(block), writer);
	}
}
