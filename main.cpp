#include <iostream>
#include <fstream>

#include "encryptjpeg.h"

using namespace std;

ifstream::pos_type size;
char * memblock;

int main() {
  // read entire file into memory
  ifstream in_file("MARBLES.JPG", ios::in|ios::binary|ios::ate);
  if (in_file.is_open())
  {
    size = in_file.tellg();
    memblock = new char [size];
    in_file.seekg(0, ios::beg);
    in_file.read(memblock, size);
    in_file.close();

    cout << "the complete file content is in memory" << endl;
  }
  else cout << "Unable to open file" << endl;
  
  // pass memblock somewhere.
  // memblock[i];
  
  
  // write file out
  ofstream out_file("MARBLES.JPG.OUT", ios::out|ios::binary);
  if (out_file.is_open())
  {
	out_file.write(memblock, size);
	out_file.close();
	
	// free the memory
	delete[] memblock;
  }
  else cout << "unable to open file for writing" << endl;
  
  return 0;
}
