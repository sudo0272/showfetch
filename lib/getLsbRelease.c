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
    unsigned int variableLength;
    int i;

    fp = fopen("/etc/lsb-release", "r");

    if (errno != 0) {
        return errno;
    }

    printf("called...\n");

    while (fgets(buffer, 129, fp) != NULL) {
        printf("== %s\n", buffer);

        bufferStringLength = strlen(buffer);

        printf("%d %s", bufferStringLength, buffer);

        variable = strtok(buffer, "=");

        variableLength = strlen(variable);

        printf("-- %s\n", variable);

        if (variableLength < bufferStringLength) {
            value = strtok(&buffer[variableLength + 1], "\n");
            printf("value: %s\n", value);
            if (!strcmp(variable, "DISTRIB_ID")) {
                strcpy(target->id, value);
            } else if (!strcmp(variable, "DISTRIB_RELEASE")) {
                strcpy(target->release, value);
            } else if (!strcmp(variable, "DISTRIB_CODENAME")) {
                strcpy(target->codename, value);
            }
        } else {
            errno = ESPIPE;

            break;
        }
    }

    return errno;
}
