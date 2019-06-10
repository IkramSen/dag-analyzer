#ifndef TASKSET_HPP
#define TASKSET_HPP

#include "../common/list.hpp"
#include "task.hpp"
#include "../platform/processor.hpp"

namespace task {
  class Task;
  class Taskset{

  private:
    common::List<Task *> *list;
    int id;
  public:
    int _size();
    Taskset(int id);
    Taskset();
    ~Taskset();
    common::List<Task *> *_list();
    void _list(common::List<Task *> * list);
    int hyperperiod();
    void read(char *);
    void write(char *);
    void sort(int );
    double utilization();
    int LCM(int , int );
    void display();
    Taskset* copy();
  };
}
#endif
