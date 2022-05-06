#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define RECV_PORT 7550
#define RECV_IP "192.168.1.11"
main() {
  int sockfd;
  struct sockaddr_in recv_addr;
  socklen_t lengReciv = sizeof(recv_addr);
  char line[100];
  int i, n;
  time_t mytime = time(NULL);

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("\n[ERROR]: while opening socket");
    return -1;
  }
  memset((char *)&recv_addr, 0, lengReciv);
  recv_addr.sin_family = AF_INET;
  recv_addr.sin_addr.s_addr = inet_addr(RECV_IP);
  recv_addr.sin_port = htons(RECV_PORT);

  strftime(line, 100, "%d-%m-%Y %H:%M", localtime(&mytime));
  sendto(sockfd, line, strlen(line) + 1, 0, (struct sockaddr *)&recv_addr, lengReciv);
}
