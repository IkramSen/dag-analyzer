#ifndef TASK_SET_CODE_HPP
#define TASK_SET_CODE_HPP

#include "task_code.hpp"
#include "../task/taskset.hpp"
#include "../task/task.hpp"

namespace code_generator {

  class Taskset_code {

  public:
    Taskset_code();
    ~Taskset_code();
    std::string print_taskset(task::Taskset *taskset);
  };
}

#endif
