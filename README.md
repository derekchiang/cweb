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

The other dependencies come with this repo and therefore do not need to be installed manually.  See the build instructions below. 

## Build

On Ubuntu:

    make 3rdparty # optional... only if you don't have the dependencies installed already
    make
    sudo make install

To build the examples:

    make examples

The examples will be put under `build/`.

## API

TODO.  For now, please refer to `include/` and `examples/`.

