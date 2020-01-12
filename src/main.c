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
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>
#include "../lib/lsb_release.h"
#include "../lib/uptime.h"

#define USERNAME_MAX 32
#define HOSTNAME_MAX 64

#define ICON_WIDTH 20
#define ICON_HEIGHT 10

extern int errno;

int main() {
    char username[USERNAME_MAX + 1];
    char hostname[HOSTNAME_MAX + 1];
    char icon[ICON_HEIGHT][ICON_WIDTH + 1];
    char os[33];
    char date[30];
    // %Y-%m-%d %A %H:%M:%S

    int i;

    struct utsname systemNameInformaton;
    struct lsbReleaseStruct lsbRelease;
    struct uptimeStructure uptime;
    struct tm *currentTime;
    time_t rawTime;

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

    if (getUptime(&uptime)) {
        printf("Getting uptime has been failed\n");
        printf("ERRNO %d: %s\n", errno, strerror(errno));

        return errno;
    }

    time(&rawTime);
    if (rawTime == NULL) {
        printf("Getting raw time has been failed\n");
        printf("ERRNO %d: %s\n", errno, strerror(errno));

        return errno;
    }

   currentTime = localtime(&rawTime);

    if (strftime(date, 30, "%Y-%m-%d %A %H:%M:%S", currentTime) == 0) {
        printf("Getting formatting time has been failed\n");
        printf("ERRNO %d: %s\n", errno, strerror(errno));

        return errno;
    }

    if (!strcmp(lsbRelease.id, "ManjaroLinux")) {
        strcpy(icon[0], "#############  #####");
        strcpy(icon[1], "#############  #####");
        strcpy(icon[2], "#############  #####");
        strcpy(icon[3], "#####          #####");
        strcpy(icon[4], "#####  ######  #####");
        strcpy(icon[5], "#####  ######  #####");
        strcpy(icon[6], "#####  ######  #####");
        strcpy(icon[7], "#####  ######  #####");
        strcpy(icon[8], "#####  ######  #####");
        strcpy(icon[9], "#####  ######  #####");

        strcpy(os, "Manjaro Linux");
    }

    printf("%s    %s@%s\n", icon[0], username, hostname);
    printf("%s   ", icon[1]);
    for (i = strlen(username) + 1 + strlen(hostname) + 2; i != 0; i--) {
        //       username       @       hostname   front and end
        putchar('-');
    }
    putchar('\n');

    printf("%s    OS       | %s %s ( %s ) %s\n", icon[2], os, lsbRelease.release, lsbRelease.codename, systemNameInformaton.machine);
    printf("%s    OS Type  | %s\n", icon[3], systemNameInformaton.sysname);
    printf("%s    Kernel   | %s\n", icon[4], systemNameInformaton.release);
    printf("%s    Home     | %s\n", icon[5], getenv("HOME"));
    printf("%s    Shell    | %s\n", icon[6], getenv("SHELL"));
    printf("%s    Terminal | %s\n", icon[7], getenv("TERM"));
    printf("%s    Time     | %s\n", icon[8], date);
    printf("%s    Uptime   | %u day%s, %u hour%s, %u minute%s, %u second%s\n", icon[9], uptime.days, uptime.days > 1 ? "s" : "", uptime.hours, uptime.hours > 1 ? "s" : "", uptime.minutes, uptime.minutes > 1 ? "s" : "", uptime.seconds, uptime.seconds > 1 ? "s" : "");
    
    return 0;
}
