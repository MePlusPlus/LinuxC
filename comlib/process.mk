libproc.a : process.o comlib.h
	ar -rsv libproc.a debug.o
process.o : process.c comlib.h
	gcc -O -c -o process.o process.c -I/mnt/hgfs/LinuxC/comlib
