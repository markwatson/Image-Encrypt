#include "accessjpeg.h"

// destructor
accessJpeg::~accessJpeg()
{
	// free the memory
	delete[] memblock;
}

// setfile also reads the file into memory.
bool accessJpeg::readInFile(char* in)
{
	ifstream in_file(in, ios::in|ios::binary|ios::ate);
	if (in_file.is_open())
	{
		size = in_file.tellg();
		memblock = new char [size];
		in_file.seekg(0, ios::beg);
		in_file.read(memblock, size);
		in_file.close();
	} else return false;

	return true;
}

bool accessJpeg::writeOutFile(char* out)
{
	ofstream out_file(out, ios::out|ios::binary);
	if (out_file.is_open())
	{
		out_file.write(memblock, size);
		out_file.close();
	} else return false;

	return true;
}
