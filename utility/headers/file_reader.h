#ifndef FILE_READER
#define FILE_READER

#include <string>
#include <fstream>
#include <cstdlib>

#include "my_consts.h"

using std::ifstream;
using std::string;


struct file_reader
{
	file_reader() = delete;
	file_reader(string const &filename);
	~file_reader();

	bool eof();

	symbol get();

	uint16_t get_short();

private:
	ifstream reader;
	string name;
	char buffer[BUFF_SIZE];
	size_t cur_ind, end_ind;
};

#endif // !FILE_READER