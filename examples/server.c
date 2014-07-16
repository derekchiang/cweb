#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <apr_general.h>
#include <apr_pools.h>
#include <apr_file_io.h>
#include <apr_strings.h>
#include <apr_time.h>

#include <custache.h>

#include "cweb.h"

static char *read_file(const char *filename) {
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen ( filename , "rb" );
    if( !fp ) perror(filename), exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
        fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

    fclose(fp);
    return buffer;
}

static req_handler_b main_handler = ^(cweb_request_t *req, cweb_response_t *res) {
    apr_pool_t *pool;
    apr_pool_create(&pool, NULL);

    const char *err = NULL;
    const char *tpl_str = read_file("examples/hello_world.mustache");

    custache_t cus = custache_compile(tpl_str, &err);
    if (err) {
        puts(err);
        exit(1);
    }
    free((void*) tpl_str);

    char *body = custache_render(cus, ^(const char *tag_name) {
        mustache_tag_t tag;
        if (!strcmp(tag_name, "show_date")) {
            tag.type = MUSTACHE_TYPE_DECORATOR;
            tag.as_decorator = ^(const char *text, mustache_render_b render) {
                apr_time_t now = apr_time_now();
                char *buf = apr_palloc(pool, 256);
                apr_rfc822_date(buf, now);
                return apr_psprintf(pool, "%s\n%s", buf, render(text));
            };
        } else if (!strcmp(tag_name, "name")) {
            tag.type = MUSTACHE_TYPE_STRING;
            tag.as_string = "Derek";
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

    apr_pool_destroy(pool);
};

int main(void) {
    apr_initialize(); cweb_initialize();
    cweb_router_t *router = cweb_router_new();

    cweb_router_add_route(router, "/", main_handler);

    /*cweb_router_add_route(router, "/", ^(cweb_request_t *req, cweb_response_t *res) {*/
        /*const char *body = "Hello, World!";*/
        /*res->body_len = strlen(body);*/
        /*res->body = body;*/
        /*res->mem_strat = CWEB_MEM_PERSISTENT;*/
    /*});*/

    /*cweb_router_add_route(router, "/{name}", ^(cweb_request_t *req, cweb_response_t *res) {*/
        /*char *buf = malloc(256);*/
        /*res->body_len = sprintf(buf, "Hello, %s!  You are %s years old.",*/
                                /*req->params[0], cweb_request_query_string(req, "age"));*/
        /*res->body = buf;*/
        /*res->mem_strat = CWEB_MEM_FREE;*/
    /*});*/

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
    apr_terminate();
    return 0;
}

