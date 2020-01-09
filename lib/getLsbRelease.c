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

#include "lsb_release.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

extern int errno;

int getLsbRelease(struct lsbReleaseStruct *target) {
    FILE *fp;
    char buffer[129];
    char *variable;
    char *value;
    unsigned int bufferStringLength;
    int i;

    // initialize target
    *target->codename = NULL;
    *target->id = NULL;
    *target->release = NULL;

    fp = fopen("/etc/lsb-release", "r");

    if (errno != 0) {
        return errno;
    }

    while ((fgets(buffer, 129, fp)) != EOF) {
        bufferStringLength = strlen(buffer);

        variable = buffer;

        for (i = 0; i < bufferStringLength - 1; i++) {
            if (buffer[i + 1] == '=') {
                buffer[i] = '\0';

                break;
            }
        }

        if (i + 2 < bufferStringLength) {
            value = i + 2;

            if (!strcmp(variable, "DISTRIB_ID")) {
                *target->id = value;
            } else if (!strcmp(variable, "DISTRIB_RELEASE")) {
                *target->release = value;
            } else if (!strcmp(variable, "DISTRIB_CODENAME")) {
                *target->release = value;
            }
        } else {
            errno = EPIPE;

            return -1;
        }
    }

    return 0;
}
