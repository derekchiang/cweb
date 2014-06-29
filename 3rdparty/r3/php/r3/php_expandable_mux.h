#ifndef PHP_EXPANDABLE_MUX_H
#define PHP_EXPANDABLE_MUX_H 1

#include "php.h"
#include "string.h"
#include "main/php_main.h"
#include "Zend/zend_API.h"
#include "Zend/zend_variables.h"
#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "zend_object_handlers.h"
#include "ext/pcre/php_pcre.h"
#include "ext/standard/php_string.h"
#include "php_r3.h"
#include "r3_functions.h"

extern zend_class_entry *ce_r3_expandable_mux;

void r3_init_expandable_mux(TSRMLS_D);

#endif
