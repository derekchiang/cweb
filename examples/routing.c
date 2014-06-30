#include <stdio.h>
#include <assert.h>

#include "cweb_common.h"
#include "cweb_router.h"

#define debug(str, args...) fprintf(stderr, str "\n", ## args)
#define print(str, args...) fprintf(stdout, str "\n", ## args)

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
    
    // Of course, we can capture dynamic variables
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

