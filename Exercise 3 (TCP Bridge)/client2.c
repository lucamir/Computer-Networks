#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define SERV_TCP_PORT 6550
#define SERV_ADDR "192.168.1.12"

str_cli_rec(int sockfd) {
  int n;
  const int MAX = 1025;
  char recvline[1026];
  while (1) {
    if ((n = read(sockfd, recvline, MAX)) < 0) {
      printf("\n[ERROR]");
      return -1;
    }
    recvline[n] = 0;
    fputs(recvline, stdout);
  }
}

int main() {
  int sockfd;
  struct sockaddr_in serv_addr;
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(SERV_ADDR);
  serv_addr.sin_port = htons(SERV_TCP_PORT);
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n[ERROR]: while opening socket");
    return -1;
  }
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\n[ERROR]: in the connect");
    return -1;
  }
  str_cli_rec(sockfd);
  close(sockfd);
  exit(0);
}
