test_fileiotime : fileiotime_test.c
	gcc -O -o test_fileiotime fileiotime_test.c -L/mnt/hgfs/LinuxC/comlib -lfileiotime -I/mnt/hgfs/LinuxC/comlib
