# cweb

`cweb` is a set of utilities to facilitate web development in C.

This is very much a work in progress.  [Here is a sneak peak](examples/server.c).

## Dependencies

1. [Apache Portable Runtime](https://apr.apache.org/)
2. [r3](https://github.com/c9s/r3)
3. [libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/)
4. [clang](http://clang.llvm.org/) with [blocks extension](http://en.wikipedia.org/wiki/Blocks_%28C_language_extension%29)

On Ubuntu, clang and the blocks extension can be installed with:

    sudo apt-get install clang libblocksruntime-dev

## Build

On Ubuntu:

    make
    sudo make install

The examples will be put under `build/bin/`.

## Benchmark

You can benchmark the server with `ab`, the Apache HTTP server benchmarking tool.  Make sure a server (`examples/server.c` will do) is running on port 8000, then:

    ab -n 10000 -c 1000 http://127.0.0.1:8000/

On my laptop, it's able to handle roughly 37K requests per second. 

## API

TODO.  For now, please refer to `include/` and `examples/`.

