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

static int echo_to_cli(int fd);
static void sig_child(int signo);

int
main(int argc, char **argv)
{
    int         listenfd, connfd;
    pid_t       pid;
    socklen_t   len;
    struct sockaddr_in srvaddr, cliaddr;

    listenfd = xsocket(AF_INET, SOCK_STREAM, 0);

    bzero(&srvaddr, sizeof(struct sockaddr_in));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(SERV_PORT);
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    xbind(listenfd, (xsockaddr *) &srvaddr, sizeof(struct sockaddr_in));

    xlisten(listenfd, LISTENQ);

    xsignal(SIGCHLD, sig_child);

    for ( ; ; ) {
        len = sizeof(struct sockaddr_in);
        connfd = xaccept(listenfd, (xsockaddr *) &cliaddr, &len);

        if ( (pid = fork()) == 0) { /* child proc */
            xclose(listenfd);
            echo_to_cli(connfd);
            xclose(connfd);
            exit(0);
        }
        xclose(connfd);
    }
}

static int
echo_to_cli(int fd)
{
    char buf[XBUFSIZE];
    int         n;

                        /* while it's not EOF */
    while ( (n = xread(fd, buf, XBUFSIZE)) != 0)
        xwrite(fd, buf, n);

    return 0;   /* Success */
}

static void
sig_child(int signo)
{
    pid_t   pid;
    int     stat;

    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated.\n", pid);

    return;
}
