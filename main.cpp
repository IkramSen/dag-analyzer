#include "task/subtask.hpp"
#include "common/list.hpp"
#include "task/task.hpp"
#include "analysis/analysis.hpp"
#include "platform/platform.hpp"

int main(int argc, char ** argv){
  
  task::Taskset *tset = new task::Taskset(5);
  common::List<task::Task *> *list = new common::List<task::Task *>();
  common::Node<task::Subtask *> *v1 = new common::Node<task::Subtask *>( new task::Subtask(1,5,1,COMPUTE,GPU));
  common::Node<task::Subtask *> *v2 = new common::Node<task::Subtask *>( new task::Subtask(2,0,1,CONDITION,CPU));
  common::Node<task::Subtask *> *v2_c = new common::Node<task::Subtask *>( new task::Subtask(22,0,1,CCONDITION,CPU));
  v2_c->el->_silent_subtask(v2->el);
  common::Node<task::Subtask *> *v3 = new common::Node<task::Subtask *>( new task::Subtask(3,10,1,COMPUTE,CPU));
  common::Node<task::Subtask *> *v4 = new common::Node<task::Subtask *>( new task::Subtask(4,10,1,COMPUTE,CPU));
  common::Node<task::Subtask *> *v5 = new common::Node<task::Subtask *>( new task::Subtask(5,10,1,COMPUTE,CPU));
  common::Node<task::Subtask *> *v6 = new common::Node<task::Subtask *>( new task::Subtask(6,0,1,ALTERNATIVE,CPU));
  common::Node<task::Subtask *> *v7 = new common::Node<task::Subtask *>( new task::Subtask(7,0,2,COMPUTE,CPU));
  common::Node<task::Subtask *> *v8 = new common::Node<task::Subtask *>( new task::Subtask(8,0,2,COMPUTE,CPU));

  common::List<task::Subtask *> *l=new common::List<task::Subtask *>();
  l->add_at_head(v1);
  l->add_at_head(v2);
  l->add_at_head(v2_c);
  l->add_at_head(v3);
  l->add_at_head(v5);
  l->add_at_head(v6);
  l->add_at_head(v7);
  l->add_at_head(v8);

  
  task::Task *tau = new task::Task(1,l);
  tau->link_two_subtasks(v1,v2);
  tau->link_two_subtasks(v2,v3);
  tau->link_two_subtasks(v2,v2_c);
  tau->link_two_subtasks(v3,v2_c);
  tau->link_two_subtasks(v2_c,v5);
  tau->link_two_subtasks(v5,v6);
  tau->link_two_subtasks(v6,v7);
  tau->link_two_subtasks(v6,v8);


  tau->to_dot("/tmp/tt.dot");


  
  
}
