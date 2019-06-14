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
    for (int i = 0; i < this->_list_code()->size; i++) 
      if (_list_code()->get(i)->_subtask() == v)
        return _list_code()->get(i);
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
      
   
    for (int i=0;i<this->task->_subtasks()->size;i++){
      common::Node <task::Subtask *> * curr_ = this->task->_subtasks()->_get(i);
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
    }
    
    //generating the subtasks code for Closing conditions 
  
    for (int i=0;i<cconds->size;i++){
      common::Node<task::Subtask *> * curr_ = cconds->_get(i);
      common::List<task::Subtask *> * preds = task->predecessors(curr_);
      common::List<task::Subtask *> * succs = task->successors(curr_);
      Subtask_code *c = new Subtask_code(curr_->el);
      common::List<task::Buffer *> * data_read  = task->filter_by_src(curr_->el);
      common::List<task::Buffer *> * data_write  = task->filter_by_dst(curr_->el);
      // Houssam : Need to calculate the subtask allocation processor here 
      int alloc = 1;      
      c->generate_source(data_write, data_read,preds,succs,semaphores, fp_h, fp_c,alloc);
    }
    
    *fp_c << "void *"+ task->_label()+"(void * arg){";
    *fp_h << "void *"+ task->_label()+"(void * arg); \n";
  
    common::List <task::Buffer *> * processed_buffers = new common::List <task::Buffer *> () ;
    for (int i=0;i<task->_comms()->size;i++){
      task::Communication * curr_comm = task->_comms()->get(i);
      if (!processed_buffers->contains(curr_comm->_buff()))
	{
	  processed_buffers->add_at_tail(new common::Node<task::Buffer *>(curr_comm->_buff()));
	  *fp_h << curr_comm->_buff()->_type()+" "+curr_comm->_buff()->_name();
	  if (curr_comm->_buff()->_size()>1)
	    *fp_h << "["+std::to_string(curr_comm->_buff()->_size())+"]";
	  *fp_h << ";\n";
	  
	  *fp_h << "pthread_mutex_t  "+ curr_comm->_buff()->_mutex_name()+" ; \n"; 
	}    
    }

    
    // parsing the arguments 
    *fp_c << " \n  struct periodic_data_struct *ps = (struct periodic_data_struct *) arg;\n";
    
    *fp_h << "\n\n // declaring semaphores \n"; 
    
    for (int i=0;i<semaphores->size;i++){
      std::string curr_sema = semaphores->get(i);
      *fp_h<<"sem_t "+curr_sema+";\n";
      *fp_c<<"  sem_init(&"+curr_sema+", 0, 0); \n";
    }

    *fp_c<<"  \n";

    // initializing the mutex to protect shared buffers 
    for (int i=0;i<processed_buffers->size;i++)
      *fp_c<<"  pthread_mutex_init(&"+processed_buffers->get(i)->_mutex_name()+", NULL); \n";

    *fp_h <<"\n";
    // creating the threads of subtasks 
    *fp_c << "\n\n // creating threads of tasks \n"; 

    for (int i=0;i<this->task->_subtasks()->size;i++){
      task::Subtask * curr_ = this->task->_subtasks()->get(i);
      std::string tid = curr_->_label()+"_tid";
      *fp_h << "pthread_t "+tid+";\n";
      *fp_c << "  pthread_create(&"+tid+", NULL, " + curr_->_label() + ",  NULL);\n";
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
    *fp_c<<"\n    // signaling the  source threads to start \n";
    for(int i = 0; i < entries->size; i++) 
      *fp_c << + "    sem_post(&ent_"+entries->get(i)->_label()+"_sem);   \n";

    // Synchronization for sinks
    *fp_c<<"\n    // Waiting for all threads to complete \n";
    
    for(int i = 0; i < exits->size; i++) 
      *fp_c << "    sem_wait(&ext_"+exits->get(i)->_label()+"_sem);   \n";
    // Make the task sleeping until the next period 
    *fp_c << "\n    timespec_add_us(&next, ps->period_us);\n";
    *fp_c << "    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);\n";

    // Unreacheable code 
    *fp_c << "  }\n\n  return NULL;\n}\n\n";
  }


}
