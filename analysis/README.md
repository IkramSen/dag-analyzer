# Real-time analysis and optimization
Author : Houssam-Eddine Zahaf

The goal of this step is to achieve real-time schedulability analysis
and optimizations so that all sub-tasks are feasibility allocated. It
takes as input a set of real-time tasks modeled with the grammar
described in the package **gramm**, analyze their behavior, and
computer their affinity so all timing constraints are respected.

If this operation fail (no-feasible solutions can be found), the
optimization phase is aborted and the whole compilation process is
also aborted, unless the user has forced the source code generation
even if the optimization failed by using FORCE_CODE_GENERATION
flag. We recall that using our grammar we defined a set of task
specifications. Each specification is several implementation
alternatives the same task using the **alta** nodes. At the end, only
one implementation has to be selected, therefore the final
implementation will not contain any **alta** node.

The problem addressed in this package is to assign to select the most
suitable implementation alternative, assign its sub-tasks to compute
and copy engines so that the all deadlines are met. This step supports
EDF and FP for preemptive and non preemptivesystems.

Details about the theory behind this package can be found in the
document *nv_paper.pdf*, attached in this package.
