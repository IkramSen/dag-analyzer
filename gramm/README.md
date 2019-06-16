# HPC-DAG Grammar:
Auteur : Houssam-Eddine Zahaf


This part of the HPC DAG Analyzer aims to provide a grammar to
describe the hardware architecture and the software stack using the
HPC DAG Model. Please, first overview the architecture and ssytem mode
section of paper authored by Zahaf et el. entitled : **"The HPC DAG
task Model for heterogeneous real-time system"**.

## The hardware description : 
## The software description :



We introduce the different features of our langage by example. 


### Simple example : LL Task model 

First let define a Liu and LayLand task. Therefore the task is a
executed using a single thread, characterized by :

- **C:**  The task worst case execution time 
- **D:**  The task deadline
- **T:**  The task period, the time duration between to activations of the same 
- **PC:** The task preemtion cost, which is the cost to account, if this task is preempted


Each task definition is considered as a Graph, task **tau** can be defined as follows:

```c
Graph tau(T=50,D=40);	
```


In this example, we define task tau, with a period of 50ms, and a deadline of 40ms.  
To define the task execution time, and preemption cost we define *Compute Nodes* as follows : 

```c
Node dd(C=4);
``` 

In the example above, we defined a compute Node **dd** having an
execution time that is equal to 4ms. To assign this node to the task
**tau**, the relation has to be defined as follows: 

```c
tau={dd;};
``` 

This is equivalent of defining a periodic Liu and Layland task, having
a period of 50 ms, a deadline of 40 ms, and worst case execution time
of 4 ms.

Further, the preemption cost may be defined using the keyword *PC* in
the node declaration, as well as the task TAG is a heterogeneous
architecture is considered. For example:

```c
Node dd(C=4, PC=3, TAG=GPU,"TT"="BB");
``` 

defines that node **dd** has a preemption cost of 3 ms and can only
execute within a GPU node. If **PC** is not explicitly mentioned, it
is considered as equal to **0**. If the **TAG** is not specified, it
is considered as the default **TAG**. The user may define extra
parameters to a given subtask so it can be used for
extra-functionalities that are not provided by the current version of
the tool. In contrast to the other optional properties, he execution
time property is mondatory, and an error is generated and compilation
will be aborted if not available.



### A parallel task example using directed acyclic graphs (examples/fork_join.c)

The user may want to express parallelization and more complex
execution patterns than those of LL model. Here we provide a new
example.


Let tau be a task compound of a sequential thread **seq1**, two
parallel threads **p1** and **p2** to join back a sequential thread
**seq2** as described in the following Figure 


<!-- ![Example of fork join parallel style ](figs/fork_join.png) -->

<div style="text-align:center"><img src="figs/fork_join.png" /></div>

Such a graph can be described using our grammar as following: 


```c++
Tag CPU, GPU;
Node seq1(C=4, TAG=CPU);
Node p1(C=4,PC=3,TAG=GPU);
Node p2(C=2, TAG=CPU);
Node seq2(C=1, TAG=CPU);

Graph tau(T=50,D=40);

tau={
  seq1;
  par(p1,p2);
  seq2;
};

generate(tau,"/tmp/gr.dot");
``` 

Let now explain each line of the above listing. The first Line is
similar to the Tags described in Hardware modeling section. Further,
we describe each thread/functionality as in the previous example.
Further, we describe the task behavior and composition, therefore the
subtasks are ordered according to their appearance/calling order in
the task structure description block. Thus, the graph **tau** starts
by seq1. Further, we find the keyword **par**, therefore all nodes
between the parenthesis after par are supposed to be executed in
parallel. Therefore, **p1** and **p2** can be executed in parallel
after **seq1** has finished its execution. At the end of the execution
of both **p1** and **p2**, the execution continues onward by executing
*seq2*. **par** operation is not only binary, it can take several
nodes (more than one).

After the task declaration block, the **generate** keyword allows to
 visualize the graph structure of task **tau**, and print it in
 "/tmp/gr.dot" in **GraphViz** (dot) format.
 
 

 
### Sgraph
 
 copy
 locks 
 
 Usually in a complex real-time task, such those found in autonomous
 driving, several functionalities are used at different places in the
 software design. Our grammar provides the necessary tools for such
 repetitive software modules, by the mean of **sGraph**s and the copy
 operation.


##  Shared buffers
 
### conditions 
### alternatives 
 
 
### multiperiodics 
 
 
 
### modular programming
