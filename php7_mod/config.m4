PHP_ARG_ENABLE(phpgenerator, whether to enable PHP Generator Extension support,
    [ --enable-phpgenerator    Enable My Extension support])
if test "$PHP_PHPGENERATOR" = "yes"; then
    PHP_REQUIRE_CXX()
    AC_DEFINE(HAVE_PHPGENERATOR, 1, [Whether you have PHP Generator Extension])
    PHP_NEW_EXTENSION(phpgenerator, phpgenerator.cpp ../engine/generator.cpp, $ext_shared,,"-O2 -Wall -Werror","-L/usr/local/lib -Wl,--rpath -Wl,/usr/local/lib")
fi