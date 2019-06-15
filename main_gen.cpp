#include <iostream>
#include <string>

#include "task/taskset.hpp"
#include "task/task.hpp"
#include "task/subtask.hpp"

#include "code_gen/subtask_code.hpp"
#include "code_gen/taskset_code.hpp"

int main(int arc, char** argv) {

  // Instantiation of a graph nodes, i. e. the graph subtask.
  common::Node<task::Subtask *> *v1  = new common::Node<task::Subtask *>(new task::Subtask(1, 5, 1, COMPUTE, CPU));
  common::Node<task::Subtask *> *v2  = new common::Node<task::Subtask *>(new task::Subtask(2, 5, 2, CONDITION, CPU));
  common::Node<task::Subtask *> *v3  = new common::Node<task::Subtask *>(new task::Subtask(3, 5, 2, COMPUTE, CPU));
  common::Node<task::Subtask *> *v4  = new common::Node<task::Subtask *>(new task::Subtask(4, 5, 2, COMPUTE, CPU));
  common::Node<task::Subtask *> *v5  = new common::Node<task::Subtask *>(new task::Subtask(5, 5, 2, CONDITION, CPU));
  common::Node<task::Subtask *> *v6  = new common::Node<task::Subtask *>(new task::Subtask(6, 5, 2, CONDITION, CPU));
  common::Node<task::Subtask *> *v7  = new common::Node<task::Subtask *>(new task::Subtask(7, 5, 2, COMPUTE, CPU));
  common::Node<task::Subtask *> *v8  = new common::Node<task::Subtask *>(new task::Subtask(8, 5, 2, COMPUTE, CPU));
  common::Node<task::Subtask *> *v9  = new common::Node<task::Subtask *>(new task::Subtask(9, 5, 2, COMPUTE, CPU));
  common::Node<task::Subtask *> *v10 = new common::Node<task::Subtask *>(new task::Subtask(10, 5, 2, COMPUTE, CPU));
  common::Node<task::Subtask *> *v11 = new common::Node<task::Subtask *>(new task::Subtask(11, 5, 2, CCONDITION, CPU));
  v11->el->_silent_subtask(v5->el);
  common::Node<task::Subtask *> *v12 = new common::Node<task::Subtask *>(new task::Subtask(12, 5, 2, CCONDITION, CPU));
    v12->el->_silent_subtask(v6->el);
  common::Node<task::Subtask *> *v13 = new common::Node<task::Subtask *>(new task::Subtask(13, 5, 2, COMPUTE, CPU));
  v13->el->_silent_subtask(v4->el);
  common::Node<task::Subtask *> *v14 = new common::Node<task::Subtask *>(new task::Subtask(14, 5, 2, CCONDITION, CPU));
  v14->el->_silent_subtask(v2->el);
    common::Node<task::Subtask *> *v15 = new common::Node<task::Subtask *>(new task::Subtask(15, 5, 2, COMPUTE, CPU));
  // Add all graph nodes to a list.
  common::List<task::Subtask *> *l = new common::List<task::Subtask *>();
  l->add_at_head(v1);
  l->add_at_head(v2);
  l->add_at_head(v3);
  l->add_at_head(v4);
  l->add_at_head(v5);
  l->add_at_head(v6);
  l->add_at_head(v7);
  l->add_at_head(v8);
  l->add_at_head(v9);
  l->add_at_head(v10);
  l->add_at_head(v11);
  l->add_at_head(v12);
  l->add_at_head(v13);
  l->add_at_head(v14);
 

  // Instantiation of a task with the subtask list.
  task::Task *tau = new task::Task(1,l);
  tau->_D(1000000);
  tau->_T(2000000);
  // Link every node with each others.
  tau->link_two_subtasks(v1,v2);
  tau->link_two_subtasks(v2,v3);
  tau->link_two_subtasks(v3,v14);
  tau->link_two_subtasks(v2,v4);
  tau->link_two_subtasks(v4,v5);
  tau->link_two_subtasks(v4,v6);
  tau->link_two_subtasks(v5,v7);
  tau->link_two_subtasks(v5,v8);
  tau->link_two_subtasks(v6,v9);
  tau->link_two_subtasks(v6,v10);

  tau->link_two_subtasks(v7,v11);
  tau->link_two_subtasks(v8,v11);
  
  tau->link_two_subtasks(v9,v12);
  tau->link_two_subtasks(v10,v12);
  
  tau->link_two_subtasks(v12,v13);
  tau->link_two_subtasks(v11,v13);
  
  tau->link_two_subtasks(v12,v13);
  tau->link_two_subtasks(v13,v14);
  




  

  
  tau->_D(1000000);
  tau->_T(2000000);



  tau->to_dot("/tmp/arb.dot");
  
  task::Taskset *taskset = new task::Taskset();

  taskset->_list()->add_at_tail(new common::Node<task::Task *>(tau));

  
  code_generator::Taskset_code *taskset_code = new code_generator::Taskset_code();

  // Print to stdout the task code set.
  taskset_code->generate_source(taskset,"code_gen/output/");
}
