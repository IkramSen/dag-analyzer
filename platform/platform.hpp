#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "../common/list.hpp"
#include "processor.hpp"
namespace platform{
  class Platform{
  private:
    common::List<platform::Processor *> *engines;
    int cost;    

  public:
    Platform * copy();
    void _engines(common::List<platform::Processor *> *engines);
    common::List<platform::Processor *> * _engines();
    bool order_processors();
    Processor * get(int i);
    int nb_proc_tag(int tag);
    common::List<int> *list_tag();
    int _size(); 
    Processor * find_processor(int id);
    void print_alloc();
    bool check_utilization();
    int _cost();
    void _cost(int cost);
    platform::Platform * Optimal_solution(common::List<platform::Platform *> * sols, int *deadlines, int nb);
    int compute_cost(int *deadlines, int nb);
    void eliminer_zero_proc(common::List<platform::Platform *> * sols);
    platform::Platform * Optimal_solution_amelior(common::List<platform::Platform *> * sols, int *deadlines, int nb);
    int compare_Qis( common::List<int > * Q_other, common::List<int > * Qi_Opt);
  };
}


#endif
