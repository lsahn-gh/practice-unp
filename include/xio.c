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

#include "punp.h"

ssize_t
xread(int fd, void *buf, size_t count)
{
    int ret;

again:
    if ( (ret = read(fd, buf, count)) < 0) {
        switch (errno) {
        case EINTR:
            goto again;
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

again:
    if ( (ret = write(fd, buf, count)) < 0) {
    /* It does not handle the case of ret is 0. */
        switch (errno) {
        case EINTR:
            goto again;
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

again:
    if ( (ret = close(fd)) != 0) {
        switch (errno) {
        case EINTR:
            goto again;
        default:
            strerr_quit("xclose");
        }
    }

    return ret;
}