#include "subtask_code.hpp"

namespace code_generator {

  /**
   * The Subtask_code class constructor.
   * @param label The subtask function label.
   * @param v The subtask.
   */
  Subtask_code::Subtask_code(task::Subtask *v) {
    preds    = new common::List<Subtask_code *> ();
    succs    = new common::List<Subtask_code *> ();
    pre_decs = new common::List<std::string> ();
    openings = new common::List<std::string> ();
    closings = new common::List<std::string> ();
    params   = new common::List<std::string> ();
    this->v = v;
  }

  /**
   * The Subtask_code class destructor.
   */
  Subtask_code::~Subtask_code() {

  }

  /**
   * The current subtask getter.
   * @return The current subtask.
   */
  task::Subtask * Subtask_code::_subtask() {
    return v;
  }

  /**
   * The predecessors list getter.
   * @return The predecessors list.
   */
  common::List<Subtask_code *> *  Subtask_code::_preds() {
    return preds;
  }

  /**
   * The successors list getter.
   * @return The successors list.
   */
  common::List<Subtask_code *> *  Subtask_code::_succs() {
    return succs;
  }

  /**
   * The pre_decs list getter.
   * @return the The pre_decs list.
   */

  common::List<std::string> * Subtask_code::_pre_decs() {
    return pre_decs;
  }

  /**
   * The openings list getter.
   * @return the openings list.
   */

  common::List<std::string> * Subtask_code::_openings() {
    return openings;
  }

  /**
   * The closings list getter.
   * @return the closings list.
   */
  common::List<std::string> * Subtask_code::_closings() {
    return closings;
  }

  /**
   * The params list getter.
   * @return the params list.
   */

  common::List<std::string> * Subtask_code::_params() {
    return params;
  }

  std::string Subtask_code::_label() {
    return label;
  }

  /**
   * This function merges subtasks that are allocated onto
   * the same core
   *
   * @param s The subtask_code to merge with.
   * @return The merged subtask_code.
   */
  // TODO: Not tested for the moment.
  // Should be fixed...

  Subtask_code * Subtask_code::merge_after(Subtask_code *s) {

    Subtask_code * merged = nullptr;

    // If the two subtasks to merge are allocated onto the same merge.

    if (this->v->_TAG() == s->v->_TAG()) {
      merged = new Subtask_code(this->v);

      // Merge pre_decs with s subtask code
      merged->pre_decs = this->_pre_decs()->copy();
      merged->pre_decs->merge(s->_pre_decs());

      // Merge openings with s subtask code
      merged->openings = this->_openings()->copy();
      merged->openings->merge(s->_openings());

      // Merge closings with s subtask code
      merged->closings = this->_closings()->copy();
      merged->closings->merge(s->_closings());

      // Merge params with s subtask code
      merged->params = this->_params()->copy();
      merged->params->merge(s->_params());
    }
    return merged;
  }

