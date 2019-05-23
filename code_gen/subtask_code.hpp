#ifndef SUB_TASK_CODE_HPP
#define SUB_TASK_CODE_HPP

#include "../task/subtask.hpp"
#include "../common/list.hpp"
#include <string>

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
    Subtask_code(std::string label, task::Subtask * v);
    ~Subtask_code();
    Subtask_code * merge_after(Subtask_code *s);
    std::string print_subtask();
    task::Subtask * _subtask();
    common::List<Subtask_code *> *  _preds();
    common::List<Subtask_code *> *  _succs();
    common::List<std::string> * _pre_decs();
    common::List<std::string> * _openings();
    common::List<std::string> * _closings();
    common::List<std::string> * _params();
    std::string _label();
    void display();
  };
}

#endif
