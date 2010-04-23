#include "accessjpeg.h"
#include "aesencrypt.h"
#include "encryptjpeg.h"

bool encryptJpeg::encrypt() {
	bool in_success;
	bool out_success;

	// get file, returns errors if can't find
	in_success = file.readInFile(in_file);
	if (!in_success)
		throw invalidInFile();
	out_success = file.writeOutFile(out_file);
	if (!out_success)
		throw invalidOutFile();
	// get jpeg
	// (gets in blocks that we loop through and pass to encrypt)
	
	return true;
}

bool encryptJpeg::decrypt() {
	return true;
}
