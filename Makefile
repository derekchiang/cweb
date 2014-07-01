CC = clang
VERSION = 1.0.0

default: lib

lib:
	mkdir -p build
	cd build && \
	    $(CC) -fblocks -c -fPIC \
	    ../src/cweb_common.c ../src/cweb_router.c ../src/cweb_server.c\
	    -I../include \
	    -I../3rdparty/apr/include \
	    -I../3rdparty/r3/include \
	    -I../3rdparty/libmicrohttpd/src/include
	$(CC) -shared -Wl,-soname,libcweb.so -o build/libcweb.so \
	    build/cweb_common.o build/cweb_router.o build/cweb_server.o

examples: lib
	mkdir -p build
	$(foreach program,server,\
	$(CC) -std=c11 -fblocks examples/$(program).c -o build/$(program) -I./include -L./build -lcweb \
	    `pkg-config --cflags --libs apr-1` \
	    `pkg-config --cflags --libs r3` \
	    `pkg-config --cflags --libs libmicrohttpd` \
	    `pkg-config --cflags --libs jansson` \
	    -lBlocksRuntime &&) echo "finished building examples"

install: lib
	cp -R include/* /usr/local/include
	cp build/libcweb* /usr/local/lib

3rdparty:
	# apr
	cd 3rdparty/apr && ./configure && make && sudo make install && make clean
	# r3
	cd 3rdparty/r3 && ./autogen.sh && ./configure && make && sudo make install && make clean
	# libmicrohttpd
	cd 3rdparty/libmicrohttpd && ./configure && make && sudo make install && make clean
	# jansson
	cd 3rdparty/jansson && ./configure && make && sudo make install && make clean
	
clean:
	rm -rf build

.PHONY: default main lib examples install clean 3rdparty

