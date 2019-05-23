#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <affinity.h>

/**
 * This function sets the CPU affinity mask of the thread pthread to the
 * core id core_id.
 * @param pthread The thread.
 * @param core_id The core id.
 */

void set_affinity(pthread_t pthread, int core_id) {
  cpu_set_t cpu_set;
  int error;
  CPU_ZERO(&cpu_set);
  CPU_SET(core_id, &cpu_set);
  if ((error = pthread_setaffinity_np(pthread, sizeof(cpu_set_t), &cpu_set)) != 0) {
    fprintf(stderr, "pthread_setaffinity_np() failed...\n");
    exit(EXIT_FAILURE);
  }
  if (!CPU_ISSET(core_id, &cpu_set)) {
    fprintf(stderr, "CPU %d is not a member of set...\n", core_id);
    exit(EXIT_FAILURE);
  }
}
