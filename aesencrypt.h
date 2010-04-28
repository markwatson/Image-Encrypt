#ifndef AESENCRYPT_H
#define AESENCRYPT_H

#define BLOCK_SIZE 4

#include <string>

class aesEncrypt
{
private:
	int Nk, Nb, Nr; // lengths.
	std::string textkey;
	char* fullkey;
	char* expandedkey;
public:
	aesEncrypt();
	~aesEncrypt();
	bool encryptBlock(char*);
	void setTextKey(std::string);
	void expandKey();

	void subBytes(char *);

	unsigned char sboxify(int val);
	unsigned char roundify(int index);
	
	// this one sboxifies a whole word (4 bytes)
	void sboxify(unsigned char * tmp) {
		tmp[0] = sboxify(tmp[0]);
		tmp[1] = sboxify(tmp[1]);
		tmp[2] = sboxify(tmp[2]);
		tmp[3] = sboxify(tmp[3]);
	}

	void rotate(unsigned char * tmp) {
		unsigned char trimmings;
		trimmings = tmp[0];
		tmp[0] = tmp[1];
		tmp[1] = tmp[2];
		tmp[3] = trimmings;
	}
};

#endif // AESENCRYPT_H
