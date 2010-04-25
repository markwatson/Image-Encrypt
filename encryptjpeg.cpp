#include <iostream>
#include <iomanip>

#include "accessjpeg.h"
#include "aesencrypt.h"
#include "encryptjpeg.h"

using namespace std;

bool encryptJpeg::encrypt() {
	char * ptr; // ptr to a block
	bool in_success;
	bool out_success;

	// get file, returns errors if can't find
	in_success = file.readInFile(in_file);
	if (!in_success)
	{
		throw invalidInFile();
		return false;
	}
	
	// do the encryption
	ptr = file.accessBlock(); // get a block of the image

	
	// write out the file
	out_success = file.writeOutFile(out_file);
	if (!out_success)
		throw invalidOutFile();
	
	return true;
}

bool encryptJpeg::decrypt() {
	return true;
}
