#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP
#include "../task/task.hpp"
#include "../task/taskset.hpp"
#include "../platform/platform.hpp"
#include "../common/list.hpp"
#include "analysis_vars.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>


namespace analysis{
        extern task::Taskset* ts;
        extern platform::Platform *platform;
        bool analyse(platform::Platform *archi,task::Taskset* tasks ,int order,int slack,int alloc, int omit);
        bool is_feasible_sequential(int alloc,task::Task* task);
        task::Task* parallelize(int alloc,int omit,task::Task* task);
        bool dbf_test(task::Taskset* tasks);
        task::Taskset *taskset_union(task::Task *task , task::Taskset *ts);
        task::Subtask* omit_remove(task::Task *curr,int omit);
        common::List<platform::Processor*> *sort_engines(common::List<platform::Processor*> *engines, int alloc);
        common::List<platform::Processor *>* select_engine(int TAG);
        task::Subtask * select_preemp_aware(task::Task *tau);
        common::List<platform::Processor *> *_processors();
}
#endif
