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

#define MAXLEN4     4
#define MAXLEN6     /* not defined yet */

static uint32_t _xinet4_addr_recognizer(const char *addr);

void 
xinet_pton(sa_family_t satype, const char *strptr, void *addrptr)
{
    switch (satype) {
    case AF_INET: {
        struct in_addr in_val;
        in_val.s_addr = _xinet4_addr_recognizer(strptr);
        memcpy(addrptr, &in_val, sizeof(struct in_addr));
        return;
    }
    case AF_INET6:
        return;
    }

    err_quit("xinet_pton: unknown family used.");
}

static uint32_t
_xinet4_addr_recognizer(const char *addr)
{
    uchar i4[4];
    const char *ch = addr;
    short num = 0;
    int count;  /* dot counter */

    for (count = 0; count < MAXLEN4; ++ch) {
        switch (*ch) {
        case '\0':
            if (count != MAXLEN4-1) /* Is len of addr valid? */
                goto err;
            i4[count] = num;
            return *((uint32_t *)i4);
        case '.':
            i4[count++] = num;
            num = 0;
            /* fall through! */
        case ' ':
            continue;
        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
        case '8': case '9':
            num = num * 10 + (*ch - '0');
            if (num <= 255)
                continue;
            /* fall through */
        default:
            goto err;
        }
    }

err:
    err_quit("xinet_pton: invalid ip address");
}
