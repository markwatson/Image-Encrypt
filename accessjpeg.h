#ifndef ACCESSJPEG_H
#define ACCESSJPEG_H

#define BLOCK_SIZE 64 // blocksize in bytes

#include <fstream>

using namespace std;

class accessJpeg
{
private:
	unsigned long int size;
	unsigned long int cursor;
public:
	char * singleblock; // single block of img to pass back
	char * memblock;
	
	accessJpeg();
	~accessJpeg();
	bool readInFile(char* in);
	bool writeOutFile(char* out);
	bool jumpToStart();
	char * accessBlock();
	bool saveBlockBack();
};

#endif // ACCESSJPEG_H
