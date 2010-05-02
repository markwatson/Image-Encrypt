#include <iostream>
#include <iomanip>

#include "accessjpeg.h"
#include "aesencrypt.h"
#include "encryptjpeg.h"

bool encryptJpeg::process(char action)
{
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
	
	// set the key
	encrypter.setTextKey(key);
		
	// do the encryption
	ptr = file.accessBlock(); // get a block of the image
	if (action == 'e')
	{
		encrypter.encryptBlock(ptr); // run the encryption
	}
	else if (action == 'd')
	{
		encrypter.decryptBlock(ptr);
	}
	else
	{
		throw invalidAction();
		return false;
	}
	file.saveBlockBack(); // save out the block
	
	// write out the file
	out_success = file.writeOutFile(out_file);
	if (!out_success)
		throw invalidOutFile();
	
	return true;
}
