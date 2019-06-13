#ifndef __TIMEUTILS_H__
#define __TIMEUTILS_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
struct periodic_data_struct {
  int index;
  long period_us;
  int deadline_us;
};

void timespec_add_us(struct timespec *t, long us);
int timespec_cmp(struct timespec *a, struct timespec *b);
int timespec_sub(struct timespec *d, struct timespec *a, struct timespec *b);
void print_spec(struct timespec *t);

int random_between(int a, int b); 

// Houssam : Need to redefine this function more properly 
void move_data(void * p, int size);
#endif
