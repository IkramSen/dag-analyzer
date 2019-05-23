#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time_utils.h>
#include <affinity.h>

sem_t task_entry_sem;
sem_t task_end_sem;

sem_t subtask_1_sem;
sem_t subtask_2_sem;
sem_t subtask_3_sem;
sem_t subtask_4_sem;
sem_t subtask_5_sem;
sem_t subtask_6_sem;
sem_t subtask_7_sem;
sem_t subtask_8_sem;
sem_t subtask_9_sem;
sem_t subtask_10_sem;
sem_t subtask_11_sem;
sem_t subtask_12_sem;

void * subtask_12(void * arg) { 

  while(1) {

    sem_init(&subtask_12_sem, 0, 0);

    sem_wait(&subtask_12_sem);

     // Task subtask_12 code here
     printf("subtask_12\n");

    sem_post(&task_end_sem);
  }

  return NULL;
}

void * subtask_11(void * arg) { 

  while(1) {

    sem_init(&subtask_11_sem, 0, 0);

    sem_wait(&subtask_11_sem);

     // Task subtask_11 code here
     printf("subtask_11\n");

    sem_post(&task_end_sem);
  }

  return NULL;
}

void * subtask_10(void * arg) { 

  while(1) {

    sem_init(&subtask_10_sem, 0, 0);

    sem_wait(&subtask_10_sem);

     // Task subtask_10 code here
     printf("subtask_10\n");

    sem_post(&subtask_7_sem);
  }

  return NULL;
}

void * subtask_9(void * arg) { 

  while(1) {

    sem_init(&subtask_9_sem, 0, 0);

    sem_wait(&subtask_9_sem);

     // Task subtask_9 code here
     printf("subtask_9\n");

    sem_post(&subtask_7_sem);
  }

  return NULL;
}

void * subtask_8(void * arg) { 

  while(1) {

    sem_init(&subtask_8_sem, 0, 0);

    sem_wait(&subtask_8_sem);

     // Task subtask_8 code here
     printf("subtask_8\n");

    sem_post(&subtask_9_sem);
    sem_post(&subtask_10_sem);
  }

  return NULL;
}

void * subtask_7(void * arg) { 

  while(1) {

    sem_init(&subtask_7_sem, 0, 0);

    sem_wait(&subtask_7_sem);
    sem_wait(&subtask_7_sem);
    sem_wait(&subtask_7_sem);

     // Task subtask_7 code here
     printf("subtask_7\n");

    sem_post(&subtask_11_sem);
    sem_post(&subtask_12_sem);
  }

  return NULL;
}

void * subtask_6(void * arg) { 

  while(1) {

    sem_init(&subtask_6_sem, 0, 0);

    sem_wait(&subtask_6_sem);

     // Task subtask_6 code here
     printf("subtask_6\n");

    sem_post(&subtask_7_sem);
  }

  return NULL;
}

void * subtask_5(void * arg) { 

  while(1) {

    sem_init(&subtask_5_sem, 0, 0);

    sem_wait(&subtask_5_sem);

     // Task subtask_5 code here
     printf("subtask_5\n");

    sem_post(&subtask_8_sem);
  }

  return NULL;
}

void * subtask_4(void * arg) { 

  while(1) {

    sem_init(&subtask_4_sem, 0, 0);

    sem_wait(&subtask_4_sem);

     // Task subtask_4 code here
     printf("subtask_4\n");

    sem_post(&subtask_5_sem);
  }

  return NULL;
}

void * subtask_3(void * arg) { 

  while(1) {

    sem_init(&subtask_3_sem, 0, 0);

    sem_wait(&subtask_3_sem);

     // Task subtask_3 code here
     printf("subtask_3\n");

    sem_post(&subtask_6_sem);
  }

  return NULL;
}

void * subtask_2(void * arg) { 

  while(1) {

    sem_init(&subtask_2_sem, 0, 0);

    sem_wait(&subtask_2_sem);

     // Task subtask_2 code here
     printf("subtask_2\n");

    sem_post(&subtask_3_sem);
    sem_post(&subtask_4_sem);
  }

  return NULL;
}

void * subtask_1(void * arg) { 

  while(1) {

    sem_init(&subtask_1_sem, 0, 0);

    sem_wait(&task_entry_sem);

     // Task subtask_1 code here
     printf("subtask_1\n");

    sem_post(&subtask_2_sem);
  }

  return NULL;
}

void * task_0(void * arg) { 

  struct periodic_data_struct *ps = (struct periodic_data_struct *) arg;
  struct timespec next;
  pthread_t tid;

  pthread_create(&tid, NULL, subtask_12,  NULL);
  pthread_create(&tid, NULL, subtask_11,  NULL);
  pthread_create(&tid, NULL, subtask_10,  NULL);
  pthread_create(&tid, NULL, subtask_9,  NULL);
  pthread_create(&tid, NULL, subtask_8,  NULL);
  pthread_create(&tid, NULL, subtask_7,  NULL);
  pthread_create(&tid, NULL, subtask_6,  NULL);
  pthread_create(&tid, NULL, subtask_5,  NULL);
  pthread_create(&tid, NULL, subtask_4,  NULL);
  pthread_create(&tid, NULL, subtask_3,  NULL);
  pthread_create(&tid, NULL, subtask_2,  NULL);
  pthread_create(&tid, NULL, subtask_1,  NULL);

  clock_gettime(CLOCK_REALTIME, &next);
  // set_affinity();

  while(1) {

    sem_init(&task_end_sem, 0, -2);

    sem_post(&task_entry_sem);

    // Task task_0 code here 
    printf("task_0\n");

    sem_wait(&task_end_sem);

    timespec_add_us(&next, ps->period_us);

    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
  }

  return NULL;
}

int main(void) {

  struct periodic_data_struct st;
  pthread_t th[1];
  st.index = 0;
  st.period_us = 300000;
  st.wcet_sim = 3000000;
  st.ndlinemiss = 2;

  pthread_create(&th[0], NULL, task_0, &st);
  pthread_join(th[0], NULL);

  return 0;
}

