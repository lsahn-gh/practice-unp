/* Echo server v1 */

#include "punp.h"

int
main(int argc, char *argv[])
{
    int sockfd, clifd;
    struct sockaddr_in cliaddr, servaddr;
    char buf[MAXLINE];

    sockfd = xsocket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    xbind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    xlisten(sockfd, LISTENQ);

    for ( ; ; ) {
        size_t n;
        socklen_t len = sizeof(cliaddr);
        clifd = xaccept(sockfd, (struct sockaddr *) &cliaddr, &len);

        n = xread(clifd, buf, MAXLINE);
        xwrite(clifd, buf, n);

        xclose(clifd);
    }

    return 0;
}