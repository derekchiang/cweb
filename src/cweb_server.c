#include <microhttpd.h>

#include "cweb_server.h"
#include "cweb_private.h"

struct cweb_server {
    cweb_server_config_t config;
    apr_pool_t *pool;
}

cweb_server_t cweb_server_new(cweb_server_config_t config) {
    apr_pool_t *pool = create_subpool();
    
    cweb_server_t *self = apr_palloc(pool, sizeof(cweb_server_t));
    self->config = config;
    self->pool = pool;
    return self;
}

void cweb_server_destroy(cweb_server_t *self) {
    apr_pool_destroy(self->pool);
}

void cweb_server_run(cweb_server_t *self) {
    struct MHD_Daemon *daemon;
}

