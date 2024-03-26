CC	= clang
CFLAGS  = -w -O2 -fpic -DCOMPILE_DL=1 -I/usr/local/include/php -I/usr/local/include/php/main -I/usr/local/include/php/TSRM -I/usr/local/include/php/Zend -I/usr/local/include/php/ext -I/usr/local/include -I../engine
LIBDIR  = -L/usr/local/lib -Wl,--rpath -Wl,/usr/local/lib -shared -rdynamic 
LIB     = 
TARGET	= generator.so

all:	phpmodule.o generator.o
	$(CC) $(LIBDIR) -o ${TARGET} phpmodule.o generator.o $(LIB)
phpmodule.o:		phpmodule.cpp ../engine/generator.h
	$(CC) $(CFLAGS) -c phpmodule.cpp
generator.o:	../engine/generator.cpp ../engine/generator.h
	$(CC) $(CFLAGS) -c ../engine/generator.cpp
clean:
	rm *.o $(TARGET)
