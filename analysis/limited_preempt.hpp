#ifndef LIMITED_PREEMPT_HPP
#define LIMITED_PREEMPT_HPP

void generate_all_solutions(task::Taskset * ts, platform::Platform *procs , int m,
			    platform::Platform * curr , common::List<platform::Platform *> * sols);



#endif
