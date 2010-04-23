#ifndef ACCESSJPEG_H
#define ACCESSJPEG_H

#include <fstream>

using namespace std;

class accessJpeg
{
private:
	ifstream::pos_type size;
	char * memblock;
public:
	~accessJpeg();
	bool readInFile(char* in);
	bool writeOutFile(char* out);
};

#endif // ACCESSJPEG_H
