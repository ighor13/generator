CC	= g++
CFLAGS  = -w -I/usr/local/include -I. -O2
LIBDIR  = -L/usr/local/lib -Wl,--rpath -Wl,/usr/local/lib
LIB     = 
TARGET	= generator

all:	main.o generator.o
	$(CC) $(LIBDIR) -o ${TARGET} main.o generator.o $(LIB)
main.o:		main.cpp ../engine/generator.h
	$(CC) $(CFLAGS) -c main.cpp
generator.o:	../engine/generator.cpp ../engine/generator.h
	$(CC) $(CFLAGS) -c ../engine/generator.cpp
clean:
	rm *.o $(TARGET)
