#pragma once

#include <stdbool.h>
#include <stdio.h>

#include <apr_pools.h>

#pragma mark =============== CONVENIENCE DATA TYPES / UTILITIES =============== 

typedef unsigned long long nat;

#define debug(str, args...) fprintf(stderr, str "\n", ## args)
#define print(str, args...) fprintf(stdout, str "\n", ## args)

#pragma mark =============== GLOBAL DATA STRUCTURES =============== 

// Track if cweb_initialize() has been called
extern bool cweb_initialized;

// The root memory pool.  All other memory pools should be the subpools of this one.
extern apr_pool_t *cweb_global_pool;

