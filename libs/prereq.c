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
xsocket(int domain, int type, int proto)
{
    int fd;

    if ( (fd = socket(domain, type, proto)) < 0)
        strerr_quit("xsocket");

    return fd;
}

int
xconnect(int sockfd, const xsockaddr *addr, socklen_t addrlen)
{
    int ret;

    if ( (ret = connect(sockfd, addr, addrlen)) != 0)
        strerr_quit("xconnect");

    return ret;
}

int
xbind(int sockfd, const xsockaddr *addr, socklen_t addrlen)
{
    int ret;

    if ( (ret = bind(sockfd, addr, addrlen)) != 0)
        strerr_quit("xbind");

    return ret;
}

int
xlisten(int sockfd, int backlog)
{
    int ret;

    if ( (ret = listen(sockfd, backlog)) != 0)
        strerr_quit("xlisten");

    return ret;
}

int
xaccept(int sockfd, xsockaddr *addr, socklen_t *addrlen)
{
    int ret;

    while ( (ret = accept(sockfd, addr, addrlen)) < 0) {
        switch (errno) {
        case EINTR:
            continue;
        default:
            strerr_quit("xaccept");
        }
    }

    return ret;
}

int
x_sctp_bindx(int sockfd, const xsockaddr *addrs,
             int addrcnt, int flags)
{
    int ret;

    if ( (ret = sctp_bindx(sockfd, addrs, addrcnt, flags)) == -1) {
        switch (errno) {
        case EINVAL:
        /* Refer to section 9.3, 'sctp_bindx' Function
         * at the book, UNIX Network Programming, Vol 1.
         * 
         * fall through! */
        default:
            strerr_quit("x_sctp_bindx");
        }
    }

    return ret;
}

int
x_sctp_connectx(int sockfd, const xsockaddr *addrs,
                int addrcnt, sctp_assoc_t *id)
{
    int ret;

    if ( (ret = sctp_connectx(sockfd, addrs, addrcnt, id)) == -1) {
        switch (errno) {
        default:
            strerr_quit("x_sctp_connectx");
        }
    }

    return ret;
}
