#include <stdlib.h>
#include <stdio.h>

#include <cweb_common.h>

bool cweb_initialized = false;
apr_pool_t *cweb_global_pool = NULL;

static inline void check_apr_status(apr_status_t status) {
    if (status != APR_SUCCESS) {
        char buf[256];
        apr_strerror(status, buf, sizeof(buf));
        puts(buf);
        exit(EXIT_FAILURE);
    }
}

void cweb_initialize(void) {
    if (cweb_initialized) return;
    apr_initialize();
    apr_status_t status = apr_pool_create(&cweb_global_pool, NULL);
    check_apr_status(status);
    cweb_initialized = true;
}

void cweb_finalize(void) {
    if (!cweb_initialized) return;
    apr_pool_destroy(cweb_global_pool);
    apr_terminate();
    cweb_initialized = false;
}

