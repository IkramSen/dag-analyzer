#ifndef TASKSET_HPP
#define TASKSET_HPP

#include "../common/list.hpp"
#include "task.hpp"
#include "../platform/processor.hpp"

namespace task {
  class subjob;
  class Subjobset{

  private:
    common::List<subjob *> *list;
    int id;
  public:
    int _size();
    Subjobset(int id);
    Subjobset();
    ~Subjobset();
    common::List<Task *> *_list();
    void _list(common::List<Task *> * list);
    void add(Subjob * s);
    
    int LCM(int , int );
    void display();
    Taskset* copy();
    bool remove(Task * tau);
    void merge(Taskset *ts);
    int preemption_cost_shorter_deadlines(int D);
    Task * get(int i); 
  };
}
