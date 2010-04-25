image_encrypt: main.o encryptjpeg.o accessjpeg.o aesencrypt.o
	g++ -g main.o encryptjpeg.o accessjpeg.o aesencrypt.o -o image_encrypt
	rm *.o
	chmod +x+x+x image_encrypt
main.o: main.cpp
	g++ -g -c main.cpp
encryptjpeg.o: encryptjpeg.cpp
	g++ -g -c encryptjpeg.cpp
accessjpeg.o: accessjpeg.cpp
	g++ -g -c accessjpeg.cpp
aesencrypt.o: aesencrypt.cpp
	g++ -g -c aesencrypt.cpp

clean:
	rm -f image_encrypt *.o
