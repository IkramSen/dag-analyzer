#ifndef SUB_TASK_HPP
#define SUB_TASK_HPP

#include <map>
#include <iostream>
#include <string.h>
#include <string>

#define CONDITION 0
#define CCONDITION 4
#define ALTERNATIVE 1
#define COMPUTE 2
#define DUMMY 3

namespace task {
  class Subjob {
  private:
    int j_id, id, C, D, nextT, _abs_r;    
  public:
    Subjob(int id, int C, int D, int T, int _abs_r, int j_id);
    ~Subjob();
  };
}
#endif
