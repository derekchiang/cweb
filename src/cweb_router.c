#include <stdlib.h>

#include <Block.h>
#include <apr_pools.h>
#include <r3/r3.h>

#include "cweb_common.h"
#include "cweb_router.h"

struct cweb_router {
    node *tree;
    data_handler_b *handlers;
    nat num_handlers;
};

cweb_router_t *cweb_router_new(void) {
    cweb_router_t *self = malloc(sizeof(cweb_router_t));   
    self->tree = r3_tree_create(10);
    self->handlers = NULL;
    self->num_handlers = 0;
    return self;
}

void cweb_router_destroy(cweb_router_t *self) {
    r3_tree_free(self->tree);
    for (nat i = 0; i < self->num_handlers; i++) {
        Block_release(self->handlers[i]);
    }
    free(self->handlers);
    free(self);
}

void cweb_router_add_route(cweb_router_t *self, const char *route, data_handler_b handler){
    self->num_handlers++;
    self->handlers = realloc(self->handlers, self->num_handlers * sizeof(data_handler_b));
    self->handlers[self->num_handlers - 1] = Block_copy(handler);
    r3_tree_insert_path(self->tree, route, &self->handlers[self->num_handlers - 1]);
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
    node *matched_node = r3_tree_match(self->tree, route, NULL);
    if (matched_node) {
        data_handler_b handler = *((data_handler_b *)matched_node->data);
        handler(data);
        return true;
    }
    return false;
}

