#include "task_code.hpp"

namespace code_generator {

  int nb_end_node = 0;


  /**
   * The Task_code class constructor.
   * @param label The task function label.
   */
  Task_code::Task_code(task::Task *tau) {
    preds        = new common::List<Subtask_code *> ();
    succs        = new common::List<Subtask_code *> ();
    pre_decs     = new common::List<std::string> ();
    openings     = new common::List<std::string> ();
    closings     = new common::List<std::string> ();
    params       = new common::List<std::string> ();
    input_semas  = new common::List<std::string> ();
    output_semas = new common::List<std::string> ();
    semaphores = new common::List<std::string>(); 
    this->ret_type = "void *";
    this->params->add_at_head(new common::Node<std::string>("void * arg"));
    list_code = new common::List<Subtask_code *>();
    this->task = tau;
  }

  /** 
   * Getter of semaphores 
   */ 
  common::List<std::string> * Task_code:: _semaphores(){
    return semaphores;
  }
  
  /**
   * The Task_code class destructor.
   */
  Task_code::~Task_code() { }

  /**
   * The predecessors list getter.
   * @return The predecessors list.
   */
  common::List<Subtask_code *> * Task_code::_preds() {
    return preds;
  }

  /**
   * The successors list getter.
   * @return The successors list.
   */
  common::List<Subtask_code *> * Task_code::_succs() {
    return succs;
  }

  /**
   * The pre_decs list getter.
   * @return the The pre_decs list.
   */

  common::List<std::string> * Task_code::_pred_decs() {
    return pre_decs;
  }

  /**
   * The openings list getter.
   * @return the openings list.
   */
  common::List<std::string> * Task_code::_openings() {
    return openings;
  }

  /**
   * The closings list getter.
   * @return the closings list.
   */
  common::List<std::string> * Task_code::_closings() {
    return closings;
  }

  /**
   * The params list getter.
   * @return the params list.
   */
  common::List<std::string> * Task_code::_params() {
    return params;
  }

  /**
   * The input semaphore list getter.
   * @return The input semaphore list.
   */

  common::List<std::string> * Task_code::_input_semas() {
    return input_semas;
  }

  /**
   * The output semaphore list getter.
   * @return The output semaphore list.
   */
  common::List<std::string> * Task_code::_output_semas() {
    return output_semas;
  }

  /**
   * The list code getter.
   * @return The list code.
   */
  common::List<Subtask_code * > * Task_code::_list_code() {
    return list_code;
  }

  /**
   * This function find the subtask code associated to the subtask
   * passed as argument.
   * @param v The subtask from which to find the associated subtask code.
   * @return The associated subtask code, if not found, it returns NULL
   */
  Subtask_code * Task_code::find_subtask_code_subtask(task::Subtask  *v) {
    common::Node<code_generator::Subtask_code * > * curr = this->_list_code()->head;
    for (int i = 0; i < this->_list_code()->size; i++) {
      if (curr->el->_subtask() == v)
        return curr->el;
      curr = curr->next;
    }
    return NULL;
  }

