#ifndef ACCESSJPEG_H
#define ACCESSJPEG_H

#define BLOCK_SIZE 4

#include <fstream>

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
	bool readInFile(char*);
	bool writeOutFile(char*);
	bool jumpToStart();
	char * accessBlock();
	bool saveBlockBack();
};

#endif // ACCESSJPEG_H
