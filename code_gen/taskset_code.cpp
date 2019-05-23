#include "taskset_code.hpp"

namespace code_generator {

    Taskset_code::Taskset_code() {}
    Taskset_code::~Taskset_code() {}
    std::string Taskset_code::print_taskset(task::Taskset *taskset) {
      
        std::string f_c = "";
        f_c += "#include <stdio.h>\n";
        f_c += "#include <pthread.h>\n";
        f_c += "#include <semaphore.h>\n";
        f_c += "#include <time_utils.h>\n";
        f_c += "#include <affinity.h>\n\n";

        f_c += "sem_t task_entry_sem;\n";
        f_c += "sem_t task_end_sem;\n\n";

        for (int i = 0; i < taskset->_size(); i++) {
            code_generator::Task_code *task_code = new code_generator::Task_code("task_" + std::to_string(i));
            task_code->add_task(taskset->_list()->get(i)->el);
            f_c += task_code->print_task();
        }

        f_c += "int main(void) {\n\n";
        f_c += "  struct periodic_data_struct st;\n";
        f_c += "  pthread_t th[" + std::to_string(taskset->_size()) + "];\n";
        f_c += "  st.index = 0;\n";
        f_c += "  st.period_us = 300000;\n";
        f_c += "  st.wcet_sim = 3000000;\n";
        f_c += "  st.ndlinemiss = 2;\n\n";

        for (int i = 0; i < taskset->_size(); i++)
            f_c += "  pthread_create(&th[" + std::to_string(i) + "], NULL, task_" + std::to_string(i) + ", &st);\n";

        for (int i = 0; i < taskset->_size(); i++)
            f_c += "  pthread_join(th[" + std::to_string(i) + "], NULL);\n";

        f_c += "\n";

        f_c += "  return 0;\n";
        f_c += "}\n";

        return f_c;
    }
}
