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

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include "../lib/lsb_release.h"

#define USERNAME_MAX 32
#define HOSTNAME_MAX 64

#define ICON_WIDTH 40
#define ICON_HEIGHT 20

extern int errno;

int main() {
    char username[USERNAME_MAX + 1];
    char hostname[HOSTNAME_MAX + 1];
    char icon[ICON_HEIGHT][ICON_WIDTH + 1];

    struct utsname systemNameInformaton;
    struct lsbReleaseStruct lsbRelease;

    if (getlogin_r(username, sizeof(username))) { // if getting username has been failed
        printf("Getting username has been failed\n");
        printf("ERRNO %d: %s\n", errno, strerror(errno));

        return errno;
    }

    if (gethostname(hostname, HOSTNAME_MAX + 1)) { // if getting hostname has been failed
        printf("Getting hostname has been failed\n");
        printf("ERRNO %d: %s\n", errno, strerror(errno));

        return errno;
    }
    
    if (uname(&systemNameInformaton)) { // if getting names of system, node, release, version or machine has been failed
        printf("Getting system information has been failed\n");
        printf("ERRNO %d: %s\n", errno, strerror(errno));

        return errno;
    }

    if (getLsbRelease(&lsbRelease)) {
        printf("Getting lsb-release information has been failed\n");
        printf("ERRNO %d: %s\n", errno, strerror(errno));

        return errno;
    }

    printf("%s\n", username);
    printf("%s\n", hostname);
    printf("%s\n", systemNameInformaton.machine);
    printf("%s\n", systemNameInformaton.release);
    printf("%s\n", systemNameInformaton.sysname);
    printf("%s\n", lsbRelease.codename);
    printf("%s\n", lsbRelease.id);
    printf("%s\n", lsbRelease.release);

    return 0;
}
