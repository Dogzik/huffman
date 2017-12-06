#include <iostream>
#include "file_decompressor.h"

vector<symbol> get_chars(size_t cnt, file_reader &reader)
{
	vector<symbol> res(cnt);
	for (size_t i = 0; i < cnt; i++)
	{
		if (reader.eof())
		{
			throw std::runtime_error("Uncorrect decompressed file: More used characters expected\n");
		}
		res[i] = reader.get();
	}
	return res;
}

vector<pair<uint16_t, uint16_t>> get_tree(size_t sz, file_reader &reader)
{
	vector<pair<uint16_t, uint16_t>> res(sz);
	for (size_t i = 0; i < sz; i++)
	{
		try
		{
			res[i].first = reader.get_short();
		}
		catch (...)
		{
			throw std::runtime_error("Uncorrect decompressed file: missing tree data\n");
		}

		try
		{
			res[i].second = reader.get_short();
		}
		catch (...)
		{
			throw std::runtime_error("Uncorrect decompressed file: missing tree data\n");
		}
	}
	return res;
}

void write_decompressed_block(vector<symbol> const &block, file_writer &writer)
{
	for (auto x : block)
	{
		writer.put(x);
	}
}

void decompress(string const &src, string const &dst)
{
	try
	{
		file_reader check(src);
	}
	catch (...)
	{
		throw std::runtime_error("Try another file for decompression, this one is unavaliable or doesn't exist\n");
	}

	file_reader reader(src);
	file_writer writer(dst);
	size_t cnt = 0;

	try
	{
		cnt = static_cast<size_t>(reader.get_short());
	}
	catch (...)
	{
		throw std::runtime_error("Uncorrect decompressed file: no data for tree\n");
	}

	if (cnt < 2)
	{
		throw std::runtime_error("Uncorrect decompressed file: less then 2 characters\n");
	}

	vector<symbol> syms;
	try
	{
		syms = get_chars(cnt, reader);
	}
	catch (...)
	{
		throw;
	}

	vector<pair<uint16_t, uint16_t>> tree;
	try
	{
		tree = get_tree(cnt - 1, reader);
	}
	catch (...)
	{
		throw;
	}

	decryptor decompressor;
	try
	{
		decompressor.initiate_decryption(tree, syms);
	}
	catch (...)
	{
		throw;
	}

	vector<symbol> cur_block;
	while (!reader.eof())
	{
		size_t x, y;
		try
		{
			x = static_cast<size_t>(reader.get_short());
			y = static_cast<size_t>(reader.get_short());
		}
		catch (...)
		{
			throw std::runtime_error("Uncorrect decompressed file: cutted block found");
		}
		cur_block.resize(x);
		for (size_t i = 0; i < x; i++)
		{
			if (reader.eof())
			{
				throw std::runtime_error("Uncorrect decompressed file: cutted block found");
			}
			cur_block[i] = reader.get();
		}
		write_decompressed_block(decompressor.decrypt(code(cur_block, y)), writer);
	}
}