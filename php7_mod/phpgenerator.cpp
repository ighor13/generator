#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "../engine/generator.h"

#define PHP_GENERATOR_VERSION "1.0"
#define PHP_GENERATOR_EXTNAME "generator"

extern zend_module_entry generator_module_entry;
#define phpext_generator_ptr &generator_module_entry
 
PHP_FUNCTION(generate);

ZEND_BEGIN_ARG_INFO(arginfo_generator_generate, 0)
        ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
 
static zend_function_entry generator_functions[] = {
    PHP_FE(generate, arginfo_generator_generate)
    {NULL, NULL, NULL}
};

zend_module_entry generator_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_GENERATOR_EXTNAME,
    generator_functions,
    NULL, // name of the MINIT function or NULL if not applicable
    NULL, // name of the MSHUTDOWN function or NULL if not applicable
    NULL, // name of the RINIT function or NULL if not applicable
    NULL, // name of the RSHUTDOWN function or NULL if not applicable
    NULL, // name of the MINFO function or NULL if not applicable
    PHP_GENERATOR_VERSION,
    STANDARD_MODULE_PROPERTIES
};
 
ZEND_GET_MODULE(generator)
 
// implementation of a custom generate()
PHP_FUNCTION(generate)
{
        char *var = (char*)"";
        size_t var_len = sizeof("") - 1;

        ZEND_PARSE_PARAMETERS_START(0, 1)
                Z_PARAM_OPTIONAL
                Z_PARAM_STRING(var, var_len)
        ZEND_PARSE_PARAMETERS_END();

//        zend_string *got;
//        got = strpprintf(0, "%s", var);

    array_init(return_value);

    int key = 0;
    try
    {
        Result r=generate(var);
        for(Result::iterator i=r.begin();i!=r.end();i++)
        {
	    zval element;
	    ZVAL_STRING(&element, (char*)(*i).c_str());
	    add_index_zval(return_value, key++, &element);
        }
    }
    catch (const char* err)
    {
    	RETURN_STRING(err);
    }
//      RETURN_STR(got);
}
