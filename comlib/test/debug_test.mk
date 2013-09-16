test_debug : debug_test.c 
	gcc -O -o test_debug debug_test.c -L/mnt/hgfs/LinuxC/comlib  -ldebug -I/mnt/hgfs/LinuxC/comlib
