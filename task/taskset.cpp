#include "taskset.hpp"

#define SORT_UTI_DESC  0
#define SORT_UTI_CROI  1
#define SORT_PREMP_AWARE  2

namespace task{

  /**
   * @return The number of tasks per the current task set 
   */
  int Taskset::_size(){
    return list->size;
  }

  /**
   * @return the list of tasks 
   */
  common::List<Task *> *Taskset::_list(){
    return list;
  }

  /**
   * set the list of tasks
   */
  void Taskset::_list(common::List<Task *> * list){
    this->list = list;
  }

  /** 
   * Adds a task to the current taskset 
   * @param tau The task to add
   */
  void Taskset:: add(Task * tau){
    list->add_at_tail(new common::Node<Task *> (tau));
  }


  /** 
   * removes a task to the current taskset 
   * @param tau The task to remove
   */
  bool  Taskset::remove(Task * tau){
    return list->remove(tau); 
  }



    /** 
   * removes a task to the current taskset 
   * @param tau The task to remove
   */
  void Taskset::merge(Taskset *ts){
    list->merge(ts->_list()); 
  }


  
    /**
   * Calculate the preemption cost for all subtasks having a deadline
   * shorter than d if allocated with the current tasks set
   *
   * @attention The taskset passed here should not contain the current one
   * @param D the subtask deadline
   * @param g_s the Tasks list
   * @return The premption cost
   */
  int Taskset::preemption_cost_shorter_deadlines(int D){
    int max = 0;
    for (int i=0;i<_size();i++){
      Task * curr_tau = list->get(i);      
      for (int j=0;j<curr_tau->_subtasks()->size;j++){
	common::Node<Subtask *> * curr_subtask = curr_tau->_subtasks()->_get(j);
	if (!curr_subtask->empty && curr_subtask->D > D)
	  max=std::max(max, curr_subtask->el->_PC());
      }
    }
    return max;
  }


  Task * Taskset::get(int i){
    return list->get(i);
  }
  
  /**
   * Constructor of the task
   * @param id the ID of the task set
   */

  Taskset::Taskset(int id){
    this->id = id;
    this->list = new common::List<Task *>();
	
  }
  
  /**
   * Initialize a task set with id -1 
   */
  Taskset::Taskset(){
    this->id = -1;
    this->list = new common::List<Task *>();
  }


  /**
   * Destroy the Takset
   */
  // Houssam: Need to be rewritten 
  Taskset::~Taskset(){
  }

  /**
   * Calculate the Least common multiple (LCM) of the 2 given numbers
   * @param a First number
   * @param b Second number
   * @return LCM of a and b
   */
  int Taskset::LCM(int a, int b){
    int x =a;
    int y = b;
    int t;
    while (b != 0) {
      t = b;
      b = a % b;
      a = t;
    }
    return (x*y)/a;
  }

  /**
   * Calculate the hyperperiod, LCM of all periods of the curren
   * task set
   * @return The hyperperiod
   */
  int Taskset::hyperperiod(){
    int hyper = 1;
    for (int i=0; i< list->size ; i++)
      hyper = LCM(hyper,list->get(i)->_T());
    return hyper;
  }
  
  /**
   * Read the task set from  file arg  
   * @param arg : the path to the file
   */
  void Taskset::read(char *arg){
  }

  /**
   * Write  the task set to the file  arg 
   * @param arg : the path to the file
   */
  void Taskset::write(char *arg){
  }

  /**
   * Sort the task list using the using  sort method: METHOD.
   *
   * Sort the task list using the one of the following methods:
   *  - Sort by descending utilisation
   *  - Sort by premption index.
   *
   * @param METHOD The given method (SORT_UTI_DESC or SORT_PREMP_AWARE)
   */
  void Taskset::sort(int METHOD){
    common::List<Task *> * l_t = new common::List<Task *>();
    while (list->size > 0){
      Task * max_tau=list->head->el;
      double max_c;
      switch (METHOD){
      case SORT_UTI_DESC:
	max_c =  max_tau->utilization();
	break;
      case  SORT_PREMP_AWARE:
	max_c = max_tau->preemp_index();
	break;
      default:
	fatal_error(35, "UNKNOW sorting option.. exiting");
      }
    

      for (int j=0;j<list->size;j++){
	double  ex_t;
	switch (METHOD){
	case SORT_UTI_DESC:
	  ex_t =  max_tau->utilization();
	  break;
	case  SORT_PREMP_AWARE:
	  ex_t = max_tau->preemp_index();
	  break;
	default:
	  fatal_error(36, "UNKNOW sorting option.. exiting");
	}
	if ( ex_t> max_c){
	  max_c  = ex_t;
	  max_tau = list->get(j);
	}
      }
      list->remove(max_tau);
      l_t->add_at_tail(new common::Node<Task *  >(max_tau));
    }
    list = l_t;
  }

  /**
   * Calculate the utilization of all the taskset's task.
   * @return The Taskset utilization.
   */
  double Taskset::utilization(){
    double U = 0;
    for (int i=0; i< list->size ; i++)
      U +=  list->get(i)->utilization();
    return U;
  }

  /**
   * Print task set 
   */
  void Taskset::display(){
    for (int i=0; i< list->size ; i++)
      list->_get(i)->display();
  }

  /**
   * Copy task set
   * @return The new task set 
   */
  Taskset* Taskset::copy(){
    Taskset *copy = new Taskset(this->id);
    common::List<Task *> *copylist = new common::List<Task *>();
    for (int i = 0; i < this->list->size; i++) 
      copylist->add(this->list->get(i)->copy());
    return copy;
  }
}
