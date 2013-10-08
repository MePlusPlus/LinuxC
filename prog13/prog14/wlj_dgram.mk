dgrecv:dgsend wlj_dgram.c wlj_dgram_recv.c
	gcc -o dgrecv wlj_dgram.c wlj_dgram_recv.c 
dgsend:wlj_dgram.c wlj_dgram_send.c
	gcc -o dgsend wlj_dgram.c wlj_dgram_send.c
