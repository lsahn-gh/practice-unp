/* MIT License

Copyright (c) 2018 Yi-Soo An

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#ifndef _practice_unp_h_
#define _practice_unp_h_

/* memnoth-defined file */
#include "headers.h"
#include "xerror.h"
/* end of memnoth-defined */

/* user-defined const */
#define XBUFSIZE 4096
#define MAXLINE XBUFSIZE

/* Network */
#define SERV_PORT   9877
#define LISTENQ     1024    /* complete connection queue */


uint32_t xinet_pton(char *addr);

int xsocket(int domain, int type, int proto);
int xconnect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int xbind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int xlisten(int sockfd, int backlog);
int xaccept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/* I/O */
ssize_t xread(int fd, void *buf, size_t count);
ssize_t xwrite(int fd, const void *buf, size_t count);
int xclose(int fd);

#endif
