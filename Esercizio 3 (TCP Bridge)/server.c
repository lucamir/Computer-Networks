#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERV_TCP_PORT 6550

str_echo(int sockfd,int sockfd2){
	int n;
	const int MAX = 1025;
	char line[1025];
	for(;;){
		bzero(line,0);
		if(!(n=read(sockfd,line,MAX))){
			printf("\nUscita da str_echo");
			return;
		}
		if(n<0){
			printf("\nErrore in str_echo");
			return;
		}
		
		if(write(sockfd2,line,n)!=n){
			printf("\nErrore in write");
			return;
		}
	}
}

int main(){
	int sockfd, newsockfd, newsockfd2, father, clilen;
	struct sockaddr_in cli_addr, serv_addr;
	extern int errno;
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("\nErrore nell'apertura della socket");
		return -1;
	}
	bzero((char*) &serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_TCP_PORT);
	if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0){
		printf("\nErrore nel binding. Errore %d \n",errno);
		return -1;
	}
	listen(sockfd,5);

	for(;;){
		clilen=sizeof(cli_addr);
		if((newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr, &clilen))<0){
		printf("\nErrore in fase di accept client 1");
		return -1;			
}
		if((newsockfd2 = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen))<0){
			printf("\nErrore in fase di accept client 2");
}
		if((father=fork())<0){
			printf("\nErrore nella fork");
		}
		else if(!father){
			close(sockfd);
			str_echo(newsockfd,newsockfd2);
			exit(0);
		}
		close(newsockfd);
		close(newsockfd2);
	}
}
