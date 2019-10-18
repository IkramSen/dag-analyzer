#include "../task/subtask.hpp"
#include "../common/list.hpp"
#include "../task/task.hpp"
#include "analysis.hpp"
#include "../platform/platform.hpp"




#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>

int ss =0;


void generate_all_solutions(task::Taskset * ts, platform::Platform *procs , int m,
			    platform::Platform * curr, common::List<platform::Platform *> * sols){
  if (ts->_size()==0){    
    ss++;
    if (curr->check_utilization())
      sols->add_at_tail(new common::Node<platform::Platform *>(curr));
    else {
      curr->print_alloc();
    }
    return;
  }

  for (int i=ts->_size()-1;i>-1;i--) {
    for (int j=0;j<m;j++){
      platform::Platform * new_sol = curr->copy();   
      new_sol->find_processor(procs->get(j)->_id())->_ts()->add(ts->get(i));;
      task::Taskset *  tasks_b =  ts->params_task_pointers();
      if (!new_sol->check_utilization())
      	  return;
      tasks_b->remove(ts->get(i));
      generate_all_solutions(tasks_b,procs,m,new_sol,sols);
    }
  }
}


