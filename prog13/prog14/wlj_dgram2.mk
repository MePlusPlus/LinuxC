dgrecv2:dgsend2 wlj_dgram.c wlj_dgram_recv2.c
	gcc -o dgrecv2 wlj_dgram.c wlj_dgram_recv2.c 
dgsend2:wlj_dgram.c wlj_dgram_send2.c
	gcc -o dgsend2 wlj_dgram.c wlj_dgram_send2.c
