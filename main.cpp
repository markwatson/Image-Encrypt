#include <iostream>
#include <fstream>
#include <string>

#include "encryptjpeg.h"

#include "aesencrypt.h"

using namespace std;

int main(int argc, char *argv[])
{
	// validate command line arguments
	if (argc != 4 || (argv[1][1] != 'e' && argv[1][1] != 'd'))
	{
		cout << "Invalid command line arguments." << endl
		     << "Please something like the following:" << endl
		     << "\t To encrypt: \t image_encrypt -e <input> <output>\n"
			 << "\t To decrypt: \t image_encrypt -d <input> <output>\n";
		return 0;
	}

	// run encryption
	try
	{
		// variables
		encryptJpeg enc;
		string key;
		
		// set files
		enc.setInFile(argv[2]);
		enc.setOutFile(argv[3]);
		
		// set key
		cout << "Please enter a key: ";
		cin >> key;
		enc.setPlainKey(key);

		// do the actual encryption
		enc.process(argv[1][1]);
	}
	catch(encryptJpeg::invalidInFile)
	{
		cout << "That input file is not valid" << endl;
	}
	catch(encryptJpeg::invalidOutFile)
	{
		cout << "Could not open output file for writing" << endl;
	}
	catch(encryptJpeg::invalidAction)
	{
		cout << "The program encountered an internal error..." << endl;
	}

	return 0;
}
