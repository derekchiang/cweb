#include <stdlib.h>

#include <Block.h>

#include <apr_general.h>
#include <apr_pools.h>
#include <apr_tables.h>

#include <r3/r3.h>

#include "cweb_common.h"
#include "cweb_private.h"
#include "cweb_router.h"

struct cweb_router {
    node *tree;
    req_handler_b not_found_handler;
    apr_pool_t *pool;
};

cweb_router_t *cweb_router_new(void) {
    if (!cweb_initialized) cweb_initialize();

    apr_pool_t *pool = create_subpool(cweb_global_pool);

    cweb_router_t *self = apr_palloc(pool, sizeof(cweb_router_t));   
    self->tree = r3_tree_create(10);
    self->not_found_handler = NULL;
    self->pool = pool;
    return self;
}

void cweb_router_set_not_found_handler(cweb_router_t *self, req_handler_b handler) {
    self->not_found_handler = Block_copy(handler);
}

void cweb_router_destroy(cweb_router_t *self) {
    r3_tree_free(self->tree);
    if (self->not_found_handler) Block_release(self->not_found_handler);
    apr_pool_destroy(self->pool);
    // TODO: you need to Block_release all the handlers as well
}

void cweb_router_add_route(cweb_router_t *self, const char *route, req_handler_b handler){
    node *matched_node = r3_tree_match(self->tree, route, NULL);
    apr_array_header_t *handlers;
    if (matched_node) {
        handlers = (apr_array_header_t *) matched_node->data;
    } else {
        handlers = apr_array_make(self->pool, 1, sizeof(req_handler_b));
    }
    APR_ARRAY_PUSH(handlers, req_handler_b) = Block_copy(handler);
    r3_tree_insert_path(self->tree, route, handlers);
}

extern void cweb_router_compile(cweb_router_t *self) {
    char *errstr;
    int err = r3_tree_compile(self->tree, &errstr);
    if (err != 0) {
        printf("error: %s\n", errstr);
        free(errstr);
        exit(EXIT_FAILURE);
    }
}

extern bool cweb_router_dispatch(cweb_router_t *self, const char *route,
                                 cweb_request_t *req, cweb_response_t *res) {
    match_entry *entry = match_entry_create(route);
    node *matched_node = r3_tree_match_entry(self->tree, entry);
    if (matched_node) {
        req->params = entry->vars->tokens;
        apr_array_header_t *handlers = matched_node->data;
        for (nat i = 0; i < handlers->nelts; i++) {
            req_handler_b handler = APR_ARRAY_IDX(handlers, i, req_handler_b);
            handler(req, res);
        }
        return true;
    } else if (self->not_found_handler) {
        self->not_found_handler(req, res);
        return true;
    } else {
        return false;
    }
}

