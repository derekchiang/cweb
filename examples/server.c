#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cweb.h"

int main(void) {
    cweb_initialize();
    cweb_router_t *router = cweb_router_new();

    cweb_router_add_route(router, "/", ^(cweb_request_t *req, cweb_response_t *res) {
        const char *body = "Hello, World!";
        res->body_len = strlen(body);
        res->body = body;
        res->mem_strat = CWEB_MEM_PERSISTENT;
    });

    cweb_router_add_route(router, "/{name}", ^(cweb_request_t *req, cweb_response_t *res) {
        char *buf = malloc(256);
        res->body_len = sprintf(buf, "Hello, %s!  You are %s years old.",
                                req->params[0], cweb_request_query_string(req, "age"));
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
    puts("try visit: http://localhost:8000/derek?age=20");
    (void) getc(stdin);

    cweb_server_stop(server);
    cweb_router_destroy(router);
    cweb_finalize();
    return 0;
}

