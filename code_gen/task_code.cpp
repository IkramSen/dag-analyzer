#include "task_code.hpp"

namespace code_generator {

  int nb_end_node = 0;

  /**
   * The Task_code class constructor.
   * @param label The task function label.
   */

  Task_code::Task_code(std::string label) {
    preds        = new common::List<Subtask_code *> ();
    succs        = new common::List<Subtask_code *> ();
    pre_decs     = new common::List<std::string> ();
    openings     = new common::List<std::string> ();
    closings     = new common::List<std::string> ();
    params       = new common::List<std::string> ();
    input_semas  = new common::List<std::string> ();
    output_semas = new common::List<std::string> ();
    this->label = label;
    this->ret_type = "void *";
    this->params->add_at_head(new common::Node<std::string>("void * arg"));
    list_code = new common::List<Subtask_code *>();
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
   * @return The associated subtask code.
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
   * This function generate the subtask code of task passed as argument.
   * @param task The task from which to generate the subtask code.
   */

  void Task_code::add_task(task::Task *task) {

    common::Node<task::Subtask *> * curr = task->_subtasks()->head;

    for (int i = 0; i < task->_subtasks()->size; i++) {
      std::string str = "subtask_" + std::to_string(curr->el->_id());
      code_generator::Subtask_code * s_c = new code_generator::Subtask_code(str, curr->el);
      this->_list_code()->add_at_tail(new common::Node <code_generator::Subtask_code *>(s_c));
      curr = curr->next;
    }

    common::List<code_generator::Subtask_code * > * entries_c = new common::List<code_generator::Subtask_code *>();
    common::List<code_generator::Subtask_code * > * exits_c = new common::List<code_generator::Subtask_code *>();
    common::Node<code_generator::Subtask_code * > * curr_ = this->_list_code()->head;

    for (int i = 0; i < this->_list_code()->size; i++) {

      common::Node<task::Subtask *> * n = task->_subtasks()->find_element(curr_->el->_subtask());
      common::List<task::Subtask *> * l_p = task->predecessors(n);
      common::Node<task::Subtask *> * curr_pred = l_p->head;

      if (l_p->size == 0) {
        entries_c->add_at_tail(new common::Node<code_generator::Subtask_code *>(curr_->el));
        this->_input_semas()->add_at_tail(new common::Node<std::string>("sem_post(&task_entry_sem);"));
      }

      for (int j = 0; j < l_p->size; j++) {
        code_generator::Subtask_code * s =  find_subtask_code_subtask(curr_pred->el);
        curr_->el->_preds()->add_at_tail(new common::Node<code_generator::Subtask_code *>(s));
        curr_pred = curr_pred->next;
      }

      l_p = task->successors(task->_subtasks()->find_element(curr_->el->_subtask()));

      if (l_p->size == 0) {
        exits_c->add_at_tail(new common::Node<code_generator::Subtask_code *>(curr_->el));
        if (nb_end_node != 0)
          this->_output_semas()->add_at_tail(new common::Node<std::string>("sem_wait(&task_end_sem);"));
        nb_end_node++;
      }

      curr_pred = l_p->head;

      for (int j = 0; j < l_p->size; j++) {
        code_generator::Subtask_code * s =  find_subtask_code_subtask(curr_pred->el);
        curr_->el->_succs()->add_at_tail(new common::Node<code_generator::Subtask_code *>(s));
        curr_pred = curr_pred ->next;
      }

      curr_ = curr_->next;
    }
  }

  std::string Task_code::print_task() {

    std::string f_c = "";

    common::Node<code_generator::Subtask_code *> * curr_ = list_code->head;

    // Generate all the subtask semaphore.
    curr_ = list_code->head;

    for (int i = 0; i < this->list_code->size; i++) {
      f_c += "sem_t subtask_" + std::to_string(i+1) + "_sem;\n";
      curr_ = curr_-> next;
    }

    f_c += "\n";

    // Add subtask code
    curr_ = list_code->head;
    for (int i = 0; i < this->list_code->size; i++) {
      f_c += curr_->el->print_subtask();
      curr_ = curr_-> next;
    }

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

    f_c += ") { \n\n";

    f_c += "  struct periodic_data_struct *ps = (struct periodic_data_struct *) arg;\n";
    f_c += "  struct timespec next;\n";
    f_c += "  pthread_t tid;\n\n";

    curr_ = list_code->head;
    for (int i = 0; i < this->list_code->size; i++) {
      f_c += "  pthread_create(&tid, NULL, " + curr_->el->_label() + ",  NULL);\n";
      curr_ = curr_->next;
    }

    f_c += "\n";

    f_c += "  clock_gettime(CLOCK_REALTIME, &next);\n";

    // TODO: Set affinity. See affinity.c
    f_c += "  // set_affinity();\n\n";

    f_c += "  while(1) {\n\n";

    f_c += "    sem_init(&task_end_sem, 0, -" + std::to_string(nb_end_node) + ");\n\n";

    // synchronization for preds
    curr = input_semas->head;
    for(int i = 0; i < input_semas->size; i++) {
      f_c += + "    " + curr->el + "\n";
      curr = curr->next;
    }

    curr = openings->head;
    for(int i = 0; i < openings->size; i++) {
      f_c += + "    " + curr->el + "\n";
      curr = curr->next;
    }

    f_c += "\n    // Task " + label + " code here \n";
    f_c += "    printf(\"" + label + "\\n\");\n\n";

    curr = closings->head;
    for(int i = 0; i < closings->size; i++) {
      f_c += + "    " + curr->el + "\n";
      curr = curr->next;
    }

    // Synchronization for successors
    curr = output_semas->head;
    for(int i = 0; i < output_semas->size; i++) {
      f_c += + "    " + curr->el + "\n";
      curr = curr->next;
    }

    f_c += "\n    timespec_add_us(&next, ps->period_us);\n";

    f_c += "\n    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);\n";

    f_c += "  }\n\n  return NULL;\n}\n\n";

    return f_c;
  }
}
