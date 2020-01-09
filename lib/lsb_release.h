#ifndef _LSB_RELEASE_H_
#define _LSB_RELEASE_H_

struct lsbReleaseStruct {
    char id[33];
    char release[17];
    char codename[17];
};

int getLsbRelease(struct lsbReleaseStruct *);

#endif
