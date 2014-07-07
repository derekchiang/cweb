#pragma once

#include <microhttpd.h>

#pragma mark =============== REQUEST ===============

typedef struct cweb_request {
    const char *url;
    const char *method;
    const char *version;
    const char *upload_data;
    size_t *upload_data_size;

    // private; do not touch
    char **params;
    struct MHD_Connection *_connection;
} cweb_request_t;

static inline const char *cweb_request_query_string(cweb_request_t *self, const char *name) {
    return MHD_lookup_connection_value(self->_connection, MHD_GET_ARGUMENT_KIND, name);
}

#pragma mark =============== RESPONSE ===============

typedef enum { CWEB_MEM_COPY, CWEB_MEM_FREE, CWEB_MEM_PERSISTENT } cweb_mem_strategy_e;

typedef struct cweb_response {
    unsigned int status;
    const char *body;
    size_t body_len;
    cweb_mem_strategy_e mem_strat;  // function to be called after response is sent
} cweb_response_t;

