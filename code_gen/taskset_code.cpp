#include "taskset_code.hpp"


namespace code_generator {

  /** 
   * Constructor  
   */
  Taskset_code::Taskset_code() {
  }

  /** 
   * Destructor  
   */
  Taskset_code::~Taskset_code() {}

  /** 
   * generates  the task set source code in CONSOLE MODE  
   *@param taskset The task set to generate code  
   */
  void  Taskset_code::generate_source(task::Taskset *taskset){
#ifdef DEBUG
    std::cout<<"Calling task set generation in CONSOLE Mode"<<std::endl;
#endif
    print_taskset(taskset, CONSOLE, "");
  }

  /** 
   * generates  the task set source code in TOFILE mode 
   *@param taskset The task set to generate code  
   *@param f_p The path to the output file if TOFILE mode is selected 
   */
  void  Taskset_code::generate_source(task::Taskset *taskset, std::string path ){
#ifdef DEBUG
    std::cout<<"Calling task set generation in TOFILE  Mode"<<std::endl;
#endif
    print_taskset(taskset, TOFILE, path);
  }

  /** 
   * generates  the task set source code 
   *@param taskset The task set to generate code  
   *@param PRINT_MODE Source code generation Output: CONSOLE or TOFILE 
   *@param f_p The path to the output file if TOFILE mode is selected 
   */
  void  Taskset_code::print_taskset(task::Taskset *taskset, int PRINT_MODE, std::string f_p) {
    std::string _h = f_p+"inc/tasks.h";
    std::string _c = f_p+"src/tasks.c";
    std::string _m = f_p+"src/main.c";
    std::ostream* fp_h;
    std::ostream* fp_c;
    std::ostream* mp_c;
    if (PRINT_MODE == TOFILE) 
      {
	fp_h= new std::ofstream(_h);
	fp_c= new std::ofstream(_c);
	mp_c= new std::ofstream(_m);
      }
    else
      {
	fp_h = &std::cout;
	fp_c = &std::cout;
	mp_c = &std::cout;
      }

    *fp_h<< "#ifndef VAR_H\n";
    *fp_h<< "#define VAR_H\n\n";

    *fp_h<< "#define _GNU_SOURCE \n";

    *fp_h<< "#include <sched.h>\n";

    *fp_h<< "#include <stdio.h>\n";
    *fp_h<< "#include <pthread.h>\n";
    *fp_h<< "#include <semaphore.h>\n";
    *fp_h<< "#include <stdlib.h>\n";
    *fp_h<< "#include <affinity.h>\n\n";


    
    *fp_h<< "#include <time_utils.h> \n";
    
    
    *fp_c<< "#include <tasks.h> \n\n";
    *mp_c<< "#include <tasks.h> \n\n";
    
    for (int i = 0; i < taskset->_size(); i++) {
      code_generator::Task_code *task_code = new code_generator::Task_code(taskset->_list()->get(i)->el);
     
      task_code->generate_source(fp_h, fp_c);
    }

    *mp_c<< "int main(void) {\n\n";
    
    *mp_c<< "  int N = "+ std::to_string(taskset->_size())+";\n";

    std::string periods="",deadlines="",thread_names="";
    common::Node<task::Task * > * curr_task = taskset->_list()->head;
    for (int i=0;i<taskset->_size();i++){
      periods+=std::to_string(curr_task->el->_T())+",";
      deadlines+=std::to_string(curr_task->el->_D())+",";
      thread_names+= ""+curr_task->el->_label()+",";
      curr_task = curr_task -> next; 
    }

    *mp_c<< "  pthread_t th["+std::to_string(taskset->_size())+"];";
    *mp_c<< "  int periods["+std::to_string(taskset->_size()+1)+"]={"+periods+"-1}; \n";
    *mp_c<< "  int deadlines["+std::to_string(taskset->_size()+1)+"]={"+deadlines+"-1}; \n";
    *mp_c<< "  void * thread_names["+std::to_string(taskset->_size()+1)+"]={"+thread_names+" NULL}; \n";
    
    *mp_c<< "  struct periodic_data_struct st[N];\n\n";
    *mp_c<< "  for (int i=0; i<N; i++){\n";

    *mp_c<< "    st[i].index = i;\n";
    *mp_c<< "    st[i].period_us = periods[i];\n"; 
    *mp_c<< "    st[i].deadline_us = deadlines[i];\n";
    *mp_c<< "  }\n";

 
    *mp_c<< "  for (int i=0;i<N;i++){ \n";
    *mp_c<< "    pthread_create(&th[i], NULL, thread_names[i], &st[i]);\n";
    *mp_c<< "  } \n ";



    *mp_c<< "  for (int i=0;i<N;i++){ \n";
    *mp_c<< "    pthread_join(th[i], NULL);\n";
    *mp_c<< "  }\n";


    *mp_c<< "\n";
    *mp_c<< "  return 0;\n";
    *mp_c<< "}\n";

    
    *fp_h<< "#endif\n";
    if (fp_c!=&std::cout) {
      delete fp_c;
      delete fp_h;
      delete mp_c;
    }
  }
}
