#ifndef TASK_HPP
#define TASK_HPP

#include "../common/list.hpp"
#include "subtask.hpp"
#include "../platform/processor.hpp"
#include "taskset.hpp"
#include "../analysis/analysis_vars.hpp"

#include "buffer.hpp"
#include "comm.hpp"

#include <fstream>
#include <math.h>
#include <cmath>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define EXACT_DBF  0
#define BARUAH_APPROX 1
#define NON_PREEMP 2

#define EXACT_PREEMP  0
#define APROX_PREEMP  1
#define EXACT_NPEEMP  2


#define FAIR 0
#define PROP 1

#define GPU 1
#define CPU 2
#define DLA 3
#define PVA 4
#define MEMCPY 5 



namespace platform{
  class Processor;
}

namespace task {

  class Buffer;
  class Communication;
  class Sema_res;
  class Taskset;
  
  class Task {


  private:
    int id;
    int D;
    int T;
    int **graph;
    int TAG;
    std::string label;

    common::List<Subtask *> *subtasks;
    Taskset * concretes;
    Taskset * elems;
    Taskset * taggeds;
    common::List<Communication *> * comms;
    common::List<common::List<Subtask *> *> *paths;

    
    
  public:

    void filter_subtasks_between(common::Node<Subtask *> *v_s,
				 common::Node<Subtask *> *v_d,
				 common::List<Subtask *> *p,
				 common::List<common::List<Subtask *> *>  * pp);
  

    common::List<Subtask *> *  find_first_condition(common::Node<Subtask *> *  v);
    
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
    std::string _label();
    void  _label(std::string);
    
    Taskset * _concretes();
    void _concretes(Taskset *conc);

    Taskset * _elems();
    void _elems(Taskset * elem);

    Taskset * _taggeds();
    void _taggeds(Taskset * taggeds);

    Task *get_tagged_task(int TAG);

    common::List<Subtask *> * _subtasks();
    void _subtasks(common::List<Subtask *> * subtask);

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

    Task * part_task_between(common::Node<Subtask *> * v_s , common::Node<Subtask *> * v_d);
    bool is_linked(common::Node<Subtask *> *v_1, common::Node<Subtask *> *v_2);

    // common use
    common::List<Subtask *> * successors(common::Node<Subtask *> *v);
    common::List<Subtask *> * predecessors(common::Node<Subtask *> *v);
    common::List<Subtask *> * list_entries();
    common::List<Subtask *> * list_exits();
    bool has_predecessors(common::Node<Subtask *> *v);
    bool has_successors(common::Node<Subtask *> *v);
    Task * find_task_by_subtask(Subtask *e, Taskset * ts);

    // Concrete, tagged and elementary generations functions
    Taskset * generate_one(common::Node<Subtask *> *c);
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
    int dbf_exact(int t, Taskset * ts);
    bool is_approximable();
    bool is_elementary();
    int dbf_approxim_baruah(int t,  Taskset  * ts);
    int dbf_exact_non_preemptif(int t, Taskset *ts);
    int dbf(int t, int METHOD, Taskset *ts);

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

    int compute_vertex_pc(common::Node<Subtask  *> * v, Taskset  *gs);
    bool not_maximal_sub_set_head(common::Node<Subtask  *> *v);


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
    Taskset  *generate_one(Subtask *c);
    common::List<Communication *> * _comms();
    void _comms(common::List<Communication *> * comms);
    

    void add_communication(Communication * comm);

    common::List<Buffer *> * filter_by_src(Subtask * src);
    common::List<Buffer *> * filter_by_dst(Subtask * dst);

    common::List<Sema_res *> * construct_if_then_else_sema(common::Node<Subtask *> * v);

    // Houssam: I need to add a function to delete the non important condition closing nodes !! reduces the complexity for elementary  tasks (not urgent) (To do for optimization reasons ) 
    
  };




  
  class Sema_res {
  public: 
    Subtask * t; // the condition node 
    bool left; // its value

    Sema_res(Subtask *t, bool left);
    ~Sema_res();
    void display(); 
  };
}

#endif
