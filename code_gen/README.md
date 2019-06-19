# Code generator description 

This package is responsible for generating the task and subtasks code
for a given task system under a heterogeneous platform. First, we
assume that all alternative choices have been made in the real-time
optimization and testing phase. Therefore, the task generation does
not consider tasks with **alternative** nodes. 

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


### The generation of subtask  Initialization  code




### Compute Node "COMPUTE"

### Conditional Nodes  "CONDITION"

### Closing condition  Nodes "CCONDITION"


## Task code generation 


