#include <tasks.h> 

int main(void) {

  int N = 1;
  pthread_t th[1];  int periods[2]={2000000,-1}; 
  int deadlines[2]={1000000,-1}; 
  void * thread_names[2]={Task_1, NULL}; 
  struct periodic_data_struct st[N];

  for (int i=0; i<N; i++){
    st[i].index = i;
    st[i].period_us = periods[i];
    st[i].deadline_us = deadlines[i];
  }
  for (int i=0;i<N;i++){ 
    pthread_create(&th[i], NULL, thread_names[i], &st[i]);
  } 
   for (int i=0;i<N;i++){ 
    pthread_join(th[i], NULL);
  }

  return 0;
}
