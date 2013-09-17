test_fileio : fileio_test.c
	gcc -O -o test_fileio fileio_test.c -L/mnt/hgfs/LinuxC/comlib -lfileio -I/mnt/hgfs/LinuxC/comlib
