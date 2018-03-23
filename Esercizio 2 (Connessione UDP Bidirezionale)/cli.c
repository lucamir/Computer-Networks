/*** Client UDP ***/ 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define PORT 7550

int setTimeout(int _sockfd,int s,int ms){
	struct timeval tv;
	tv.tv_sec=s;
	tv.tv_usec=ms;
	return setsockopt(_sockfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
}

int main(int argc, char**argv) {
	int sockfd,n=0,c=1;
	struct sockaddr_in servaddr,cliaddr; 
	char send[50],recv[1];
	socklen_t servAdd=sizeof(servaddr);
	FILE* pf=fopen("udp.txt","r");
	
	if(argc!=2) return 1; 
	else printf ("\n %s\n",argv[1]);
	
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
		printf("Errore nell'apertura della socket\n");
		return -1;
	}

	memset(send,'\0',sizeof(send));
	memset(&servaddr,0,servAdd); 
	servaddr.sin_family=AF_INET; 
	servaddr.sin_addr.s_addr=inet_addr(argv[1]); 
	servaddr.sin_port=htons(PORT);
	
	setTimeout(sockfd,2,2);

	fread(send,1,48,pf);
	while(1){
		printf("Invio %d paccheto\n",c);
		sendto(sockfd,send,strlen(send),0,(struct sockaddr *)&servaddr,servAdd);
		if(recvfrom(sockfd,recv,1,0,NULL,NULL)>=0){
			c++;
			memset(send,'\0',sizeof(send));
			if(!(fread(send,1,48,pf))){
				strcpy(send,"./end/.");
				sendto(sockfd,send,strlen(send),0,(struct sockaddr *)&servaddr,servAdd);
				if(recvfrom(sockfd,recv,1,0,NULL,NULL)>=0){ 
					printf("\nComunication Closed\n"); 
					fclose(pf);
					break; 
				}		 
			}
		}
	}	
}
