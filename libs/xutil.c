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

#include "xutil.h"

static void set_byteorder_value(void);

static xbyteorder xb_value = XB_NONE;

xbyteorder
byteorder(void)
{
    if (xb_value != XB_NONE)
        return xb_value;
    
    set_byteorder_value();

    return xb_value;
}

static void
set_byteorder_value(void)
{
    union {
        short s;
        char c[sizeof(short)];
    } u;

    u.s = 0x0102;
    if (sizeof(short) == 2) {
        if (u.c[0] == 1 && u.c[1] == 2)
            xb_value = XB_BIG;
        else if (u.c[0] == 2 && u.c[1] == 1)
            xb_value = XB_LITTLE;
        else
            xb_value = XB_UNKNOWN;
    } 
}