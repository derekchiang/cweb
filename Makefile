CC = clang
VERSION = 1.0.0

default: lib

lib:
	mkdir -p build
	$(CC) -fblocks -c -fPIC src/cweb_router.c -o build/cweb.o -I./include \
	    -I./3rdparty/apr/include \
	    -I./3rdparty/r3/include \
	    -I./3rdparty/libmicrohttpd/src/include
	$(CC) -shared -Wl,-soname,libcweb.so -o build/libcweb.so build/cweb.o

main: lib
	mkdir -p build
	$(CC) -std=c11 -fblocks main.c -o build/main -I ./include -L./build -lcweb \
	    -L./3rdparty/apr/.libs -lapr-1 \
	    -L./3rdparty/r3/.libs -lr3 \
	    -L./3rdparty/libmicrohttpd/src/microhttpd/.libs -lmicrohttpd \
	    -lBlocksRuntime

run: main
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./build ./build/main


install: lib
	cp -R include/* /usr/local/include
	cp build/libcweb* /usr/local/lib

3rdparty:
	# apr
	cd 3rdparty/apr && ./configure && make && sudo make install
	# r3
	cd 3rdparty/r3 && ./autogen.sh && ./configure && make && sudo make install
	# libmicrohttpd
	cd 3rdparty/libmicrohttpd && ./configure && make && sudo make install
	
clean:
	rm -rf build

.PHONY: default main run lib install clean 3rdparty

