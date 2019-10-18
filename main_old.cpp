#include "task/subtask.hpp"
#include "common/list.hpp"
#include "task/task.hpp"
#include "analysis/analysis.hpp"
#include "platform/platform.hpp"




#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>
int ss =0;


common::List<platform::Platform *> * sols;
platform::Platform * current_sol;


void generate_all_solutions(task::Taskset * ts, platform::Platform *procs , int m,
			    platform::Platform * curr){
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
      generate_all_solutions(tasks_b,procs,m,new_sol);
    }
  }
}


int main(int argc, char ** argv){


  sols  = new common::List<platform::Platform *>(); 

  task::Task * tau_1 = new task::Task(0,6,10,15);
  task::Task * tau_2 = new task::Task(1,5,10,15);
  task::Task * tau_3 = new task::Task(2,5,10,15);
   

  task::Taskset * tss = new task::Taskset();
  tss->add(tau_1);
  tss->add(tau_2);
  tss->add(tau_3);




  common::List<platform::Processor *> *engines = new    common::List<platform::Processor *>();
   
  platform::Processor *p_1 = new platform::Processor(0);
  platform::Processor *p_2 = new platform::Processor(1); 


  engines->add_at_head(new common::Node<platform::Processor *>(p_1));
  engines->add_at_head(new common::Node<platform::Processor *>(p_2));


  platform::Platform *pl = new platform::Platform();
  pl->_engines(engines);




  current_sol = pl->copy();
  sols = new common::List<platform::Platform *> ();
  generate_all_solutions(tss,pl,2,current_sol);

      

 



  printf("---------------------------------------------------------------- \n");

  for (int i=0;i<sols->size;i++)
    {
      printf("************************************************ \n");
      sols->get(i)->print_alloc();
    }








































   
  // This is the original source code !! to be uncommented !!
  // Houssam : Do not delete 
  
  // task::Taskset *tset = new task::Taskset(5);
  // common::List<task::Task *> *list = new common::List<task::Task *>();
  // common::Node<task::Subtask *> *v1 = new common::Node<task::Subtask *>( new task::Subtask(1,5,1,COMPUTE,GPU));
  // common::Node<task::Subtask *> *v2 = new common::Node<task::Subtask *>( new task::Subtask(2,0,1,CONDITION,CPU));
  // common::Node<task::Subtask *> *v2_c = new common::Node<task::Subtask *>( new task::Subtask(22,0,1,CCONDITION,CPU));
  // v2_c->el->_silent_subtask(v2->el);
  // common::Node<task::Subtask *> *v3 = new common::Node<task::Subtask *>( new task::Subtask(3,10,1,COMPUTE,CPU));
  // common::Node<task::Subtask *> *v4 = new common::Node<task::Subtask *>( new task::Subtask(4,10,1,COMPUTE,CPU));
  // common::Node<task::Subtask *> *v5 = new common::Node<task::Subtask *>( new task::Subtask(5,10,1,COMPUTE,CPU));
  // common::Node<task::Subtask *> *v6 = new common::Node<task::Subtask *>( new task::Subtask(6,0,1,ALTERNATIVE,CPU));
  // common::Node<task::Subtask *> *v7 = new common::Node<task::Subtask *>( new task::Subtask(7,0,2,COMPUTE,CPU));
  // common::Node<task::Subtask *> *v8 = new common::Node<task::Subtask *>( new task::Subtask(8,0,2,COMPUTE,CPU));

  // common::List<task::Subtask *> *l=new common::List<task::Subtask *>();
  // l->add_at_head(v1);
  // l->add_at_head(v2);
  // l->add_at_head(v2_c);
  // l->add_at_head(v3);
  // l->add_at_head(v5);
  // l->add_at_head(v6);
  // l->add_at_head(v7);
  // l->add_at_head(v8);



  // task::Task *tau = new task::Task(1,l);
  // tau->link_two_subtasks(v1,v2);
  // tau->link_two_subtasks(v2,v3);
  // tau->link_two_subtasks(v2,v2_c);
  // tau->link_two_subtasks(v3,v2_c);
  // tau->link_two_subtasks(v2_c,v5);
  // tau->link_two_subtasks(v5,v6);
  // tau->link_two_subtasks(v6,v7);
  // tau->link_two_subtasks(v6,v8);



  // tau->to_dot("/tmp/tt.dot");

  // // Houssam: I need to correct the generaton of the dbf 
  // tau->generate_all_conc_tag_el(ALTERNATIVE);
  // printf("here, passed? 1  \n");
  // task::Taskset *ts = new task::Taskset(-1);
  // tau->_concretes()->get(0)->display();
  // printf("here, passed? 2  Size : %d \n", tau->_concretes()->_size());
  // for (int t=0;t<200;t++){
  //   tau->_concretes()->get(0)->generate_all_conc_tag_el(CONDITION); 
  //   std::cout<<"("<<t<<","<<tau->_concretes()->get(0)->dbf_exact(t,ts)<<")"<<std::endl;
// }
}
