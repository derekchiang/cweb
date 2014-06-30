# cweb

`cweb` is a set of utilities to facilitate web development in C.

This is very much a work in progress.  [Here is a sneak peak](examples/server.c).


`cweb` makes heavy use of the [blocks extension](http://en.wikipedia.org/wiki/Blocks_%28C_language_extension%29#Relation_to_GCC_nested_functions).  What this means is that you will need to use [clang](http://clang.llvm.org/) to compile any project that uses `cweb`.

## Dependencies

1. [Apache Portable Runtime](https://apr.apache.org/)
2. [r3](https://github.com/c9s/r3)
3. [libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/)
4. clang with blocks extension

On Ubuntu, the blocks extension can be installed via `sudo apt-get install libblocksruntime-dev`

## Build

`make 3rdparty` will build and install all third-party libraries that `cweb` depends on.

`make` will build `cweb` in the `build/` folder.

`make install` will install `cweb` in your system.

`make examples` will build the examples under `examples/` to `build/`.  You can then manually run the examples.

## API

TODO.  For now, please refer to `include/` and `examples/`.

