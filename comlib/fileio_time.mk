libfileiotime.a : fileiotime.o
	ar -rsv libfileiotime.a fileiotime.o
fileiotime.o : fileio_time.c
	gcc -O -c -o fileiotime.o fileio_time.c 
