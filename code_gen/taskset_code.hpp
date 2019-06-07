#ifndef TASK_SET_CODE_HPP
#define TASK_SET_CODE_HPP

#include "task_code.hpp"
#include "../task/taskset.hpp"
#include "../task/task.hpp"


#define TOFILE 0
#define CONSOLE 1


namespace code_generator {

  class Taskset_code {

  public:
    Taskset_code();
    ~Taskset_code();

    void  generate_source(task::Taskset *taskset, std::string path );
    void  generate_source(task::Taskset *taskset);
    void  print_taskset(task::Taskset *taskset, int PRINT_MODE, std::string f_p) ;
  };
}

#endif
