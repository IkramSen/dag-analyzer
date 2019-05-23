#ifndef TASK_CODE_HPP
#define TASK_CODE_HPP

#include "subtask_code.hpp"
#include "../task/task.hpp"

namespace code_generator {

  class Task_code {

  private:
    task::Task * task;                         /* Tâche courante.                */
    std::string ret_type;                      /* Type de retour de la fonction. */
    std::string label;                         /* Nom de la fonction.            */
    common::List<Subtask_code *> * preds;      /* Liste des prédécesseurs.       */
    common::List<Subtask_code *> * succs;      /* Liste des successeurs.         */
    common::List<std::string> * pre_decs;      /* */
    common::List<std::string> * openings;      /* */
    common::List<std::string> * closings;      /* */
    common::List<std::string> * params;        /* Paramètres de la fonction.     */
    common::List<std::string> * input_semas;   /* Sémaphores de synchronisation pour les prédécesseurs. */
    common::List<std::string> * output_semas;  /* Sémaphores de synchronosation pour les successeurs.   */
    common::List<Subtask_code * > * list_code; /* Une list de code des sous-tâches. */
    Subtask_code * find_subtask_code_subtask(task::Subtask  *v);

  public:
    Task_code(std::string label);
    ~Task_code();
    Task_code * merge();
    std::string print_task();
    common::List<Subtask_code *> * _preds();
    common::List<Subtask_code *> *_succs();
    common::List<std::string> * _pred_decs();
    common::List<std::string> * _openings();
    common::List<std::string> * _closings();
    common::List<std::string> * _params();
    common::List<std::string> * _input_semas();
    common::List<std::string> * _output_semas();
    common::List<Subtask_code * > * _list_code();
    void add_task(task::Task *task);
  };
}

#endif
