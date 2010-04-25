#include <iostream>
#include <fstream>

#include "encryptjpeg.h"

using namespace std;

int main()
{
	try
	{
		encryptJpeg enc;
		
		enc.setInFile( (char*) "MARBLES.JPG");
		enc.setOutFile( (char*) "MARBLES.JPG.OUT");
	
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