  /** 
      The goal is to generate the task source code and initiate the sub-tasks source code 
      @return A string of the sub-task source codes 

   */
  void Task_code::generate_source(std::ostream* fp_h, std::ostream* fp_c) {
    *fp_h << "\n";

    // generating source subtasks code
    common::List<task::Subtask *> * cconds = new common::List<task::Subtask *> ();
      
    common::Node <task::Subtask *> * curr_ = this->task->_subtasks()->head;
    for (int i=0;i<this->task->_subtasks()->size;i++){
      if (curr_->el->_type()!=CCONDITION){
      common::List<task::Subtask *> * preds = task->predecessors(curr_);
      common::List<task::Subtask *> * succs = task->successors(curr_);
      Subtask_code *c = new Subtask_code(curr_->el);
      common::List<task::Buffer *> * data_read  = task->filter_by_src(curr_->el);
      common::List<task::Buffer *> * data_write  = task->filter_by_dst(curr_->el);
      // Houssam : Need to calculate the subtask allocation processor here 
      int alloc = 1;      
      c->generate_source(data_write, data_read,preds,succs,semaphores, fp_h, fp_c,alloc);
      }
      else
	cconds->add_at_tail(new common::Node<task::Subtask *>(curr_,SAVE));
      curr_ = curr_->next;
    }
    
    //generating the subtasks code for Closing conditions 
    curr_ = cconds->head;
    for (int i=0;i<cconds->size;i++){
      common::List<task::Subtask *> * preds = task->predecessors(curr_);
      common::List<task::Subtask *> * succs = task->successors(curr_);
      Subtask_code *c = new Subtask_code(curr_->el);
      common::List<task::Buffer *> * data_read  = task->filter_by_src(curr_->el);
      common::List<task::Buffer *> * data_write  = task->filter_by_dst(curr_->el);
      // Houssam : Need to calculate the subtask allocation processor here 
      int alloc = 1;      
      c->generate_source(data_write, data_read,preds,succs,semaphores, fp_h, fp_c,alloc);
      curr_ = curr_->next;
    }


    

    
    

    *fp_c << "void *"+ task->_label()+"(void * arg){";
    *fp_h << "void *"+ task->_label()+"(void * arg); \n";

    common::Node <task::Communication *> * curr_comm = task->_comms()->head;
    common::List <task::Buffer *> * processed_buffers = new common::List <task::Buffer *> () ;
    
    for (int i=0;i<task->_comms()->size;i++){
      if (!processed_buffers->contains(curr_comm->el->_buff()))
	{
	  
	  processed_buffers->add_at_tail(new common::Node<task::Buffer *>(curr_comm->el->_buff()));
	  *fp_h << curr_comm->el->_buff()->_type()+" "+curr_comm->el->_buff()->_name();
	  if (curr_comm->el->_buff()->_size()>1)
	    *fp_h << "["+std::to_string(curr_comm->el->_buff()->_size())+"]";
	  *fp_h << ";\n";
	  
	  *fp_h << "pthread_mutex_t  "+ curr_comm->el->_buff()->_mutex_name()+" ; \n"; 
	}
      curr_comm = curr_comm->next;
    }

    
    // parsing the arguments 
    *fp_c << " \n  struct periodic_data_struct *ps = (struct periodic_data_struct *) arg;\n";
    
    *fp_h << "\n\n // declaring semaphores \n"; 
    common::Node<std::string> * curr_sema = semaphores->head;
    for (int i=0;i<semaphores->size;i++){
      *fp_h<<"sem_t "+curr_sema->el+";\n";
      *fp_c<<"  sem_init(&"+curr_sema->el+", 0, 0); \n";
      curr_sema= curr_sema->next;
    }



    *fp_c<<"  \n";

    // initializing the mutex to protect shared buffers 
    common::Node<task::Buffer *> * curr_buff = processed_buffers->head;
    for (int i=0;i<processed_buffers->size;i++){
      *fp_c<<"  pthread_mutex_init(&"+curr_buff->el->_mutex_name()+", NULL); \n";
      curr_buff= curr_buff->next;
    }

    
    

    *fp_h <<"\n";
    // creating the threads of subtasks 
    *fp_c << "\n\n // creating threads of tasks \n"; 
    curr_ = this->task->_subtasks()->head;
    for (int i=0;i<this->task->_subtasks()->size;i++){
      std::string tid = curr_->el->_label()+"_tid";
      *fp_h << "pthread_t "+tid+";\n";
      *fp_c << "  pthread_create(&"+tid+", NULL, " + curr_->el->_label() + ",  NULL);\n";
      curr_ = curr_->next;
    }


    *fp_c << "\n";
    *fp_c << "  struct timespec next;\n";

    // Houssam: May be  I need to synchronize all tasks at this level
    *fp_c <<"  // Synchronize all tasks  here \n ";
  
    *fp_c << "  while(1) {\n\n";
    *fp_c << "    clock_gettime(CLOCK_REALTIME, &next);\n";

    // synchronization for source nodes
    common::List<task::Subtask *> * entries = this->task->list_entries();
    common::List<task::Subtask *> * exits = this->task->list_exits();
    curr_ = entries->head;
    *fp_c<<"\n    // signaling the  source threads to start \n";
    for(int i = 0; i < entries->size; i++) {
      *fp_c << + "    sem_post(&ent_"+curr_->el->_label()+"_sem);   \n";
      curr_ = curr_->next;
    }
    // Synchronization for sinks
    *fp_c<<"\n    // Waiting for all threads to complete \n";
    curr_ = exits->head;
    for(int i = 0; i < exits->size; i++) {
      *fp_c << "    sem_wait(&ext_"+curr_->el->_label()+"_sem);   \n";
      curr_ = curr_->next;
    }
    
    // Make the task sleeping until the next period 
    *fp_c << "\n    timespec_add_us(&next, ps->period_us);\n";
    *fp_c << "    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);\n";

    // Unreacheable code 
    *fp_c << "  }\n\n  return NULL;\n}\n\n";
  }


  // void check_sema(task::Subtask * src, task::Subtask *dst, common::List<task::Subtask *> *l_1, common::List<boolean> *l_2 ){

  //   task::Task * l = generate_task_between(src,dst);
  //   task::Subtask *s = get_first_condition_starting from_src(l);
  //   if (s!=NULL) {
  //     common::List<Subtask *>  * succ_1 = get_successors_of(successors(s)[0]);
  //     common::List<Subtask *>  * succ_2 = get_successors_of(successors(s)[1]);

  //     if (succ_1->contains(dst) && succ_2->contains(dst))
  // 	return ;

  //     if (succ_1->contains(dst))
  // 	{
  // 	  l_1->add_at_tail(s);
  // 	  l_2->add_at_tail(true);
  // 	  check_sema(succ_1,dst,l_1,l_2);
  // 	}
  //     else {
  // 	l_1->add_at_tail(s);
  // 	l_2->add_at_tail(false);
  // 	check_sema(succ_2,dst,l_1,l_2);
  //     }
  //   }
  // }
}
