#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define SERV_TCP_PORT 6550

str_echo(int sockfd, int sockfd2) {
  int n;
  const int MAX = 1025;
  char line[1025];
  for (;;) {
    bzero(line, 0);
    if (!(n = read(sockfd, line, MAX))) {
      printf("\nOut from str_echo");
      return;
    }
    if (n < 0) {
      printf("\nError in str_echo");
      return;
    }

    if (write(sockfd2, line, n) != n) {
      printf("\nError in write");
      return;
    }
  }
}

int main() {
  int sockfd, newsockfd, newsockfd2, father, clilen;
  struct sockaddr_in cli_addr, serv_addr;
  extern int errno;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n[ERROR]: while opening socket");
    return -1;
  }
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(SERV_TCP_PORT);
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\n[ERROR]: in the binding. Errore %d \n", errno);
    return -1;
  }
  listen(sockfd, 5);

  for (;;) {
    clilen = sizeof(cli_addr);
    if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0) {
      printf("\n[ERROR]: In the accept phase from client 1");
      return -1;
    }
    if ((newsockfd2 = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0) {
      printf("\n[ERROR]: In the ccept phase from client 2");
    }
    if ((father = fork()) < 0) {
      printf("\n[ERROR]: In Fork");
    } else if (!father) {
      close(sockfd);
      str_echo(newsockfd, newsockfd2);
      exit(0);
    }
    close(newsockfd);
    close(newsockfd2);
  }
}
