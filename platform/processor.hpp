#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "../task/taskset.hpp"
#include "../task/task.hpp"

#define PREEMPTIVE 0
#define NPREEMPTIVE 1
#define EDF  0
#define FP 1


namespace task{
  class Taskset;
  class Task;
}

namespace platform{

  class Processor {
  private:
    int id;
    task::Taskset *ts;
    int TAG;
    int policy;


  public:
    Processor();
    Processor(int id, int tag, task::Taskset *ts );
    void _id(int id);
    int _id();

    void print_ts();
    Processor(int id) ;
    void _ts(task::Taskset *ts);
    task::Taskset *_ts();

    bool test_edf(task::Task *tau, int PREEMPTION);
    bool test_FP(task::Task *tau, int PREEMPTION);
    bool test_schedulability(int POLICY, task::Task *tau, int PREEMPTION);
    
    void _TAG(int tag);
    int _TAG();
    Processor* copy();    
  };

}

#endif
