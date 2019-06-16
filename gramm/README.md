# HPC-DAG Grammar:
Auteur : Houssam-Eddine Zahaf

# Tool description : 

This part of the HPC DAG Analyzer aims to provide a grammar to
describe the hardware architecture and the software stack using the
HPC DAG Model. Please, first overview the architecture and ssytem mode
section of paper authored by Zahaf et el. entitled : **The HPC DAG
task Model for heterogeneous real-time system**.

## The software description :
Our model support parallel execution and complex behaviors. 


We introduce the different features of our langage by example. First
let define a Liu and LayLand task. Therefore the task is a executed
using a single thread, characterized by :

- **C:** The task worst case execution time 
- **D**  The task deadline
- **T**  The task period, the time duration between to activations of the same 
- **PC** The task preemtion cost, which is the cost to account, if this task is preempted


