#ifndef ENCRYPTJPEG_H
#define ENCRYPTJPEG_H

#include "accessjpeg.h"

class encryptJpeg
{
private:
	char* in_file;
	char* out_file;
	accessJpeg file;
public:
	class invalidInFile {};
	class invalidOutFile {};
	void setInFile(char* in) {in_file = in;}
	void setOutFile(char* out) {out_file = out;}
	bool encrypt();
	bool decrypt();
};

#endif // ENCRYPTJPEG_H
