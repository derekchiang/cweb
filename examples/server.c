#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cweb.h"

int main(void) {
    cweb_initialize();
    cweb_router_t *router = cweb_router_new();

    cweb_router_add_route(router, "/hello/{name}", ^(cweb_request_t *req, cweb_response_t *res) {
        char *buf = malloc(256);
        res->body_len = sprintf(buf, "Hello, %s", cweb_request_param(req, "name"));
        res->body = buf;
        res->mem_strat = CWEB_MEM_FREE;
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

