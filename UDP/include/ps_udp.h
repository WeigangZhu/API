#ifndef PS_UDP_H_
#define PS_UDP_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PACKET_SIZE 	1248
#define PS_PORT 		9966
#define PS_BUFFER_SIZE	4096
int 	ps_open_net();
void 	ps_err_recvfrom(int );
void	ps_receive_test();

#endif
