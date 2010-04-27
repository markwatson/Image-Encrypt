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
		enc.encrypt();  
	}
	catch(encryptJpeg::invalidInFile)
	{
		cout << "That input file is not valid" << endl;
	}
	catch(encryptJpeg::invalidOutFile)
	{
		cout << "Could not open output file for writing" << endl;
	}

	return 0;
}
