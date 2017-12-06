#include "file_reader.h"


file_reader::file_reader(string const &filename) : reader(filename, ifstream::binary), name(filename), cur_ind(0), end_ind(0)
{
	if (reader.fail())
	{
		reader.close();
		throw std::runtime_error("No file");
	}
}

file_reader::~file_reader()
{
	reader.close();
}

bool file_reader::eof()
{
	return (cur_ind == end_ind) && (reader.peek() == EOF);
}

symbol file_reader::get()
{
	if (cur_ind == end_ind) 
	{
		reader.read(buffer, BUFF_SIZE);
		end_ind = reader.gcount();
		cur_ind = 0;
	}
	return static_cast<symbol>(buffer[cur_ind++]);
}

uint16_t file_reader::get_short()
{
	uint16_t res = 0;
	if (eof())
	{
		throw std::runtime_error("Expected more data");
	}
	res += static_cast<uint16_t>(get());
	res <<= 8;
	if (eof())
	{
		throw std::runtime_error("Expected more data");
	}
	res += static_cast<uint16_t>(get());
	return res;
}