lib/libtecplotreader.so : lib/tecplotreader.o lib/reader_ctypes.o
	g++ -shared -o lib/libtecplotreader.so lib/tecplotreader.o lib/reader_ctypes.o lib/libtecio.a

lib/tecplotreader.o : src/tecplotReader.cpp src/tecplotReader.h
	g++ -c -fPIC src/tecplotReader.cpp -o lib/tecplotreader.o

lib/reader_ctypes.o : src/reader_ctypes.cpp
	g++ -c -fPIC src/reader_ctypes.cpp -o lib/reader_ctypes.o
