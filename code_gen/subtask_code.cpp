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
   * Generates the subtask code prototype for .c and .h files 
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   */
  void Subtask_code::generate_header( std::ostream* fp_h, std::ostream* fp_c){
    *fp_c << "void * " + v->_label() + "(){ \n";
    *fp_h << "void * " + v->_label() + "(); \n";
  }

  /** 
   * Generates the subtask affinity code in the  .c file
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   * @param alloc The index for the the processor where the task is allocated 
   */
  void Subtask_code::generate_affinity( std::ostream* fp_h, std::ostream* fp_c, int alloc){
    *fp_c <<"  int s; \n";
    *fp_c <<"  cpu_set_t cpuset;\n";
    *fp_c <<"  pthread_t thread;\n";
    *fp_c <<"  thread = pthread_self();\n";
    *fp_c <<"  CPU_ZERO(&cpuset);\n";
    *fp_c <<"  CPU_SET("+std::to_string(alloc)+", &cpuset);\n";
    *fp_c <<"  s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);\n";
    *fp_c <<"  if (s != 0){ \n";
    *fp_c <<"    printf(\" Allocation Error: Unable to allocate"+v->_label()+" to computing unit "+std::to_string(alloc)+", exiting \\n \");\n    exit(-1); \n  } \n";
    
  }

   /** 
   * Generates the subtask wait semaphores, therefore the task waits for its predecessors 
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   * @param preds The list of the subtask predecessors 
   * @param semaphores The list of the declared semaphores/to delcare 
   */
  void Subtask_code::generate_wait_sync(std::ostream* fp_h, std::ostream* fp_c,
					common::List<task::Subtask *> * preds,
					common::List<std::string > * semaphores){
    if (preds->size == 0)
      {
	std::string sema_name = "ent_"+v->_label()+"_sem"; 
	*fp_c << "    sem_wait(&"+sema_name+");\n";
	semaphores->add_at_tail(new common::Node<std::string>(sema_name));
      }
    else {

      for (int j = 0; j < preds->size; j++){
	std::string sema_name = preds->get(j)->_label()+"_"+this->v->_label()+"_sem";
	*fp_c << "    sem_wait(&" +sema_name+");\n";
	if (!semaphores->contains_string(sema_name)){
	  semaphores->add_at_tail(new common::Node<std::string>(sema_name));
	}

      }
    }
  }

   /** 
   * Generates the subtask freeing (post) semaphores, therefore the task frees its succesors to execute 
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   * @param succs  The list of the subtask successors  
   * @param semaphores The list of the declared semaphores/to delcare 
   */
  void Subtask_code::generate_free_sync(std::ostream* fp_h, std::ostream* fp_c,
					common::List<task::Subtask *> * succs,
					common::List<std::string > * semaphores){
      if (succs->size == 0) {
	std::string sema_name = "ext_"+v->_label()+"_sem"; 
	*fp_c << "    sem_post(&"+sema_name+");\n";
	semaphores->add_at_tail(new common::Node<std::string>(sema_name));
      } else {
	for(int i = 0; i < succs->size; i++) {
	  std::string sema_name = this->v->_label()+"_"+succs->get(i)->_label()+"_sem"; 
	  *fp_c << "    sem_post(&"+sema_name+");\n";
	  if (!semaphores->contains_string(sema_name)){
	    semaphores->add_at_tail(new common::Node<std::string>(sema_name));
	  }

	}
      }
  }


  /** 
   * Generates the buffers the subtask should load in an AER/PREM Fashion 
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   * @param  data_read  The list of the buffers to read 
   */
  void Subtask_code::generate_read_buffers(std::ostream* fp_h, std::ostream* fp_c,
					   common::List<task::Buffer *> * data_read){
   
    for (int i=0;i<data_read->size;i++){
      task::Buffer * curr_buff = data_read->get(i);
      if (PROTECT_READ==PROTECT){
	*fp_c<<"    pthread_mutex_lock(&"+ curr_buff->_mutex_name() +"); \n";
	*fp_c<<"    move_data(";
	if (curr_buff->_size()==1)
	  *fp_c<<"&";

	*fp_c<<curr_buff->_name()+", sizeof("+curr_buff->_type()+")*"+std::to_string(curr_buff->_size())+");  /* read operation */ \n";
	*fp_c<<"    pthread_mutex_unlock(&"+ curr_buff->_mutex_name() +"); \n";
      }
      else {
	*fp_c<<"    //read operation \n";
	*fp_c<<"    move_data(curr_buff->name), curr_buff->size)\n;";
      }
    }
  }

    /** 
   * Generates the buffers the subtask should load in an AER/PREM Fashion 
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   * @param  data_write  The list of the buffers to write  
   */
  void Subtask_code::generate_write_buffers(std::ostream* fp_h, std::ostream* fp_c,
					    common::List<task::Buffer *> * data_write){
    
    for (int i=0;i<data_write->size;i++){
      task::Buffer * curr_buff = data_write->get(i);
      if (PROTECT_WRITE==PROTECT){
	*fp_c<<"    pthread_mutex_lock(&"+ curr_buff->_mutex_name() +"); \n";
	*fp_c<<"    move_data(";
	if (curr_buff->_size()==1)
	  *fp_c<<"&";
	*fp_c<<curr_buff->_name()+", sizeof("+curr_buff->_type()+")*"+std::to_string(curr_buff->_size())+");  /* read operation */ \n";
	*fp_c<<"    pthread_mutex_unlock(&"+ curr_buff->_mutex_name() +"); \n";
      }
      else {
	*fp_c<<"    //write opertion \n";
	*fp_c<<"    move_data(curr_buff->name), curr_buff->size)\n;";
      }
     
    }
  }

  

  /** 
   * Generate  the conditional node code
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   */ 
  std::string  Subtask_code::generate_condition(std::ostream* fp_h, std::ostream* fp_c,
					common::List<task::Subtask *> * succs,
					common::List<std::string > * semaphores){

    if (succs->size!=2)
      fatal_error(37," A conditional node should have only two successors");
    std::string condition_name = this->v->_label()+"_c";
    std::string to_ret = "int "+condition_name+"=10;\n";
    *fp_c <<"    "<< condition_name+"=random_between(-10,10);\n";
    *fp_c << "\n \n    if ("+condition_name+">0) { \n";
    std::string sema_name = this->v->_label()+"_"+succs->get(0)->_label()+"_sem";
    v->_sema_left(sema_name);
    *fp_c << "      sem_post(&"+sema_name+");\n  }\n";
    if (!semaphores->contains_string(sema_name)){
      semaphores->add_at_tail(new common::Node<std::string>(sema_name));
    }
    *fp_c<< "    else{ \n";
    sema_name = this->v->_label()+"_"+succs->get(1)->_label()+"_sem";
    v->_sema_right(sema_name);
    *fp_c << "      sem_post(&"+sema_name+");\n  }\n";
    std::string c_sema_name = v->_label()+"_closing_sem";
    semaphores->add_at_tail(new common::Node<std::string >(c_sema_name));
    *fp_c << "    sem_post(&"+c_sema_name+"); \n ";
   
    if (!semaphores->contains_string(sema_name)){
      semaphores->add_at_tail(new common::Node<std::string>(sema_name));
    }
    return to_ret;
  }

  /** 
   * Generate  the CPU code
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   */ 
  void Subtask_code::generate_cpu_thread(std::ostream* fp_h, std::ostream* fp_c){
    *fp_c << "    // Please insert Sub-task   " + v->_label() + "   code here\n";      
    *fp_c << "    printf(\"  " + v->_label() + "  \\n\");\n\n";      
  }

  /** 
   * Generate  the GPU kernel call inside a cpu thread
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   */ 
  void Subtask_code::generate_gpu_kernel_call(std::ostream* fp_h, std::ostream* fp_c){
    *fp_c << "\n   // this is the GPU KERNEL Call \n";      
    *fp_c << "     "+v->_label() +"_gpu<<<GRID_SIZE, BLOCK_SIZE>>>(/*Kernel params*/);\n";
  }

  /** 
   * Generate  the GPU kernel code
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   */ 
  void Subtask_code::generate_gpu_kernel_code(std::ostream* fp_h, std::ostream* fp_c){
    *fp_c << "__global__ void "+v->_label()+"_gpu (/* Insert your kernel parameters here */) { \n ";
    *fp_c << "  // you may want to define other indexes using threadIdy, threadIdz \n";
    *fp_c << "  int index= threadIdx.x+ blockIdx.x* blockDim.x; \n";
    *fp_c << "  printf(\" printing from core %d \\n\",index );  \n";
    *fp_c << "  // Insert your GPU code here \n";
    *fp_c << "\n}\n\n";
  }

  // Houssam : Needs to be written
  /** 
   * Generate  the memory copy operation between  GPU and CPU 
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   */ 
  void Subtask_code::generate_mem_copy(std::ostream* fp_h, std::ostream* fp_c){
  }
  
  /** 
   * Generate  the semaphores for closing if-then-else structures 
   * @param fp_h The streaming writting pointer of the header code 
   * @param fp_c The streaming writting pointer of the source code
   */ 
  void 	Subtask_code::generate_ccondition(std::ostream* fp_h, std::ostream* fp_c,
					  common::List<task::Subtask *> * preds){

    if (preds->size!=2)
      fatal_error(38, "A closing conditional node should have only two predecessors");
    *fp_c<< "  sem_wait(&"+v->_silent_subtask()->_label()+"_closing_sem);\n";
    std::string condition_name = v->_silent_subtask()->_label()+"_c";
    *fp_c << "  if ("+condition_name+">0)\n";
    *fp_c << "    sem_wait(&"+preds->get(0)->_label()+"_"+v->_label()+"_sem);\n";
    *fp_c<<  "  else {\n";
    *fp_c << "    sem_wait(&"+preds->get(1)->_label()+"_"+v->_label()+"_sem); \n  } \n";
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
    if (v->_type()==CONDITION)
      *fp_c << "int "+v->_label()+"_c;\n";

    generate_header( fp_h, fp_c);
    generate_affinity( fp_h, fp_c, alloc);
    // Repeted processing
    *fp_c << "  while(1) {\n\n";
    if (v->_type()==CCONDITION){
      generate_ccondition(fp_h, fp_c,preds);
    } else {
      generate_wait_sync(fp_h, fp_c, preds,semaphores);
    *fp_c<<"\n";
    generate_read_buffers(fp_h, fp_c,data_read);
    }
    // Generating current thread Body
    switch (v->_type())
      {
      case CONDITION:
	generate_condition(fp_h, fp_c, succs,semaphores);
	break;
      case CCONDITION:
	break;
      case COMPUTE:
	switch (v->_TAG())
	  {
	  case CPU:
	    generate_cpu_thread(fp_h, fp_c);
	    break;
	  case GPU:	   
	    generate_gpu_kernel_call(fp_h, fp_c);
	    break;
	  case MEMCPY:
	    generate_mem_copy(fp_h, fp_c);
	    break;	
	  default:
	    fatal_error(40,"Unsupported TAG type, exiting ...");
	  }
	break;
      default:
	fatal_error(39,"Unsupported node type, exiting ...");
      }
    generate_write_buffers(fp_h, fp_c, data_write);
    if (v->_type()!=CONDITION)
      generate_free_sync(fp_h, fp_c, succs,  semaphores);
    
    // While loop closing and thread closing 
    *fp_c << "  }\n}\n\n";
    
    // Generate the gpu kernel source code 
    if (v->_TAG() == GPU)
      generate_gpu_kernel_code(fp_h, fp_c);    
  }

  /**
   * This function display the current subtask.
   */
  void Subtask_code::display(){
    v->display();
  }
}
