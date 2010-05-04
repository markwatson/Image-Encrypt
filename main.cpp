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
		encryptJpeg dec;
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
		dec.setInFile( (char*) "MARBLES.JPG.OUT");
		dec.setOutFile( (char*) "MARBLES.UNENCED.JPG");
		dec.setPlainKey(key);

		// do decrypt
		dec.process('d');
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
