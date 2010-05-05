#ifndef AESENCRYPT_H
#define AESENCRYPT_H

#define BLOCK_SIZE 16

#include <string>
#include <bitset>
#include "stdio.h"

class aesEncrypt
{
private:
	int Nk, Nb, Nr; // lengths.
	std::string textkey;
	char* expandedkey;
public:
	char* fullkey;
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

	unsigned char sboxify(unsigned char val);
	unsigned char invsboxify(unsigned char val);
	unsigned char roundify(unsigned char index);
	
	unsigned char ffmul(unsigned char, unsigned char);
	
	// testing
	void print(char* block, int length=16){
		printf("\n-----\n");
		for (int cnt = 0; cnt < length; cnt++) {
			if (cnt % 4 == 0) printf("\n");
			printf("%3x", (unsigned char) block[cnt]);
		}
	}
		
	// assumes a word
	void rotate_left(unsigned char * tmp) {
		unsigned char trimmings;
		trimmings = tmp[0];
		tmp[0] = tmp[1];
		tmp[1] = tmp[2];
		tmp[2] = tmp[3];
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
	unsigned char rcon(unsigned char in) {
		unsigned char c=1;
		if(in == 0)  
		        return 0; 
		while(in != 1) {
			unsigned char b;
			b = c & 0x80;
			c <<= 1;
			if(b == 0x80) {
				c ^= 0x1b;
			}
		        in--;
		}
		return c;
	}

};

#endif // AESENCRYPT_H
