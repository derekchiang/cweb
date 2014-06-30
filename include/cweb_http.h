#pragma once

#include <apr_tables.h>

#pragma mark =============== REQUEST ===============

typedef struct cweb_request {
    const char *url;
    const char *method;
    const char *version;
    const char *upload_data;
    size_t *upload_data_size;
    apr_table_t *_params; // private; use cweb_request_param to read it
} cweb_request_t;

static inline const char *cweb_request_param(cweb_request_t *self, const char *name) {
    return apr_table_get(self->_params, name);
}

#pragma mark =============== RESPONSE ===============

typedef enum { CWEB_MEM_COPY, CWEB_MEM_FREE, CWEB_MEM_PERSISTENT } cweb_mem_strategy_e;

typedef struct cweb_response {
    unsigned int status;
    const char *body;
    size_t body_len;
    cweb_mem_strategy_e mem_strat;  // function to be called after response is sent
} cweb_response_t;

