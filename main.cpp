#include <iostream>
#include <fstream>
#include <string>

#include "encryptjpeg.h"

#include "aesencrypt.h"

using namespace std;

int main()
{
	/*try
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
	}*/

	// testing
	aesEncrypt aes;
	aes.fullkey = new char [16];
	aes.fullkey[0] = 0x2b;
	aes.fullkey[1] = 0x7e;
	aes.fullkey[2] = 0x15;
	aes.fullkey[3] = 0x16;
	aes.fullkey[4] = 0x28;
	aes.fullkey[5] = 0xae;
	aes.fullkey[6] = 0xd2;
	aes.fullkey[7] = 0xa6;
	aes.fullkey[8] = 0xab;
	aes.fullkey[9] = 0xf7;
	aes.fullkey[10] = 0x15;
	aes.fullkey[11] = 0x88;
	aes.fullkey[12] = 0x09;
	aes.fullkey[13] = 0xcf;
	aes.fullkey[14] = 0x4f;
	aes.fullkey[15] = 0x3c;
	char * block;
	block = new char [16];
	block[0] = 0x32;
	block[1] = 0x43;
	block[2] = 0xf6;
	block[3] = 0xa8;
	block[4] = 0x88;
	block[5] = 0x5a;
	block[6] = 0x30;
	block[7] = 0x8d;
	block[8] = 0x31;
	block[9] = 0x31;
	block[10] = 0x98;
	block[11] = 0xa2;
	block[12] = 0xe0;
	block[13] = 0x37;
	block[14] = 0x07;
	block[15] = 0x34;
	
	aes.expandKey();
	bool succ;
	succ = aes.encryptBlock(block);
	
	printf("Final result");
	for (int cnt = 0; cnt < 16; cnt++) {
		if (cnt % 4 == 0) printf("\n");
		printf("%3x", (unsigned char) block[cnt]);
	}

	return 0;
}
