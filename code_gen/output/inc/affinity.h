#ifndef __DEF_AFFINITY_H__
#define __DEF_AFFINITY_H__

#include <pthread.h>

void set_affinity(pthread_t pthread, int core_id);

#endif /* __DEF_AFFINITY_H__ */
