libfileio.a : fileio.o
	ar -rsv libfileio.a fileio.o
fileio.o : comlib.h fileio.c
	gcc -O -c -o fileio.o fileio.c
