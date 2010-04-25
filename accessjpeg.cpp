#include <iostream>
#include <iomanip>

#include "accessjpeg.h"

using namespace std;

// constructor
accessJpeg::accessJpeg()
{
	singleblock = new char [BLOCK_SIZE];
}

// destructor
accessJpeg::~accessJpeg()
{
	// free the memory
	delete[] memblock;
	delete[] singleblock;
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

		// initialize ptr.
		cursor = 0;
		// start at beginning of jpeg pixel data
		jumpToStart();
		 
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

// jumps to start of actual image data
// no need to encrypt the headers of the image and such...
// returns false if not a valid jpeg.
bool accessJpeg::jumpToStart()
{
	for (int cnt=0;cnt < size;cnt++)
	{
		if ((unsigned char) memblock[cnt] == 0xFF &&
			(unsigned char) memblock[cnt+1] == 0xDA)
		{
			cursor = cnt;
			cout << "!!!" << cursor << endl;
			return true;
		}
	}

	return false;
}

// access a block from the memory
char * accessJpeg::accessBlock()
{
	for(int cnt = 0;cnt < BLOCK_SIZE;cnt++)
	{
		singleblock[cnt] = memblock[cursor + cnt];
		cursor++;
	}

	return singleblock;
}
