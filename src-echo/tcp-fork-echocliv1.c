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

static void sendrecv(int fd);

int
main(int argc, char **argv)
{
    int     sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
        strerr_quit("Usage: %s <ip address>", argv[0]);

    sockfd = xsocket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    xinet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    xconnect(sockfd, (xsockaddr *) &servaddr, sizeof(struct sockaddr_in));

    sendrecv(sockfd);

    xclose(sockfd);

    return 0;
}

static void
sendrecv(int fd)
{
    int     n;
    char buf[XBUFSIZE];

    while ( (n = xread(fileno(stdin), buf, XBUFSIZE)) != 0) {
        xwrite(fd, buf, n);

        n = xread(fd, buf, XBUFSIZE);

        xwrite(fileno(stdout), buf, n);
    }
}
