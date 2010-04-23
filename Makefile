image_compress: main.o encryptjpeg.o accessjpeg.o aesencrypt.o
	g++ main.o encryptjpeg.o accessjpeg.o aesencrypt.o -o image_compress
	rm *.o
	chmod +x+x+x image_compress
main.o: main.cpp
	g++ -c main.cpp
encryptjpeg.o: encryptjpeg.cpp
	g++ -c encryptjpeg.cpp
accessjpeg.o: accessjpeg.cpp
	g++ -c accessjpeg.cpp
aesencrypt.o: aesencrypt.cpp
	g++ -c aesencrypt.cpp

clean:
	rm -f image_compress *.o
