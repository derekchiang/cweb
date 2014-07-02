CC = clang
VERSION = 1.0.0

SOURCES := $(realpath $(wildcard src/*.c))
OBJECTS := $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))
SHARED_LIBS := apr-1 r3 libmicrohttpd jansson

default: lib

lib: $(SOURCES)
	mkdir -p build
	cd build && \
	    $(CC) -fblocks -c -fPIC $(SOURCES) \
	    -I../include \
	    -I../3rdparty/apr/include \
	    -I../3rdparty/r3/include \
	    -I../3rdparty/libmicrohttpd/src/include
	$(CC) -shared -Wl,-soname,libcweb.so -o build/libcweb.so $(OBJECTS)

examples: lib
	mkdir -p build
	$(foreach program,server,\
	$(CC) -std=c11 -fblocks examples/$(program).c -o build/$(program) -I./include -L./build -lcweb \
	    $(foreach lib,$(SHARED_LIBS),`pkg-config --cflags --libs $(lib)`) \
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

