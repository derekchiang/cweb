#include <stdio.h>
#include "cweb_router.h"

#define debug(str, args...) fprintf(stderr, str "\n", ## args)
#define print(str, args...) fprintf(stdout, str "\n", ## args)

int main(void) {
    cweb_router_t *router = cweb_router_new();

    __block int sum = 0;
    cweb_router_add_route(router, "/hello", ^(void *data) {
        // normally you shouldn't be casting between int and void *... this is just an example
        sum += (int) data;  
    });

    cweb_router_compile(router);

    cweb_router_dispatch(router, "/hello", 100);
    cweb_router_dispatch(router, "/hello", 200);
    cweb_router_dispatch(router, "/hello", 300);

    printf("sum is: %d\n", sum);  // should be 600

    cweb_router_destroy(router);
    return 0;
}

