#pragma once

#include <limits.h>
#include <linux/limits.h>
#include <stdbool.h>

#include <apr_pools.h>

typedef unsigned long long nat;

#pragma mark =============== GLOBAL DATA STRUCTURES =============== 

// Track if cweb_initialize() has been called
extern bool cweb_initialized;

// The root memory pool.  All other memory pools should be the subpools of this one.
extern apr_pool_t *cweb_global_pool;

extern void cweb_initialize(void);
extern void cweb_finalize(void);

