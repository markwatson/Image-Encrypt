// Mark Watson
// CS 306
// Semester Project

#ifndef ACCESSJPEG_H
#define ACCESSJPEG_H

#define BLOCK_SIZE 16 

#include <fstream>

class accessJpeg
{
private:
	unsigned long int size;
	unsigned long int cursor;
public:
	char * memblock;
	
	accessJpeg();
	~accessJpeg();
	bool readInFile(char*);
	bool writeOutFile(char*);
	bool jumpToStart();
	char * accessBlock();
	bool hasMore();
};

#endif // ACCESSJPEG_H
