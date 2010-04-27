#include "stdio.h"
#include <string>
#include <stdexcept>

#include "aesencrypt.h"

aesEncrypt::aesEncrypt()
{
	// set values
	Nk = 16;
	Nb = 16;
	Nr = 22; // extrapolated fom table for aes standard
	fullkey = NULL;
}

aesEncrypt::~aesEncrypt()
{
	if (fullkey != NULL)
		delete[] fullkey;
}

bool aesEncrypt::encryptBlock(char* block)
{
	return true;
}

void aesEncrypt::setTextKey(std::string key)
{
	// set the key
	fullkey = new char [Nk * 4];
	
	// go through the text key copying till full key is full
	int pos = 0; // start grabbing from string at 0
	for (int cnt = 0;cnt < BLOCK_SIZE;cnt++)
	{
		try
		{
			fullkey[cnt] = key.at(pos);
		}
		catch (std::out_of_range& e)
		{
			// recover by repeating key
			pos = pos - (key.length()+1);
			cnt--;
		}

		pos++; // incrmemnt string position
	}
}

void aesEncrypt::expandKey()
{

}