  /**
   * This function return the source code of the subtask. It is called at the end
   * of every thing.-
   */
  void Subtask_code::generate_source(common::List<task::Buffer *> * data_read,
				     common::List<task::Buffer *> * data_write,
				     common::List<task::Subtask *> * preds,
				     common::List<task::Subtask *> * succs,
				     common::List<std::string > * semaphores,
				     std::ostream* fp_h, std::ostream* fp_c, int alloc ) {

#ifdef DEBUG
    std::cout<<"************************"<<std::endl;
    v->display();
    std::cout<<"************"<<std::endl;
    preds->display();
    std::cout<<"************"<<std::endl;
    succs->display();
    std::cout<<"************************"<<std::endl;
#endif
  
    *fp_c << "void * " + v->_label() + "(){ \n";
    *fp_h << "void * " + v->_label() + "(); \n";


    // Affinity setting 

    *fp_c <<"  int s; \n";
    *fp_c <<"  cpu_set_t cpuset;\n";
    *fp_c <<"  pthread_t thread;\n";
    *fp_c <<"  thread = pthread_self();\n";
    *fp_c <<"  CPU_ZERO(&cpuset);\n";
    *fp_c <<"  CPU_SET("+std::to_string(alloc)+", &cpuset);\n";
    *fp_c <<"  s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);\n";
    *fp_c <<"  if (s != 0){ \n";
    *fp_c <<"    printf(\" Allocation Error: Unable to allocate "+v->_label()+" to computing unit "+std::to_string(alloc)+", exiting \\n \");\n    exit(-1); \n  } \n";

    
    
    

    
    // Repeted processing
    *fp_c << "  while(1) {\n\n";


    // synchronization 
    if (preds->size == 0)
      {
	std::string sema_name = "ent_"+v->_label()+"_sem"; 
	*fp_c << "    sem_wait(&"+sema_name+");\n";
	semaphores->add_at_tail(new common::Node<std::string>(sema_name));
      }
    else {
      
   
      common::Node<task::Subtask *> * curr_ = preds->head;
      for (int j = 0; j < preds->size; j++){
	std::string sema_name = curr_->el->_label()+"_"+this->v->_label()+"_sem";
	*fp_c << "    sem_wait(&" +sema_name+");\n";
	if (!semaphores->contains_string(sema_name)){
	  semaphores->add_at_tail(new common::Node<std::string>(sema_name));
	}
	curr_=curr_->next;
      }
    }
    *fp_c<<"\n";
    
    // Buffer management
    common::Node<task::Buffer * > * curr_buff = data_read->head;
    for (int i=0;i<data_read->size;i++){
      if (PROTECT_READ==PROTECT){
	*fp_c<<"    pthread_mutex_lock(&"+ curr_buff->el->_mutex_name() +"); \n";
	*fp_c<<"    move_data(";
	if (curr_buff->el->_size()==1)
	  *fp_c<<"&";

	*fp_c<<curr_buff->el->_name()+", sizeof("+curr_buff->el->_type()+")*"+std::to_string(curr_buff->el->_size())+");  /* read operation */ \n";
	*fp_c<<"    pthread_mutex_unlock(&"+ curr_buff->el->_mutex_name() +"); \n";
      }
      else {
	*fp_c<<"    //read operation \n";
	*fp_c<<"    move_data(curr_buff->name), curr_buff->size)\n;";
      }
      curr_buff = curr_buff->next;
    }
    
    // Generating conditions 
    if (v->_type() == CONDITION){
      if (succs->size!=2){
	std::cerr<<"Fatal error: A conditional node should have only two successors"<<std::endl;
	exit(-1);
      }
      *fp_c << "\n int a; \n  if (a>0) ";
      std::string sema_name = this->v->_label()+"_"+succs->get(0)->el->_label()+"_sem"; 
      *fp_c << "    sem_post(&"+sema_name+");\n";
      if (!semaphores->contains_string(sema_name)){
	semaphores->add_at_tail(new common::Node<std::string>(sema_name));
      }
      *fp_c<< "  else \n";
      sema_name = this->v->_label()+"_"+succs->get(1)->el->_label()+"_sem"; 
      *fp_c << "    sem_post(&"+sema_name+");\n";
      if (!semaphores->contains_string(sema_name)){
	semaphores->add_at_tail(new common::Node<std::string>(sema_name));
      }
    }
    else {

      // Houssam : Need to generate also mem copy tasks 
      if (v->_TAG() == GPU) {
	*fp_c << "\n   // this is the GPU KERNEL Call \n";      
	*fp_c << "     "+v->_label() +"_gpu<<<GRID_SIZE, BLOCK_SIZE>>>(/*Kernel params*/);\n";
      }
      else {
      *fp_c << "\n   // Please insert Sub-task   " + v->_label() + "   code here\n";      
      *fp_c << "     printf(\"  " + v->_label() + "  \\n\");\n\n";
      }

      
      
      // Data writting 
      curr_buff = data_write->head;
    
      for (int i=0;i<data_write->size;i++){
	if (PROTECT_WRITE==PROTECT){
	  *fp_c<<"    pthread_mutex_lock(&"+ curr_buff->el->_mutex_name() +"); \n";
	  *fp_c<<"    move_data(";
	  if (curr_buff->el->_size()==1)
	    *fp_c<<"&";

	  *fp_c<<curr_buff->el->_name()+", sizeof("+curr_buff->el->_type()+")*"+std::to_string(curr_buff->el->_size())+");  /* read operation */ \n";
	  *fp_c<<"    pthread_mutex_unlock(&"+ curr_buff->el->_mutex_name() +"); \n";
	}
	else {
	  *fp_c<<"    //write opertion \n";
	  *fp_c<<"    move_data(curr_buff->name), curr_buff->size)\n;";
	}
	curr_buff = curr_buff->next;
      }

      
      // Synchronization for successors
      if (succs->size == 0) {
	std::string sema_name = "ext_"+v->_label()+"_sem"; 
	*fp_c << "    sem_post(&"+sema_name+");\n";
	semaphores->add_at_tail(new common::Node<std::string>(sema_name));
      } else {
	common::Node<task::Subtask *> * curr_ = succs->head;
	for(int i = 0; i < succs->size; i++) {
	  std::string sema_name = this->v->_label()+"_"+curr_->el->_label()+"_sem"; 
	  *fp_c << "    sem_post(&"+sema_name+");\n";
	  if (!semaphores->contains_string(sema_name)){
	    semaphores->add_at_tail(new common::Node<std::string>(sema_name));
	  }
	  curr_ = curr_->next;
	}
      }
    }
    *fp_c << "  }\n}\n\n";
    if (v->_TAG() == GPU){
      *fp_c << "__global__ void "+v->_label()+"_gpu (/* Insert your kernel parameters here */) { \n ";
      *fp_c << "  // you may want to define other indexes using threadIdy, threadIdz \n";
      *fp_c << "  int index= threadIdx.x+ blockIdx.x* blockDim.x; \n";
      *fp_c << "  printf(\" printing from core %d \\n\",index );  \n";
      *fp_c << "  // Insert your GPU code here \n";
      *fp_c << "\n}\n\n";
    }
  }

  /**
   * This function display the current subtask.
   */
  void Subtask_code::display(){
    v->display();
  }
}
