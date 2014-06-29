#include <stdlib.h>

#include <Block.h>

#include <apr_general.h>
#include <apr_pools.h>
#include <apr_tables.h>

#include <r3/r3.h>

#include "cweb_common.h"
#include "cweb_router.h"

struct cweb_router {
    node *tree;
    apr_pool_t *pool;
};

cweb_router_t *cweb_router_new(void) {
    if (!cweb_initialized) cweb_initialize();

    apr_pool_t *pool;
    apr_pool_create(&pool, cweb_global_pool);

    cweb_router_t *self = apr_palloc(pool, sizeof(cweb_router_t));   
    self->tree = r3_tree_create(10);
    self->pool = pool;
    return self;
}

void cweb_router_destroy(cweb_router_t *self) {
    r3_tree_free(self->tree);
    apr_pool_destroy(self->pool);
}

void cweb_router_add_route(cweb_router_t *self, const char *route, data_handler_b handler){
    node *matched_node = r3_tree_match(self->tree, route, NULL);
    apr_array_header_t *handlers;
    if (matched_node) {
        handlers = (apr_array_header_t *) matched_node->data;
    } else {
        handlers = apr_array_make(self->pool, 1, sizeof(data_handler_b));
    }
    APR_ARRAY_PUSH(handlers, data_handler_b) = Block_copy(handler);
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

extern bool cweb_router_dispatch(cweb_router_t *self, const char *route, void *data) {
    match_entry *entry = match_entry_create(route);
    node *matched_node = r3_tree_match_entry(self->tree, entry);
    if (matched_node) {
        apr_array_header_t *handlers = matched_node->data;
        for (nat i = 0; i < handlers->nelts; i++) {
            data_handler_b handler = APR_ARRAY_IDX(handlers, i, data_handler_b);
            handler(entry->vars->tokens, entry->vars->len, data);
        }
        return true;
    }
    return false;
}

