#include <stdio.h>
#include <assert.h>

#include "cweb.h"

int main(void) {
    cweb_initialize();
    cweb_router_t *router = cweb_router_new();

    cweb_router_add_route(router, "/hello/{name}", ^(const char **vars, int vars_len, void *data) {
        assert(vars_len > 0);
        const char *name = vars[0];
        printf("Hello, %s\n", name);
    });

    cweb_router_compile(router);

    cweb_server_config_t config = {
        .port = 8000,
        .router = router
    };

    cweb_server_t *server = cweb_server_run(config);
    puts("server is running at: http://localhost:8000");
    (void) getc(stdin);

    cweb_server_stop(server);
    cweb_router_destroy(router);
    cweb_finalize();
    return 0;
}

