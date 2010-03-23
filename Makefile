image_compress: main.o
	g++ main.o -o image_compress
	rm main.o
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f image_compress *.o
