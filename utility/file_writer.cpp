#include "file_writer.h"

file_writer::file_writer(string const &filename) : writer(filename, ofstream::binary), cur_ind(0) {}

file_writer::~file_writer()
{
	writer.write(buffer, cur_ind);
	writer.close();
}

void file_writer::put(symbol const c) {
	if (cur_ind == BUFF_SIZE) 
	{
		writer.write(buffer, cur_ind);
		cur_ind = 0;
	}
	buffer[cur_ind++] = static_cast<char>(c);
}

void file_writer::put_short(uint16_t const x)
{
	put(static_cast<symbol>(x >> 8));
	put(static_cast<symbol>((x << 8) >> 8));
}



