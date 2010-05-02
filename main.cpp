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
		enc.process('e');

		// set output
		enc.setInFile( (char*) "MARBLES.JPG.OUT");
		enc.setOutFile( (char*) "MARBLES.UNENCED.JPG");

		// do decrypt
		enc.process('d');
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
