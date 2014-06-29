# cweb

`cweb` is a set of utilities to facilitate web development in C.

This is very much a work in progress.  Currently I have only built a router.  Here is a sneak peak:

```c
#include <stdio.h>
#include <assert.h>

#include "cweb_common.h"
#include "cweb_router.h"

int main(void) {
    cweb_initialize();
    cweb_router_t *router = cweb_router_new();

    __block int sum = 0;
    cweb_router_add_route(router, "/sum", ^(const char **vars, int vars_len, void *data) {
        // normally you shouldn't be casting between int and void *... this is just an example
        sum += (int) data;  
    });
    
    // Multiple handlers for the same route is OK.  Handles are called in the order they were added
    cweb_router_add_route(router, "/sum", ^(const char **vars, int vars_len, void *data) {
        printf("sum is: %d\n", sum);
    });

    cweb_router_add_route(router, "/hello/{name}", ^(const char **vars, int vars_len, void *data) {
        assert(vars_len > 0);
        const char *name = vars[0];
        printf("Hello, %s\n", name);
    });

    cweb_router_compile(router);

    cweb_router_dispatch(router, "/sum", 100);
    cweb_router_dispatch(router, "/sum", 200);
    cweb_router_dispatch(router, "/sum", 300);

    cweb_router_dispatch(router, "/hello/derek", NULL);

    cweb_router_destroy(router);
    cweb_finalize();
    return 0;
}
```

`cweb` makes heavy use of the [blocks extension](http://en.wikipedia.org/wiki/Blocks_%28C_language_extension%29#Relation_to_GCC_nested_functions).  What this means is that you will need to use [clang](http://clang.llvm.org/) to compile any project that uses `cweb`.

## Dependencies

1. [Apache Portable Runtime](https://apr.apache.org/)
2. [r3](https://github.com/c9s/r3)
3. [libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/)
4. clang with blocks extension

On Ubuntu, the blocks extension can be installed via `sudo apt-get install libblocksruntime-dev`

## Build

`make 3rdparty` will build and install all third-party libraries that `cweb` depends on.

`make` will build `cweb` in the `build` folder.

`make install` will install `cweb` in your system.

`make run` will build and run `main.c`, which is an example using `cweb`.

## API

TODO.  For now, please refer to `include/` and `main.c`.

