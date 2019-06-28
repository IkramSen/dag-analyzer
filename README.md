# Real-time graph tool : Description language, Optimization and C-code generation

This software is a full-stack tool to describe, analyse and generate
the source code for a set of parallel real-time tasks that can be
modelled using *HPC dag* or  *Digraph* task models.

This software is authored and actively mainainted by **Houssam-Eddine
Zahaf**. We aknowledge the participation of *Lug Lemaitre, Damien
Amara* and *Ikram senoussaoui* for their participation in writting
some modules in this tool.  This tool is under **GPL Licence**. If you
want to cite this work, please use the following citation:


Houssam-Eddine ZAHAF, Nicola Capodieci, Roberto Cavicchioli, Giuseppe
Lipari, Marko Bertogna: *"The HPC-DAG Task Model for Heterogeneous
Real-Time Systems"*.


# Tool description

This tool is compound of mainly 4 components: **shared structures
package**, **description language package**, **real-time package**,
**c-code generator package**.


## shared structures package

In this package different data structures needed by all other packages
are detailled. It is compound of tasks and processors structures. 


### task structures 

The task structures package contains the definition of a subtask,
task, taskset, buffers and communications. The main class is task, as
it contains the main functions used in the task description analysis
and code generation. 


### processor structures 

The processor structures package contains all classes needed to
describe a set of **engines**. An engine is a processor able to achive
a given operation, it can be either a **compute** or **memory copy**
operation. An example of a compute engine can be a *CPU*, a *GPU* or
any type of compute engine. A memory copy engine can be a *schedulable
DMA* or a *copy engine* in a GPU. A platform is a list of engines. The
different types of engines can be defined using our language
tools. Each engine must have a real-time scheduling policy. Our tool
supports EDF and FP with preemptive and non-preemptive scheduling
using Global or partitioned scheduling techniques.


### list and common function 

This package contains the optimizations on list operations that are
used at different places in our tool, and priniting and debugging
funtionalities.


## Real-time description language

This package contains the implementation of a language that can be
used to describe a set of real-time tasks and a platform. Further
details can be found in README.md of gramm package.


## Real-time analysis and optimizations 

This package contains the descriptions how real-time optimization are
achieved.


## C-code generator

This package contains the description of how the source code of our
platform can be generated. Further details can be found in README.md
of code generation package.
