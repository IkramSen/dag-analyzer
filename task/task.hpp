#ifndef TASK_HPP
#define TASK_HPP

#include "../common/list.hpp"
#include "subtask.hpp"
#include "../platform/processor.hpp"
#include "taskset.hpp"
#include "../analysis/analysis_vars.hpp"

#include <fstream>
#include <math.h>
#include <cmath>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define EXACT_DBF  0
#define BARUAH_APPROX 1
#define NON_PREEMP 2

#define FAIR 0
#define PROP 1

#define GPU 1
#define CPU 2
#define DLA 3
#define PVA 4

namespace platform{
  class Processor;
}

namespace task {

  class Task {


  private:
    int id;
    int D;
    int T;
    int **graph;
    int TAG;

    common::List<Subtask *> *communications;

    common::List<Subtask *> *subtasks;
    common::List<Task *> * concretes;
    common::List<Task *> * elems;
    common::List<Task *> * taggeds;

    common::List<common::List<Subtask *> *> *paths;

  
      
  public:

    
    Task * copy_partial(int id);
    Task * copy_partial();
    void link_task_after_subtask(Task * tau,Subtask * s );
    
    Task(int id, common::List<Subtask*> *l);
    ~Task();
    bool link_two_subtasks(common::Node<Subtask *> *v1, common::Node<Subtask *> *v2);

    // functions used by the grammar
    void add_subtask(Subtask *s);
    void link_new_entry(Subtask * s);
    void link_new_exit(Subtask *s);
    void link_task_after(Task *);
    void merge_task(Task *);
    int _size();

    common::List<Task *> * _concretes();
    void _concretes(common::List<Task *> *conc);

    common::List<Task *> * _elems();
    void _elems(common::List<Task *> * elem);

    common::List<Task *> * _taggeds();
    void _taggeds(common::List<Task *> * taggeds);

    Task *get_tagged_task(int TAG);

    common::List<Subtask *> * _subtasks();
    void _subtasks(common::List<Subtask *> * subtask);

    common::List<Subtask *> * _communications();
    void _communications(common::List<Subtask *> * com);

    common::List<common::List<Subtask *> *> * _paths();
    void _paths(common::List<common::List<Subtask *> *> * paths);

    int **_graph();
    void _graph(int **g);

    void _tag(int TAG);
    int _tag();

    int _T();
    void _T(int period);

    int _D();
    void _D(int deadline);


    // common use
    common::List<Subtask *> * successors(common::Node<Subtask *> *v);
    common::List<Subtask *> * predecessors(common::Node<Subtask *> *v);
    common::List<Subtask *> * list_entries();
    common::List<Subtask *> * list_exits();
    bool has_predecessors(common::Node<Subtask *> *v);
    bool has_successors(common::Node<Subtask *> *v);
    Task * find_task_by_subtask(Subtask *e, common::List<Task *> * ts);

    // Concrete, tagged and elementary generations functions
    common::List<Task *> * generate_one(common::Node<Subtask *> *c);
    void generate_all_conc_tag_el(int type);
    common::List<Subtask *> * children(common::Node<Subtask *> *v);
    void _children(common::Node<Subtask *> *v, common::List<Subtask *> * l);
    common::List<Subtask *> * ancetors(common::Node<Subtask  *> *v);
    void _ancetors(common::Node<Subtask *> *v, common::List<Subtask * > * l);
    void generate_tagged();
    bool sort_concretes(int order, common::List<int> *tag);
    bool sort_concretes_partial();
    bool sort_concretes_relation(common::List<int> *tags);
    // analysis functions
    int dbf_exact(int t, common::List<Task *> * ts);
    bool is_approximable();
    bool is_elementary();
    int dbf_approxim_baruah(int t,  common::List<Task *> * ts);
    int dbf_exact_non_preemptif(int t, common::List<Task *> *ts);
    int dbf(int t, int METHOD, common::List<Task *> *ts);

    //deadline assignment functions
    bool deadline_single_task(int METHOD);
    void fair_assignment(common::List<Subtask *> *curr_path,int sl);
    void prop_assignment(common::List<Subtask *> *curr_path,int sl);

    void update_deadline(int new_D,Subtask * to_find);
    int compute_slack(int D ,common::List<Subtask *> *l );
    int compute_contributors(common::List<Subtask *> *l);
    int compute_contributing_charge(common::List<Subtask *> *l);
    bool order_paths();
    bool generate_paths();
    void generate_single_path(common::Node<Subtask *> *v, common::List<Subtask *> *p);

    double preemp_index();

    int compute_vertex_pc(common::Node<Subtask  *> * v, common::List<Task *>  *gs);
    bool not_maximal_sub_set_head(common::Node<Subtask  *> *v);
    int preemption_cost_shorter_deadlines(int D,  common::List<Task *> *g_s);

    common::List<Subtask *> * ancetors(Subtask *v);
    void _ancetors(Subtask *v, common::List<Subtask *> * l);

    void extract_task(int tag);
    int path_exec_time(common::List<Subtask *> * L);
    double utilization();
    int exec_time();
    int volume();
    Task * copy();
    common::List<Subtask *> * children(Subtask *v);
    void _children(Subtask *v, common::List<Subtask *> * l);
    bool to_dot(std::string );
    void display();
    common::List<Task *> *generate_one(Subtask *c);
  };
}

#endif
