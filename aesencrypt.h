#ifndef AESENCRYPT_H
#define AESENCRYPT_H

#define BLOCK_SIZE 16

#include <string>
#include <bitset>

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
	bool decryptBlock(char*);
	void setTextKey(std::string, char);
	void expandKey();
	void invExpandKey();

	void subBytes(char *);
	void invSubBytes(char *);
	void shiftRows(char *);
	void invShiftRows(char *);
	void mixColumns(char *);
	void invMixColumns(char *);
	void xorRoundKey(char *, char *);

	unsigned char sboxify(int val);
	unsigned char invsboxify(int val);
	unsigned char roundify(int index);
	
	unsigned char ffmul(unsigned char, unsigned char);
	
	// this one sboxifies a whole word (4 bytes)
	void sboxify(unsigned char * tmp) {
		tmp[0] = sboxify(tmp[0]);
		tmp[1] = sboxify(tmp[1]);
		tmp[2] = sboxify(tmp[2]);
		tmp[3] = sboxify(tmp[3]);
	}
	
	// assumes a word
	void rotate_left(unsigned char * tmp) {
		unsigned char trimmings;
		trimmings = tmp[0];
		tmp[0] = tmp[1];
		tmp[1] = tmp[2];
		tmp[3] = trimmings;
	}
	void rotate_right(unsigned char * tmp) {
		unsigned char trimmings;
		trimmings = tmp[3];
		tmp[3] = tmp[2];
		tmp[2] = tmp[1];
		tmp[1] = tmp[0];
		tmp[0] = trimmings;
	}
};

#endif // AESENCRYPT_H
