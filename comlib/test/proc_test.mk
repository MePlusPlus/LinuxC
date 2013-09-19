test_fileio : process_test.c
	gcc -O -o test_process process_test.c -L/mnt/hgfs/LinuxC/comlib -lproc -I/mnt/hgfs/LinuxC/comlib
