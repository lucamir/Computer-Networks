/*** Server UDP ***/
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#define PORT 7550
main() {
  int sockfd;
  struct sockaddr_in servaddr, cliaddr;
  char mesg[50], ack[1] = {'1'};
  FILE *fp = fopen("new.txt", "w+");
  socklen_t len = sizeof(cliaddr), servAdd = sizeof(servaddr);
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&servaddr, 0, servAdd);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);
  bind(sockfd, (struct sockaddr *)&servaddr, servAdd);

  printf("Listening!!\n");

  while (1) {
    memset(mesg, '\0', sizeof(mesg));
    recvfrom(sockfd, mesg, 50, 0, (struct sockaddr *)&cliaddr, &len);
    sendto(sockfd, ack, 1, 0, (struct sockaddr *)&cliaddr, len);
    if (strcmp("./end/.", mesg) == 0) {
      fclose(fp);
      break;
    } else {
      fputs(mesg, fp);
      printf("------------------------------------------------\n");
      printf("Received the following:\n");
      printf("%s", mesg);
      printf("------------------------------------------------\n");
    }
  }
}
