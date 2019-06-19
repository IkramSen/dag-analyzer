# Code generator description 

This package is responsible for generating the task and subtasks code
for a given task system under a heterogeneous platform. First, we
assume that all alternative choices have been made in the real-time
optimization and testing phase. Therefore, the task generation does
not consider tasks with **alternative** nodes. 

```c
void * v13(){ 
 // The rest of the code 
}
```


Mainly three files are generated: **main.cpp**, **tasks.cpp** and
**tasks.hpp**. 


## Subtask code generation

Each sub-task is implemented using a thread. If we consider
multiperiodic task sets (communicating tasks may have different
periods), each thread is periodic it self. However, if all subtasks of
the same task share the same period, threads periodicity is ensured by
the task thread. 

For each task we generate two parts : The initialization part, and the
periodic part.



### The generation of subtask  Initialization  code



```c
  int s; 
  cpu_set_t cpuset;
  pthread_t thread;
  thread = pthread_self();
  CPU_ZERO(&cpuset);
  CPU_SET(1, &cpuset);
  s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
  if (s != 0){ 
    printf(" Allocation Error: Unable to allocatev13 to computing unit 1, exiting \n ");
    exit(-1); 
  } 
``` 


### The generation of subtask  looped code

```c
  while(1) {

    sem_wait(&v11_v13_sem);
    sem_wait(&v12_v13_sem);

    // Please insert Sub-task   v13   code here
    printf("  v13  \n");

    sem_post(&v13_v14_sem);
  }
```
 



### Compute Node "COMPUTE"

### Conditional Nodes  "CONDITION"

### Closing condition  Nodes "CCONDITION"


## Task code generation 


