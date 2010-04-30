#include <iostream>
#include <fstream>
#include <string>

#include "encryptjpeg.h"

using namespace std;

int main()
{
	try
	{
		// variables
		encryptJpeg enc;
		string key;
		
		// set files
		enc.setInFile( (char*) "MARBLES.JPG");
		enc.setOutFile( (char*) "MARBLES.JPG.OUT");
		
		// set key
		cout << "Please enter a key: ";
		cin >> key;
		enc.setPlainKey(key);

		// do the actual encryption
		enc.process("encrypt");

		// set output
		enc.setInFile( (char*) "MARBLES.JPG.OUT");
		enc.setOutFile( (char*) "MARBLES.UNENCED.JPG");

		// do decrypt
		enc.process("decrypt");
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
		cout << "there was a problem internal to the program..." << endl;
	}

	return 0;
}
