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
    void sort(int);
    void add(Task * tau);
    double utilization();
    int LCM(int , int );
    void display();
    Taskset* copy();
    bool remove(Task * tau);
    void merge(Taskset *ts);
    int preemption_cost_shorter_deadlines(int D);
    Task * get(int i);
    Taskset* partial_copy();
    Taskset* params_copy();
    Taskset* params_task_pointers();
    double Liu_U();
  };
}
#endif
