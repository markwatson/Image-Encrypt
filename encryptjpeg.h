#ifndef ENCRYPTJPEG_H
#define ENCRYPTJPEG_H

#include <string>
#include "accessjpeg.h"
#include "aesencrypt.h"

class encryptJpeg
{
private:
	char* in_file;
	char* out_file;
	accessJpeg file;
	aesEncrypt encrypter;
	std::string key;
public:
	class invalidInFile {};
	class invalidOutFile {};
	class invalidAction {};

	void setInFile(char* in) {in_file = in;}
	void setOutFile(char* out) {out_file = out;}
	bool process(char *);
	void setPlainKey(std::string in_key) {key = in_key;}
};

#endif // ENCRYPTJPEG_H
