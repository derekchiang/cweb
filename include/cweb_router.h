#pragma once

#include <stdbool.h>

// Data handler
typedef void (^data_handler_b)(void *);

// Router
typedef struct cweb_router cweb_router_t;

// Create a new router
extern cweb_router_t *cweb_router_new(void);

// Destroy a router.  For every router created, a destory must be called.
extern void cweb_router_destroy(cweb_router_t *);

// Register a new route with a handler.
// It's OK to register multiple handlers with the same route.  In this case, the handlers will be called
// in the order they were registered.
extern void cweb_router_add_route(cweb_router_t *, const char *, data_handler_b);

// Compile the routes for faster matching.  This function does not necessarily need to be
// manually called; the library will make sure to call it once before start using the router.
// You should not add new routes after calling this function
extern void cweb_router_compile(cweb_router_t *);

// Dispatch a route with the given router.  The corresponding handler, if any, will then be called.
extern bool cweb_router_dispatch(cweb_router_t *, const char *route, void *data);

