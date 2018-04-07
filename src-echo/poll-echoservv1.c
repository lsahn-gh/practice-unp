/*
 * MIT License
 *
 * Copyright (c) 2018 Yi-Soo An
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "punp.h"

int
main(int argc, char **argv)
{
            /* maxi is max index. */
    int     i, maxi, listenfd, connfd, sockfd;
    int     nready;
    ssize_t n;
    char    buf[MAXLINE];
    struct pollfd clients[XOPEN_MAX];
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;

    listenfd = xsocket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    xbind(listenfd, (xsockaddr *) &servaddr, sizeof(servaddr));

    xlisten(listenfd, LISTENQ);

    maxi = 0;
    clients[maxi].fd = listenfd;
    clients[maxi].events = POLLIN;
    for (i = 1; i < XOPEN_MAX; i++)
        clients[i].fd = -1;

    for ( ; ; ) {
        nready = xpoll(clients, maxi+1, INFTIM);

        if (clients[0].revents & POLLIN) { /* Req connection */
            clilen = sizeof(cliaddr);
            connfd = xaccept(listenfd, (xsockaddr *) &cliaddr, &clilen);

            for (i = 1; i < XOPEN_MAX; i++)
                if (clients[i].fd == -1) {
                    clients[i].fd = connfd;
                    clients[i].events = POLLIN;
                    break;
                }
            if (i == XOPEN_MAX)
                err_quit("List of clients is full.");

            if (i > maxi)
                maxi = i;

            if (--nready <= 0)
                continue;
        }

        for (i = 1; i <= maxi; i++) {
            if ( (sockfd = clients[i].fd) < 0)
                continue;
            if (clients[i].revents & (POLLIN | POLLERR)) {
                if ( (n = xread(sockfd, buf, MAXLINE)) == 0) {
                    xclose(sockfd);
                    clients[i].fd = -1;
                }
                else
                    xwrite(sockfd, buf, n);

                if (--nready <= 0)
                    break;
            }
        }
    }

    return EXIT_SUCCESS;
}