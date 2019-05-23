#include "subtask_code.hpp"

namespace code_generator {

  /**
   * The Subtask_code class constructor.
   * @param label The subtask function label.
   * @param v The subtask.
   */

  Subtask_code::Subtask_code(std::string label, task::Subtask *v) {
    preds    = new common::List<Subtask_code *> ();
    succs    = new common::List<Subtask_code *> ();
    pre_decs = new common::List<std::string> ();
    openings = new common::List<std::string> ();
    closings = new common::List<std::string> ();
    params   = new common::List<std::string> ();
    this->label = label;
    this->ret_type = "void *";
    this->params->add_at_head(new common::Node<std::string>("void * arg"));
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

      merged = new Subtask_code(this->label, this->v);

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
   * of every thing.
   */

  std::string Subtask_code::print_subtask() {

    std::string f_c = "";

    common::Node<std::string> *curr = pre_decs->head;
    for(int i = 0; i < pre_decs->size; i++) {
      f_c += curr->el;
      curr = curr->next;
    }

    f_c += ret_type + " " + label + "(";

    // get the list of predecessors and select DNodes and add them to params
    curr = params->head;
    for(int i = 0; i < params->size; i++) {
      f_c += curr->el;
      curr = curr->next;
    }

    f_c+=") { \n\n";

    // add affinity and real-time () code here

    f_c += "  while(1) {\n\n";

    f_c += "    sem_init(&" + label + "_sem, 0, 0);\n\n";

    // Synchronization for preds
    common::Node<Subtask_code *> * curr_ = preds->head;

    for (int j = 0; j < preds->size; j++)
      f_c += "    sem_wait(&" + label + "_sem);\n";

    if (preds->size == 0)
      f_c += "    sem_wait(&task_entry_sem);\n";

    curr = openings->head;
    for(int i = 0; i < openings->size; i++) {
      f_c += + "    " + curr->el + "\n";
      curr = curr->next;
    }

    f_c += "\n     // Task " + label + " code here\n";
    f_c += "     printf(\"" + label + "\\n\");\n\n";

    curr = closings->head;
    for(int i = 0; i < closings->size; i++) {
      f_c += "    " + curr->el + "\n";
      curr = curr->next;
    }

    // Synchronization for successors
    if (succs->size == 0) {

      f_c += "    sem_post(&task_end_sem);\n";

    } else {

      curr_ = succs->head;
      for(int i = 0; i < succs->size; i++) {
        f_c += "    sem_post(&" + curr_->el->label + "_sem);\n";
        curr_ = curr_->next;
      }
    }

    f_c += "  }\n\n  return NULL;\n}\n\n";

    return f_c;
  }

  /**
   * This function display the current subtask.
   */

  void Subtask_code::display(){
    v->display();
  }
}
