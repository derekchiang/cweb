#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Block.h>

#include <custache.h>

#include "cweb.h"

int main(void) {
    // Initialize cweb
    cweb_initialize();

    // Compile template
    const char *err = NULL;
    const char *tpl_str = "{{#decorate}}Hello, my name is {{name}}.{{#age}}  My age is {{age}}.{{/age}}{{/decorate}}";  // mustache
    custache_t cus = custache_compile(tpl_str, &err);
    if (err) {
        puts(err);
        exit(1);
    }

    // Set up routes
    cweb_router_t *router = cweb_router_new();
    cweb_router_add_route(router, "/{name}", ^(cweb_request_t *req, cweb_response_t *res) {
        const char *err = NULL;
        char *body = custache_render(cus, ^(const char *tag_name) {
            mustache_tag_t tag;
            if (!strcmp(tag_name, "decorate")) {
                tag.type = MUSTACHE_TYPE_DECORATOR;
                tag.as_decorator = Block_copy(^(const char *text, mustache_render_b render) {
                    char *buf = malloc(1024);
                    sprintf(buf, "~~~~~~~~\n%s\n~~~~~~~~", render(text));
                    return buf;
                });
            } else if (!strcmp(tag_name, "name")) {
                tag.type = MUSTACHE_TYPE_STRING;
                tag.as_string = req->params[0];
            } else if (!strcmp(tag_name, "age")) {
                tag.type = MUSTACHE_TYPE_STRING;
                tag.as_string = cweb_request_query_string(req, "age");
            }
            return tag;
        }, &err);
        if (err) {
            puts(err);
            exit(1);
        }
        res->body = body;
        res->body_len = strlen(body);
        res->mem_strat = CWEB_MEM_FREE;
    });

    // Compile routes for fast matching
    cweb_router_compile(router);

    // Start running server
    cweb_server_config_t config = {
        .port = 8000,
        .router = router
    };
    cweb_server_t *server = cweb_server_run(config);
    puts("server is running at: http://localhost:8000");
    puts("try visit: http://localhost:8000/derek?age=20");
    (void) getc(stdin);  // enter anything on console to stop the server

    // Finalize things
    cweb_server_stop(server);
    cweb_router_destroy(router);
    custache_release(cus);
    cweb_finalize();
    return 0;
}

