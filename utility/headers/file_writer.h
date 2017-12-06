#ifndef FILE_WRITER
#define FILE_WRITER

#include <string>
#include <fstream>
#include <cstdlib>

#include "my_consts.h"

using std::ofstream;
using std::string;


struct file_writer
{
	file_writer() = delete;
	file_writer(string const &filename);
	~file_writer();

	void put(symbol const c);

	void put_short(uint16_t const x);

private:
	ofstream writer;
	char buffer[BUFF_SIZE];
	size_t cur_ind;
};
#endif // !FILE_WRITER