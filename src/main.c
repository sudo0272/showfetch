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
#include "../lib/icon.h"

#define USERNAME_MAX 32
#define HOSTNAME_MAX 64

#define ICON_WIDTH 20
#define ICON_HEIGHT 10

extern int errno;

int main() {
    char username[USERNAME_MAX + 1];
    char hostname[HOSTNAME_MAX + 1];
    struct iconStructure icon[ICON_HEIGHT][ICON_WIDTH] = {0, };
    char os[33];
    char date[30];
    // %Y-%m-%d %A %H:%M:%S

    int i, j;

    struct utsname systemNameInformaton;
    struct lsbReleaseStruct lsbRelease;
    struct uptimeStructure uptime;
    struct tm *currentTime;
    time_t rawTime;

    enum colorEnum symbolColor;

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
        setIconCharacterRow(icon[0], "#############  #####", ICON_WIDTH);
        setIconCharacterRow(icon[0], "#############  #####", ICON_WIDTH);
        setIconCharacterRow(icon[1], "#############  #####", ICON_WIDTH);
        setIconCharacterRow(icon[2], "#############  #####", ICON_WIDTH);
        setIconCharacterRow(icon[3], "#####          #####", ICON_WIDTH);
        setIconCharacterRow(icon[4], "#####  ######  #####", ICON_WIDTH);
        setIconCharacterRow(icon[5], "#####  ######  #####", ICON_WIDTH);
        setIconCharacterRow(icon[6], "#####  ######  #####", ICON_WIDTH);
        setIconCharacterRow(icon[7], "#####  ######  #####", ICON_WIDTH);
        setIconCharacterRow(icon[8], "#####  ######  #####", ICON_WIDTH);
        setIconCharacterRow(icon[9], "#####  ######  #####", ICON_WIDTH);
        
        for (i = 0; i < ICON_HEIGHT; i++) {
            for (j = 0; j < ICON_WIDTH; j++) {
                icon[i][j].color = GREEN;
                icon[i][j].thickness = BOLD;
            }
        }

        strcpy(os, "Manjaro Linux");

        symbolColor = GREEN;
    }

    printIconRow(icon[0], ICON_WIDTH); printf("    \033[%u;%um%s\033[%u;%um@\033[%u;%um%s\n", BOLD, symbolColor, username, REGULAR, WHITE, BOLD, symbolColor, hostname);
    printIconRow(icon[1], ICON_WIDTH);printf("   \033[%u;%um", BOLD, WHITE);
    for (i = strlen(username) + 1 + strlen(hostname) + 2; i != 0; i--) {
        //       username       @       hostname   front and end
        putchar('-');
    }
    putchar('\n');

    printIconRow(icon[2], ICON_WIDTH); printf("    \033[%u;%umOS       \033[%u;%um| \033[%u;%um%s %s ( %s ) %s\n", BOLD, symbolColor, BOLD, WHITE, REGULAR, WHITE, os, lsbRelease.release, lsbRelease.codename, systemNameInformaton.machine);
    printIconRow(icon[3], ICON_WIDTH); printf("    \033[%u;%umOS Type  \033[%u;%um| \033[%u;%um%s\n", BOLD, symbolColor, BOLD, WHITE, REGULAR, WHITE, systemNameInformaton.sysname);
    printIconRow(icon[4], ICON_WIDTH); printf("    \033[%u;%umKernel   \033[%u;%um| \033[%u;%um%s\n", BOLD, symbolColor, BOLD, WHITE, REGULAR, WHITE, systemNameInformaton.release);
    printIconRow(icon[5], ICON_WIDTH); printf("    \033[%u;%umHome     \033[%u;%um| \033[%u;%um%s\n", BOLD, symbolColor, BOLD, WHITE, REGULAR, WHITE, getenv("HOME"));
    printIconRow(icon[6], ICON_WIDTH); printf("    \033[%u;%umShell    \033[%u;%um| \033[%u;%um%s\n", BOLD, symbolColor, BOLD, WHITE, REGULAR, WHITE, getenv("SHELL"));
    printIconRow(icon[7], ICON_WIDTH); printf("    \033[%u;%umTerminal \033[%u;%um| \033[%u;%um%s\n", BOLD, symbolColor, BOLD, WHITE, REGULAR, WHITE, getenv("TERM"));
    printIconRow(icon[8], ICON_WIDTH); printf("    \033[%u;%umTime     \033[%u;%um| \033[%u;%um%s\n", BOLD, symbolColor, BOLD, WHITE, REGULAR, WHITE, date);
    printIconRow(icon[9], ICON_WIDTH); printf("    \033[%u;%umUptime   \033[%u;%um| \033[%u;%um%u day%s, %u hour%s, %u minute%s, %u second%s\n", BOLD, symbolColor, BOLD, WHITE, REGULAR, WHITE, uptime.days, uptime.days > 1 ? "s" : "", uptime.hours, uptime.hours > 1 ? "s" : "", uptime.minutes, uptime.minutes > 1 ? "s" : "", uptime.seconds, uptime.seconds > 1 ? "s" : "");

    return 0;
}
