#include "stdio.h"
#include <string>
#include <stdexcept>

#include "aesencrypt.h"

aesEncrypt::aesEncrypt()
{
	// set values
	Nk = 4; // this is in words
	Nb = BLOCK_SIZE; // !! important, this is in bytes, not words
	Nr = 10; // extrapolated fom table for aes standard
	fullkey = NULL;
	expandedkey = NULL;
}

aesEncrypt::~aesEncrypt()
{
	if (fullkey != NULL)
		delete[] fullkey;
	if (expandedkey != NULL)
		delete[] expandedkey;
}

bool aesEncrypt::encryptBlock(char* block)
{
	xorRoundKey(block, expandedkey);
	for(int cnt = 1;cnt <= (Nr-1);cnt++)
	{
		subBytes(block);
		shiftRows(block);
		mixColumns(block);
		xorRoundKey(block, expandedkey + (cnt * Nb));
	}
	subBytes(block);
	shiftRows(block);
	xorRoundKey(block, expandedkey + (Nr * Nb));
	
	return true; // could error check in future
}

bool aesEncrypt::decryptBlock(char* block)
{
	xorRoundKey(block, expandedkey + (Nr * Nb));

	for(int cnt = Nr-1; cnt > 0;cnt--)
	{
		invShiftRows(block);
		invSubBytes(block);
		xorRoundKey(block, expandedkey + cnt * Nb);
		invMixColumns(block);
	}

	invShiftRows(block);
	invSubBytes(block);
	xorRoundKey(block, expandedkey);
	
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
	
	expandKey();
}

void aesEncrypt::expandKey()
{
	// limit
	int limit = (Nb/4)*(Nr+1);
	// grab some fresh memory for the expanded key
	expandedkey = new char [4*limit];
	// main counter
	int cnt;
	// temp loaction
	unsigned char temp[4];

	// set first key
	for(cnt = 0;cnt < Nk;cnt++)
	{
		for (int n = 0; n < 4; n++)
		{
			expandedkey[cnt*4+n] = fullkey[cnt*4+n];
		}
	}
	// continue where we left off with other keys
	for (cnt = Nk;cnt < limit;cnt++)
	{
		// copy key into temp location
		for(int n=0;n<4;n++)
		{
			temp[n] = expandedkey[(cnt-1)*4+n];
		}
		if ((cnt % Nk) == 0)
		{
			// rotate and then sboxify
			rotate_left(temp);
			for (int n = 0;n<4;n++)
				temp[n] = sboxify(temp[n]);
			// round
			temp[0] ^= roundify(cnt/Nk);
		}
		// xor temp
		for (int n = 0; n < 4; n++)
		{
			expandedkey[cnt*4+n] = expandedkey[(cnt-Nk)*4+n] ^ temp[n];
		}
	}
	// rearrange
	unsigned char temp2[Nb];
	for (int all = 0; all <= Nr;all++)
	{
		// copy into temp
		for (int i = 0; i < Nb; i++)
		{
			temp[i] = expandedkey[Nb*all+i];
		}
		for (cnt = 0;cnt < Nb/4;cnt++)
		{
			for (int i = 0; i < Nb/4;i++)
			{
				expandedkey[Nb*all+(cnt+i*4)] = temp[i+cnt*4];
			}
		}
	}
}

void aesEncrypt::subBytes(char * state)
{
	for (int cnt = 0;cnt < Nb;cnt++)
	{
		state[cnt] = sboxify(state[cnt]);
	}
}

void aesEncrypt::invSubBytes(char * state)
{
	for (int cnt = 0;cnt < Nb;cnt++)
	{
		state[cnt] = invsboxify(state[cnt]);
	}
}

void aesEncrypt::invShiftRows(char * state)
{
	for (int row = 1; row <4; row++)
	{
		// see below
		for (int n = 1; n < (row+1); n++)
		{
			rotate_right((unsigned char*) state + (row*4));
		}
	}
}

void aesEncrypt::invMixColumns(char * state)
{
	unsigned char temp[4];

	for (int col = 0; col < (Nb/4); col++)
	{
		for (int n = 0; n < 4; n++)
		{
			temp[n] = state[n*4+col];
		}
		for (int cnt = 0; cnt < 4; cnt++)
		{
			state[cnt*4+col] = ffmul(0x0e, temp[cnt]) ^
			                   ffmul(0x0b, temp[(cnt+1) % 4]) ^
			                   ffmul(0x0d, temp[(cnt+2) % 4]) ^
			                   ffmul(0x09, temp[(cnt+3) % 4]); 
		}
	}
}

void aesEncrypt::shiftRows(char * state)
{
	for (int row = 1; row < 4;row++)
	{
		// shift it over needed amount of times
		// 0 for row 1, 1, for row 2, etc.
		for (int n = 1; n < (row+1);n++)
		{
			// pass in a pointer to the row
			rotate_left((unsigned char*) state + (row*4));
		}
	}
}

void aesEncrypt::mixColumns(char * state)
{
	unsigned char temp[4];

	for (int col = 0; col < (Nb/4); col++)
	{
		for (int n = 0; n < 4; n++)
		{
			temp[n] = state[n*4+col]; //state[col*4+n];
		}
		for (int cnt = 0; cnt < 4; cnt++)
		{
			state[cnt*4+col] = ffmul(0x02, temp[cnt]) ^
			                   ffmul(0x03, temp[(cnt+1) % 4]) ^
			                   temp[(cnt+2) % 4] ^
			                   temp[(cnt+3) % 4];

		}
	}
}

void aesEncrypt::xorRoundKey(char * state, char * key)
{
	for (int cnt = 0;cnt < Nb;cnt++)
	{
		state[cnt] ^= key[cnt];
	}
}


// this function multiplies two values
// ints are passed in to deal with overflow
unsigned char aesEncrypt::ffmul(unsigned char x, unsigned char y) {
	if (x == 0 && y == 0) return 0; // special case...
	// bitsets
	std::bitset<8> p (0);
	std::bitset<8> a (x);
	std::bitset<8> b (y);
	// bool
	bool left_a;
	// run
	for(int cnt = 0; cnt < 8;cnt++)
	{
		if (b[0]) p ^= a;
		left_a = a[7];
		a<<=1;
		if (left_a) a^=0x1b;
		b>>=1;
	}
	return (unsigned char) p.to_ulong();
}

unsigned char aesEncrypt::sboxify(unsigned char val)
{
	//printf("\n sbox: %i \n", val);
	unsigned char sbox[256] = {
	//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  //F
	};
	return sbox[val];
}

unsigned char aesEncrypt::invsboxify(unsigned char val)
{
	unsigned char sbox[256] = {
	//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
	};
	return sbox[val];
}

unsigned char aesEncrypt::roundify(unsigned char index)
{
	unsigned char round[255] = {  
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,   
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,   
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,   
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,   
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,   
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,   
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,   
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,   
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,   
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,   
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,   
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,   
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,   
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,   
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,   
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb
	};
	return round[index];
}
