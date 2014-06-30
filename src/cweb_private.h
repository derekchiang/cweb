#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <apr_pools.h>

#pragma mark =============== GLOBAL DATA STRUCTURES =============== 

// Track if cweb_initialize() has been called
extern bool cweb_initialized;

// The root memory pool.  All other memory pools should be the subpools of this one.
extern apr_pool_t *cweb_global_pool;

#pragma mark =============== CONVENIENCE DATA TYPES / UTILITIES =============== 

typedef unsigned long long nat;

#define logerr(str, args...) fprintf(stderr, str "\n", ## args)
#define log(str, args...) fprintf(stdout, str "\n", ## args)

static inline void check_apr_status(apr_status_t status) {
    if (status != APR_SUCCESS) {
        char buf[256];
        apr_strerror(status, buf, sizeof(buf));
        puts(buf);
        exit(EXIT_FAILURE);
    }
}

static inline apr_pool_t *create_subpool(apr_pool_t *parent) {
    apr_pool_t *pool;
    apr_status_t status = apr_pool_create(&pool, parent);
    check_apr_status(status);
    return pool;
}

