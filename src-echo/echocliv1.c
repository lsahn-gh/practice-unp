/* Echo client v1 
 * With default error handlers. */

#include "punp.h"

int
main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;
    char str[XBUFSIZE];

    if (argc != 2)
        err_quit("usage: echocliv1 <IPaddress>");

    sockfd = xsocket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = xinet_pton(argv[1]);

    xconnect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    for ( ; ; ) {
        int n;
        n = xread(fileno(stdin), str, MAXLINE);
        xwrite(sockfd, str, n);
        xread(sockfd, str, MAXLINE);
        printf("%s\n", str);
    }

    return 0;
}