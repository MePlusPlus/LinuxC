libdebug.a : debug.o comlib.h
	ar -rsv libdebug.a debug.o
debug.o : debug.c comlib.h
	gcc -O -c -o debug.o debug.c
