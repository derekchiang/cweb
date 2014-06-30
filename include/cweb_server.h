#pragma once

#include "cweb.h"

#pragma mark =============== SERVER CONFIG ===============

typedef struct cweb_server_config {
    unsigned int port;
    cweb_router_t *router;
} cweb_server_config_t;

#pragma mark =============== SERVER ===============

typedef struct cweb_server cweb_server_t;

extern cweb_server_t cweb_server_new(cweb_server_config_t config);

extern void cweb_server_run(cweb_server_t);

