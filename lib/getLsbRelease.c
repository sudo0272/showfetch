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
