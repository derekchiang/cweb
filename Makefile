CC = clang
VERSION = 1.0.0

default: lib

lib:
	mkdir -p build
	cd build && \
	    $(CC) -fblocks -c -fPIC \
	    ../src/cweb_common.c ../src/cweb_router.c \
	    -I../include \
	    -I../3rdparty/apr/include \
	    -I../3rdparty/r3/include \
	    -I../3rdparty/libmicrohttpd/src/include
	$(CC) -shared -Wl,-soname,libcweb.so -o build/libcweb.so \
	    build/cweb_common.o build/cweb_router.o

examples: lib
	mkdir -p build
	$(foreach program,routing,\
	$(CC) -std=c11 -fblocks examples/$(program).c -o build/$(program) -I./include -L./build -lcweb \
	    -I./3rdparty/apr/include -L./3rdparty/apr/.libs -lapr-1 \
	    -L./3rdparty/r3/.libs -lr3 \
	    -L./3rdparty/libmicrohttpd/src/microhttpd/.libs -lmicrohttpd \
	    -lBlocksRuntime)

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

.PHONY: default main lib examples install clean 3rdparty

