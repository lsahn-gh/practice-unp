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

ssize_t
xread(int fd, void *buf, size_t count)
{
    int ret;

    while ( (ret = read(fd, buf, count)) < 0) {
        switch (errno) {
        case EINTR:
            continue;
        default:
            strerr_quit("xread");
        }
    }

    return ret;
}

/* xwrite is just a wrapper function.
 * The functionality is almost same, except error handling.
 * 
 * It can handle errors as below,
 * - EINTR (raised by Signal) */
ssize_t
xwrite(int fd, const void *buf, size_t count)
{
    int ret;

    while ( (ret = write(fd, buf, count)) < 0) {
    /* It does not handle the case of ret is 0. */
        switch (errno) {
        case EINTR:
            continue;
        default:
            strerr_quit("xwrite");
        }
    }

    return ret;
}

int
xclose(int fd)
{
    int ret;

    if ( (ret = close(fd)) != 0) {
        switch (errno) {
        case EINTR:
            break;
        default:
            strerr_quit("xclose");
        }
    }

    return ret;
}

int
xpoll(struct pollfd *fds,
      nfds_t nfds,
      int timeout)
{
    int nready;

    while ( (nready = poll(fds, nfds, timeout)) <= 0) {
        if (nready == 0)
            /* timeout and none of readable streams yet. */
            continue;
        switch (errno) {
            case EAGAIN: 
            /* For portable programs, some other UNIX systems
             * poll can fail with 'EAGAIN' if the system fails to
             * allocate kernel-internal resources.
             * -- see POLL(2) man 
             * 
             * fall through! */
            case EINTR:
                continue;
            default:
                strerr_quit("xpoll");
        }
    }

    return nready;
}
