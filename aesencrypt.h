#ifndef AESENCRYPT_H
#define AESENCRYPT_H

#define BLOCK_SIZE 64

#include <string>

class aesEncrypt
{
private:
	int Nk, Nb, Nr; // lengths.
	std::string textkey;
	char* fullkey;
public:
	aesEncrypt();
	~aesEncrypt();
	bool encryptBlock(char*);
	void setTextKey(std::string);
	void expandKey();
};

#endif // AESENCRYPT_H
