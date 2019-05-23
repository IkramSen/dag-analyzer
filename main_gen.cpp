#include <iostream>
#include <string>

#include "task/taskset.hpp"
#include "task/task.hpp"
#include "task/subtask.hpp"

#include "code_gen/subtask_code.hpp"
#include "code_gen/taskset_code.hpp"

#define CPU   0
#define GPU   1
#define IGPU  2
#define DLA   3
#define PVA   4

int main(int arc, char** argv) {

  // Instantiation of a graph nodes, i. e. the graph subtask.
  common::Node<task::Subtask *> *v1  = new common::Node<task::Subtask *>(new task::Subtask(1, 5, 1, COMPUTE, GPU));
  common::Node<task::Subtask *> *v2  = new common::Node<task::Subtask *>(new task::Subtask(2, 5, 2, ALTERNATIVE, GPU));
  common::Node<task::Subtask *> *v3  = new common::Node<task::Subtask *>(new task::Subtask(3, 5, 2, COMPUTE, GPU));
  common::Node<task::Subtask *> *v4  = new common::Node<task::Subtask *>(new task::Subtask(4, 5, 2, COMPUTE, GPU));
  common::Node<task::Subtask *> *v5  = new common::Node<task::Subtask *>(new task::Subtask(5, 5, 2, COMPUTE, GPU));
  common::Node<task::Subtask *> *v6  = new common::Node<task::Subtask *>(new task::Subtask(6, 5, 2, COMPUTE, GPU));
  common::Node<task::Subtask *> *v7  = new common::Node<task::Subtask *>(new task::Subtask(7, 5, 2, CONDITION, GPU));
  common::Node<task::Subtask *> *v8  = new common::Node<task::Subtask *>(new task::Subtask(8, 5, 2, ALTERNATIVE, GPU));
  common::Node<task::Subtask *> *v9  = new common::Node<task::Subtask *>(new task::Subtask(9, 5, 2, COMPUTE, GPU));
  common::Node<task::Subtask *> *v10 = new common::Node<task::Subtask *>(new task::Subtask(10, 5, 2, COMPUTE, GPU));
  common::Node<task::Subtask *> *v11 = new common::Node<task::Subtask *>(new task::Subtask(11, 5, 2, COMPUTE, GPU));
  common::Node<task::Subtask *> *v12 = new common::Node<task::Subtask *>(new task::Subtask(12, 5, 2, COMPUTE, GPU));

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

  // Instantiation of a task with the subtask list.
  task::Task *tau = new task::Task(1,l);

  // Link every node with each others.
  tau->link_two_subtaks(v1,v2);
  tau->link_two_subtaks(v2,v3);
  tau->link_two_subtaks(v2,v4);
  tau->link_two_subtaks(v4,v5);
  tau->link_two_subtaks(v3,v6);
  tau->link_two_subtaks(v5,v8);
  tau->link_two_subtaks(v8,v9);
  tau->link_two_subtaks(v8,v10);
  tau->link_two_subtaks(v10,v7);
  tau->link_two_subtaks(v9,v7);
  tau->link_two_subtaks(v6,v7);
  tau->link_two_subtaks(v7,v11);
  tau->link_two_subtaks(v7,v12);

  // Draw the graph for debugging.
  tau->to_dot("/tmp/tau.dot");

  // Instantiation of a taskset with the task.
  task::Taskset *taskset = new task::Taskset(1);
  taskset->_list()->add_at_tail(new common::Node<task::Task *>(tau));

  // Instantiation of a new taskset code class
  code_generator::Taskset_code *taskset_code = new code_generator::Taskset_code();

  // Print to stdout the task code set.
  std::cout << taskset_code->print_taskset(taskset) << std::endl;
}
