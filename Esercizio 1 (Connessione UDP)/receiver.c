

/* udp receiver */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define RECV_PORT 7550

main(){
	int sockfd;
	struct sockaddr_in recv_addr,send_addr;
	socklen_t lengSend=sizeof(send_addr),lengReciv=sizeof(recv_addr);
	char line[100];
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
		printf("\nErrore nell'apertura della socket");
		return -1;
	}
	memset((char *)&recv_addr,0,lengReciv);
	recv_addr.sin_family=AF_INET;
	recv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	recv_addr.sin_port=htons(RECV_PORT);
	
	printf("\nSono in ascolto!\n");
	
	if(bind(sockfd,(struct sockaddr *)&recv_addr,lengSend)<0){
		printf("\nErrore nel binding. Errore %d \n");
		return -1;
	}
	while(1){	
		printf("%s\n");
	recvfrom(sockfd,line,101,0,(struct sockaddr *)&send_addr,&lengSend);
		printf("%s");	
}
}
