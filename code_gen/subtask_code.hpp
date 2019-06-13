#ifndef SUB_TASK_CODE_HPP
#define SUB_TASK_CODE_HPP

#include "../task/subtask.hpp"
#include "../common/list.hpp"
#include "../task/buffer.hpp"
#include <string>

#define PROTECT_READ 0
#define PROTECT 0
#define UNPROTECT 1
#define PROTECT_WRITE 0 

// Houssam: Faire l'héritage ? ou pas


namespace code_generator {

  class Subtask_code { 
  private:
    task::Subtask * v;                        /* Sous-tâche courante.           */
    std::string ret_type;                     /* Type de retour de la fonction. */
    std::string label;                        /* Nom de la fonction.            */
    common::List<Subtask_code *> * preds;     /* Liste des prédécesseurs.       */
    common::List<Subtask_code *> * succs;     /* Liste des successeurs.         */
    common::List<std::string> * pre_decs;     /* */
    common::List<std::string> * openings;     /* */
    common::List<std::string> * closings;     /* */
    common::List<std::string> * params;       /* Paramètres de la fonction.     */
    common::List<std::string> * input_semas;  /* Sémaphores de synchronisation pour les prédécesseurs. */
    common::List<std::string> * output_semas; /* Sémaphores de synchronosation pour les successeurs.   */
 
    
  public:
    Subtask_code(task::Subtask * v);
    ~Subtask_code();
    Subtask_code * merge_after(Subtask_code *s);
    void generate_source(common::List<task::Buffer *> * data_read,
			 common::List<task::Buffer *> * data_write,
			 common::List<task::Subtask *> * preds,
			 common::List<task::Subtask *> * succs,
			 common::List<std::string > * semphores,
			 std::ostream* fp_h, std::ostream* fp_c, int alloc);
    
    task::Subtask * _subtask();
    common::List<Subtask_code *> *  _preds();
    common::List<Subtask_code *> *  _succs();
    common::List<std::string> * _pre_decs();
    common::List<std::string> * _openings();
    common::List<std::string> * _closings();
    common::List<std::string> * _params();
    std::string _label();
    void display();
    
    void generate_header(std::ostream* fp_h, std::ostream* fp_c);
    void generate_affinity(std::ostream* fp_h, std::ostream* fp_c, int alloc);
    void generate_wait_sync(std::ostream* fp_h, std::ostream* fp_c,
			    common::List<task::Subtask *> * preds,
			    common::List<std::string > * semaphores);
    void generate_free_sync(std::ostream* fp_h, std::ostream* fp_c,
			    common::List<task::Subtask *> * succs,
			    common::List<std::string > * semaphores);
    void generate_read_buffers(std::ostream* fp_h, std::ostream* fp_c,
			       common::List<task::Buffer *> * data_read);
    void generate_write_buffers(std::ostream* fp_h, std::ostream* fp_c,
				common::List<task::Buffer *> * data_write);
    std::string generate_condition(std::ostream* fp_h, std::ostream* fp_c,
				   common::List<task::Subtask *> * succs,
				   common::List<std::string > * semaphores);
    void generate_cpu_thread(std::ostream* fp_h, std::ostream* fp_c);
    void generate_gpu_kernel_call(std::ostream* fp_h, std::ostream* fp_c);
    void generate_gpu_kernel_code(std::ostream* fp_h, std::ostream* fp_c);
    void generate_mem_copy(std::ostream* fp_h, std::ostream* fp_c);
    void generate_ccondition(std::ostream* fp_h, std::ostream* fp_c,
			     common::List<task::Subtask *> * preds);	
  };
}

#endif
