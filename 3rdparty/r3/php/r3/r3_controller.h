#ifndef PHP_CONTROLLER_H
#define PHP_CONTROLLER_H 1

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

extern zend_class_entry *ce_r3_controller;

void r3_init_controller(TSRMLS_D);

char * translate_method_name_to_path(const char *method_name);
zend_bool phannot_fetch_argument_value(zval **arg, zval** value TSRMLS_DC);
zend_bool phannot_fetch_argument_type(zval **arg, zval **type TSRMLS_DC);
int strpos(const char *haystack, char *needle);

PHP_METHOD(Controller, __construct);
PHP_METHOD(Controller, expand);
PHP_METHOD(Controller, getActionMethods);
PHP_METHOD(Controller, getActionRoutes);
PHP_METHOD(Controller, before);
PHP_METHOD(Controller, after);
PHP_METHOD(Controller, toJson);


#endif
