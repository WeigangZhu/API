#include"ps_udp.h"

int ps_open_net()
{
	int sockfd;
    struct sockaddr_in server;
    	

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("creating socket failed!");
		exit(1);
    }

    int opt = 1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&opt,sizeof(opt))) {
        perror("setsockopt error!");
        return -1;
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PS_PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		perror("bind error!");
		exit(1);
    }
    
	return sockfd;

}

void ps_err_recvfrom(int num)
{
	if (num < 0) {
		perror("recvfrom() error\n");
		exit(1);
	} else if (num != PACKET_SIZE) {
	printf("incomplete packet read: %d\n bytes", num );
	}
}


void ps_receive_test()
{
	unsigned int num = 0;
	char buf[PS_BUFFER_SIZE];
	struct sockaddr_in my_addr;
	socklen_t addrlen = sizeof(my_addr);
	
	int sockfd = ps_open_net();
	
	printf("Received packet from %s:%d\n", inet_ntoa(my_addr.sin_addr), ntohs(my_addr.sin_port)); 
	printf("sockfd = %d\n",sockfd);

	num =recvfrom(sockfd, buf, PACKET_SIZE, 0,
		     (struct sockaddr *) &my_addr, &addrlen);
	buf[num] = '\0';
	printf("%s\n\n",buf);
	
	close(sockfd);
}	
