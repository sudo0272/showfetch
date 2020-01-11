/*
MIT License

Copyright (c) 2020 홍세정

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
SOFTWARE.
*/

#include "uptime.h"
#include <stdio.h>
#include <errno.h>

extern int errno;

int getUptime(struct uptimeStructure *target) {
    unsigned int total;

    // initialize structure
    target->days = 0;
    target->hours = 0;
    target->minutes = 0;
    target->seconds = 0;

    FILE *fp;

    fp = fopen("/proc/uptime", "r");

    if (errno != 0) {
        return errno;
    }

    fscanf(fp, "%u", &total);
    
    target->days = total / 60 / 60 / 24;
    target->hours = total / 60 / 60 - target->days * 24;
    target->minutes = total / 60 - target->hours * 60 - target->days * 60 * 24;
    target->seconds = total - target->minutes * 60 - target->hours * 60 * 60 - target->days * 60 * 60 * 24;

    return errno;
}
