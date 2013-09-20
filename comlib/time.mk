libtime.a : time.o
	ar -rsv libtime.a  time.o
time.o : time.c
	gcc -O -c -o time.o time.c
