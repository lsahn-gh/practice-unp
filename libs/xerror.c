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

#include "xerror.h"

static void _punp_err_log(int lvl, const char *fmt, va_list ap);

void
_punp_err_quit(int lvl, const char *fmt, ...)
{
    va_list     ap;

    va_start(ap, fmt);
    _punp_err_log(lvl, fmt, ap);
    va_end(ap);
    exit(EXIT_FAILURE);
}

/* Not sure this is useful */
void
_punp_err_print(int lvl, const char *fmt, ...)
{
    va_list     ap;

    va_start(ap, fmt);
    _punp_err_log(lvl, fmt, ap);
    va_end(ap);
}

static void
_punp_err_log(int lvl, const char *fmt, va_list ap)
{
    int errno_save, n;
    char buf[MAXERRLOG];

    errno_save = errno;
#if (defined _ISOC99_SOURCE || (defined _BSD_SOURCE || _XOPEN_SOURCE >= 500))
    n = vsnprintf(buf, MAXERRLOG, fmt, ap); /* safe */
#else
    n = vsprintf(buf, fmt, ap);     /* unsafe */
#endif
    assert(n < MAXERRLOG);
    switch (lvl) {
    case LOG_STRERR:
        snprintf(buf + n, MAXERRLOG - n, ": %s", strerror(errno_save));
    }
    
    if (strlen(buf) < MAXERRLOG-1)
        strcat(buf, "\n");

    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
}
