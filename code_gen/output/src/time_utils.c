#include <time_utils.h>




void timespec_add_us(struct timespec *t, long us)
{

  t->tv_sec += us/1000000;
  t->tv_nsec += us%1000000;  
  if (t->tv_nsec > 1000000000) {
    t->tv_nsec = t->tv_nsec - 1000000000;
    t->tv_sec += 1;
  }
}

void print_spec(struct timespec *t)
{
  printf("[ tv_sec: %lu, tv_nsec:  %lu @ \n",t->tv_sec, t->tv_nsec);
}

int random_between(int a, int b)
{
  return  rand()%20-10;
}

int timespec_cmp(struct timespec *a, struct timespec *b)
{
  if (a->tv_sec > b->tv_sec) return 1;
  else if (a->tv_sec < b->tv_sec) return -1;
  else if (a->tv_sec == b->tv_sec) {
    if (a->tv_nsec > b->tv_nsec) return 1;
    else if (a->tv_nsec == b->tv_nsec) return 0;
    else return -1;
  }
  return -1;
}

int timespec_sub(struct timespec *d, struct timespec *a, struct timespec *b)
{
  d->tv_nsec = a->tv_nsec - b->tv_nsec;
  d->tv_sec =  a->tv_sec - b->tv_sec;
  if (a->tv_nsec < b->tv_nsec) {
    d->tv_nsec += 1000000000;
    d->tv_sec -= 1;
  }
  return 1;
}


void move_data(void * p, int size){
}
