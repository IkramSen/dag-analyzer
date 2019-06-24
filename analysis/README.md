# Real-time analysis and optimization

The goal of this step is to take as input a set of real-time tasks
modelled with the grammar described in the package **gramm**, analyze
their behavior, and computer their affinity so all timing requirements
are respected.

If this operation fail, if no-feasibile solutions can be found. We
recall that using our grammar we defined a set of task specifications,
which are the expression of the same task using alternative nodes. At
the end, the task will select only one implementation, therefore the
final implementation will contain no-alternative node. We call an
implementation without alternatives, a **concrete** task. 
 

The problem adressed in this package is to assign each vertex, to a
single/muultiple core so that the all deadlines are met.

The details of each step how to optimize and analyze the behavior of a
real-time system can be found in the document "nv_paper.pdf" 
