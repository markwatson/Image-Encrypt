image_compress: main.o encryptjpeg.o
	g++ main.o encryptjpeg.o -o image_compress
	rm main.o
main.o: main.cpp
	g++ -c main.cpp
encryptjpeg.o: encryptjpeg.cpp
	g++ -c encryptjpeg.cpp

clean:
	rm -f image_compress *.o
