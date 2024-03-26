#include "php.h"
#include "../engine/generator.h"

ZEND_FUNCTION(generate);

zend_function_entry generator_functions[] =
{
    ZEND_FE(generate, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry generator_module_entry =
{
    STANDARD_MODULE_HEADER,
    "Generator Module",
    generator_functions,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL,
    NO_VERSION_YET,
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(generator)

ZEND_FUNCTION(generate)
{
    char* s;
    int s_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &s, &s_len) == FAILURE) {
        return;
    }


    array_init(return_value);

    int key = 1;
    try
    {
        Result r=generate(s);
        for(Result::iterator i=r.begin();i!=r.end();i++)
	{
	    zval *element;
	    MAKE_STD_ZVAL(element);
	    ZVAL_STRING(element, (char*)(*i).c_str(), 1);
	    if(zend_hash_index_update(return_value->value.ht, key++, (void *)&element, sizeof(zval *), NULL) == FAILURE)
		; // no error handling here
	}
    }
    catch (const char* err)
    {
        err;
    }
									    

}
