#ifndef __TIMEUTILS_H__
#define __TIMEUTILS_H__

#include <time.h>

struct periodic_data_struct {
    int index;
    long period_us;
    int wcet_sim;
    int ndlinemiss;
    int highp;
    int lowp;
};

void timespec_add_us(struct timespec *t, long us);
int timespec_cmp(struct timespec *a, struct timespec *b);
int timespec_sub(struct timespec *d, struct timespec *a, struct timespec *b);

#endif
