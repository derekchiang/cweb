#include <microhttpd.h>

#include "cweb_server.h"
#include "cweb_http.h"
#include "cweb_private.h"

struct cweb_server {
    cweb_server_config_t config;
    apr_pool_t *pool;
    struct MHD_Daemon *daemon;
};

static int root_handler(void *user_data, struct MHD_Connection *connection,
                        const char *url, const char *method, const char *version,
                        const char *upload_data, size_t *upload_data_size, void **ptr) {
    cweb_server_t *server = user_data;
    cweb_router_t *router = server->config.router;
    
    cweb_request_t req = {
        .url = url, .method = method, .version = version,
        .upload_data = upload_data, .upload_data_size = upload_data_size,
        .params = NULL, ._connection = connection
    };
    cweb_response_t res = {};
    res.mem_strat = CWEB_MEM_COPY;
    cweb_router_dispatch(router, url, &req, &res);

    enum MHD_ResponseMemoryMode mode;
    switch (res.mem_strat) {
    case CWEB_MEM_COPY:
        mode = MHD_RESPMEM_MUST_COPY; break;
    case CWEB_MEM_FREE:
        mode = MHD_RESPMEM_MUST_FREE; break;
    case CWEB_MEM_PERSISTENT:
        mode = MHD_RESPMEM_PERSISTENT; break;
    }
    MHD_queue_response(connection, res.status,
                       MHD_create_response_from_buffer(res.body_len, (void *) res.body, mode));
    return MHD_YES;
}

cweb_server_t *cweb_server_run(cweb_server_config_t config) {
    apr_pool_t *pool = create_subpool(cweb_global_pool);
    
    cweb_server_t *self = apr_palloc(pool, sizeof(cweb_server_t));
    self->config = config;
    self->pool = pool;
    self->daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                                    self->config.port,
                                    NULL, NULL, &root_handler, self,
                                    MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 120,
                                    MHD_OPTION_END);
    return self;
}

void cweb_server_stop(cweb_server_t *self) {
    MHD_stop_daemon(self->daemon);
    apr_pool_destroy(self->pool);
}

