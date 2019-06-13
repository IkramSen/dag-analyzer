#include "task.hpp"


//#define DEBUG


//using namespace common;

namespace task {

  


  /** 
   * Compute the first conditions in the successors of the the input sub-task
   * The input subtask has to be unique 
   * @param v : The begining subtask 
  * @return The list of the first condition nodes that directly follow from the input vertex 
   */
  common::List<Subtask *> *  Task::find_first_condition(common::Node<Subtask *> *  v){
 
    common::List<Subtask * > * succs = successors(v);
    common::List<Subtask * > * to_ret = new common::List<Subtask *>();
    common::Node <Subtask *> * curr = succs->head;

    for (int i=0;i<succs->size;i++){
      if (curr->el->_type() == CONDITION){
  	// Houssam : I need to write this code recrusiblt
  	to_ret->add_at_tail(new common::Node<Subtask *>(curr,SAVE));
      } else {
	to_ret->merge(find_first_condition(curr)); 
      }
      curr = curr->next;
    }    
    return to_ret;
  }


  
  /**  Houssam :  I need to write this funtion
   */
  // Need tp checl multiple if conditions 
  common::List<Sema_res *> * Task::construct_if_then_else_sema(common::Node<Subtask *> * v){
    common::List<Sema_res * > * to_ret = new common::List<Sema_res *> ();
    if (v!=NULL){
    printf("calling forr \n");
    v->display();
    common::List<Subtask * > * succs = successors(v);
    printf("this is the successor \n");
    succs->head->display();
    if (succs->size==1){
      printf("here \n");
      to_ret->add_at_tail(new common::Node<Sema_res *>(new Sema_res(v->el,true)));
      to_ret->merge(construct_if_then_else_sema(find_first_condition(v)->head));;
    }
    }
    return to_ret; 
  }







  
  /** 
   * Check's wiether two vertices are linked or not
   * @param v_1 The source subtask 
   * @param v_2 The destination subtask 
   * @return True if the v_1 and v_2 are linked, otherwise it returns false 
   */
  bool Task::is_linked(common::Node<Subtask *> *v_1, common::Node<Subtask *> *v_2){
    return this->graph[v_1->t_id][v_2->t_id]!=0;
  }
  

  /**
   * getter of label 
   */
  std::string Task::_label(){
    return this->label;
  }


  
  
  /**
   * setter of buffer
   * @param buff The buffer to set 
   */

  void Task::add_communication(Communication * comm){
    this->comms->add_at_tail(new common::Node<Communication * >(comm));
  }



  

  /**
   * Get the list of buffers as function of source node 
   * @param src The source node initiating the communication 
   * @return The list of buffers initiated by src 
   */
  common::List<Buffer *> * Task::filter_by_src(Subtask * src){
    common::List<Buffer *> *  to_ret = new   common::List<Buffer *>();
    common::Node<Communication *> * curr = comms-> head; 
    for (int i=0;i<comms->size;i++){
      if (curr->el->_src()==src)
	if (!to_ret->contains(curr->el->_buff()))
	  to_ret->add_at_tail(new common::Node<Buffer *>(curr->el->_buff()));
      curr = curr->next;
    }
    return to_ret;
  }

  /**
   * Get the list of buffers as function of destination node node 
   * @param dst The destination node reading  the communication 
   * @return The list of buffers read by dst node  
   */
  common::List<Buffer *> * Task::filter_by_dst(Subtask * dst){

    common::List<Buffer *> *  to_ret = new   common::List<Buffer *>();
    
    common::Node<Communication *> * curr = comms-> head;
    
    for (int i=0;i<comms->size;i++){
      if (curr->el->_dst()==dst)
	if (!to_ret->contains(curr->el->_buff()))
	    to_ret->add_at_tail(new common::Node<Buffer *>(curr->el->_buff()));
	
      curr = curr->next;
    }
    return to_ret; 
  }

  

  


  /**
   * setter of label
   * @param label The label to set 
   */
  
  void  Task::_label(std::string label){
    this->label=label;
  }




  /**
   * getter of buffers 
   */  
  common::List<Communication *> * Task::_comms(){
    return comms; 
  }
  


  /**
   * setter of buffers
   * @param buff The buffers to set 
   */
  
  void  Task::_comms(common::List<Communication *> * comms){
    this->comms= comms;  
  }

  
  /**
   * Copy exactely the same task without sharing structure
   * @return a reference to the new task object 
   */  
  Task * Task::copy_partial(){
    common::Node<Subtask *> *curr = subtasks->head;
    common::List<Subtask *> *l = new common::List<Subtask *> ();
    for (int i=0;i<subtasks->size;i++){
      Subtask * s  = new Subtask(curr->el->_id(), curr->el->_C(), curr->el->_PC(), curr->el->_type(), curr->el->_TAG());
      common::Node<Subtask *> *n = new common::Node<Subtask *>(curr,SAVE);
      n->el = s; 
      n->el->_label(curr->el->_label());
      l->add_at_tail(n);
      n->el->_label(curr->el->_label()+std::to_string((curr->el->_id())));
      curr = curr->next;
    }
    Task * tau = new Task(-1,l);
    for (int i=0;i<subtasks->size;i++)
      {
	for (int j=0;j<subtasks->size;j++)
	  tau->_graph()[i][j]=graph[i][j]; 
      }
    return tau;
  }


  /**
   * Copy exactely the same task without sharing structure by
   * incrementing incrementing sub-tasks indexes by s_id 
   * @param s_id The index starting params
   * @return a reference to the new task object
   */
  Task * Task::copy_partial(int s_id){
    common::Node<Subtask *> *curr = subtasks->head;
    common::List<Subtask *> *l = new common::List<Subtask *> ();
    for (int i=0;i<subtasks->size;i++){
      Subtask * s  = new Subtask(s_id+i, curr->el->_C(), curr->el->_PC(), curr->el->_type(), curr->el->_TAG());
      common::Node<Subtask *> *n = new common::Node<Subtask *>(curr,SAVE);
      n->el = s; 
      n->el->_label(curr->el->_label());
      l->add_at_tail(n);
      n->el->_label(curr->el->_label()+std::to_string((s_id+i)));
      curr = curr->next;
    }
    Task * tau = new Task(-1,l);
    for (int i=0;i<subtasks->size;i++)
      {
	for (int j=0;j<subtasks->size;j++)
	  tau->_graph()[i][j]=graph[i][j]; 
      }
    return tau;
  }
  
  /**
   * Links task tau in the current task where all entries of tau are successors of s 
   * @param tau the task to insert 
   * @param the concerned vertex
   */
  void Task::link_task_after_subtask(Task * tau,Subtask * s ){
    common::List<Subtask *> * entries = tau->list_entries();
    common::Node<Subtask *> * src = subtasks->find_element(s);
    merge_task(tau);
    common::Node<Subtask *>  * curr_en = entries->head;
    for (int i=0;i<entries->size;i++){
      link_two_subtasks(src, subtasks->find_element(curr_en->el));
      curr_en = curr_en ->next;
    }
  }

  /**
   * The task constructor using the task id and a list of the subtasks
   * that it contains
   * @param id The task id 
   * @param l The list of subtasks 
   */
  Task::Task(int id, common::List<Subtask *> *l){
    this->id = id;
    this->subtasks = l;
    TAG = -1;
    D = -1;
    T = -1;
    label="Task_"+std::to_string(id);
    common::Node <Subtask *> *current = subtasks->head;
    for (int i=0;i<_size();i++){
      current->t_id=i;
      current = current->next;
    }
    graph = (int **)malloc(subtasks->size * sizeof(int *));
    for (int i=0; i<_size(); i++)
      graph[i] = (int *)malloc(subtasks->size * sizeof(int));

     for (int i=0; i<_size(); i++)
       for (int j=0; j<_size(); j++)
	 graph[i][j] = 0 ; 

    
    comms = new common::List<Communication *>();
  }

  /** 
   * Generates a part of the task and all the corresponding Edges 
   * Between two vertices 
   * @param v_s The source subtask 
   * @param v_d The destination subtask 
   * @return a the sub graph of the current task between v_s and v_d 
   */ 
  Task * Task::part_task_between(common::Node<Subtask *> * v_s , common::Node<Subtask *> * v_d){

    common::List<Subtask *> *p= new common::List<Subtask *>();
    common::List<common::List<Subtask *> *> * pp =  new common::List<common::List<Subtask *> *>();
    filter_subtasks_between(v_s,v_d, p, pp);  
    common::List <Subtask *> * merged = pp->head->el->copy();
    common::Node<common::List<Subtask *> *> * curr; 
    curr = pp->head;
    for (int i=0;i<pp->size-1;i++){
      merged->merge_without_duplicates(curr->next->el->copy());
      curr= curr->next;
    }
    merged->add_at_tail(new common::Node<Subtask *>(v_d->el));
    Task * tau_  = new Task(-1, merged);
    for (int i=0;i<_size();i++){
      for (int j=0;j<_size();j++){
	if (i==j)
	  continue;      
	if (merged->contains(_subtasks()->get(i)->el) && merged->contains(_subtasks()->get(j)->el)){
	  if ( is_linked(_subtasks()->get(i), _subtasks()->get(j)))
	    tau_->link_two_subtasks(tau_->_subtasks()->find_element(_subtasks()->get(i)->el),
				    tau_->_subtasks()->find_element(_subtasks()->get(j)->el));
	}   
      }    
    }
    return tau_;
  }


  

  /**
   * The task destructor 
   */
  Task::~Task(){
    // do not forget to destroy the malloc of the grap table !!
    // do not forget to destroy all the conc and sep.
  }

  /** 
      Getter of Period T 
  */ 
  int Task::_T(){
    return T;
  }

  /**  
   * setter of  T 
   * @param T The Period T to set 
   */
  void  Task::_T(int period){
    this->T = period;
  }

  /** 
      Getter of D 
  */ 
  int Task::_D(){
    return this->D;
  }
  /**  
   * setter of D 
   * @param D The D to set 
   */
  void  Task::_D(int deadline){
    this->D = deadline;
  }

  /** 
      Getter of subtasks list 
  */ 
  common::List<Subtask *> * Task::_subtasks(){
    return this->subtasks;
  }
  /**  
   * setter of subtasks list 
   * @param subtasks  The subtasks list to set 
   */
  void Task::_subtasks(common::List<Subtask *> * subtask){
    this->subtasks = subtask;
  }
   

  /** 
      Getter of concrete task list 
  */ 
  common::List<Task *> * Task::_concretes(){
    return this->concretes;
  }
  /**  
   * setter of concretes task list 
   * @param conc Concrete task list to set 
   */
  void Task::_concretes(common::List<Task *> * conc){
    this->concretes = conc;
  }

  /** 
      Getter of tagged tasks list 
  */ 
  common::List<Task *> * Task::_taggeds(){
    return this->taggeds;
  }
  /**  
   * setter of taggeds tasks lists 
   * @param taggeds tasks lists to set 
   */
  void Task::_taggeds(common::List<Task *> * taggeds){
    this->taggeds = taggeds;
  }


  /** 
      Getter of Elems Elementary tasks list 
  */ 
  common::List<Task *> * Task::_elems(){
    return this->elems;
  }
  /**  
   * setter of Elems Elmentary task list 
   * @param Elems Elmentary task list 
   */
  void Task::_elems(common::List<Task *> * elem){
    this->elems = elem;
  }

  /**  
   * setter of Tag 
   * @param Tag The Tag to set 
   */
  void Task::_tag(int TAG){
    this->TAG = TAG;
  }

  /**  
   * setter of Tag 
   * @param Tag The Tag to set 
   */
  int Task::_tag(){
    return this->TAG;
  }

  /** 
      Getter of paths List of paths 
  */ 
  common::List<common::List<Subtask *> *> * Task::_paths(){
    return this->paths;
  }
  /**  
   * setter of path List of paths 
   * @param path List of paths The path List of paths to set 
   */
  void Task::_paths(common::List<common::List<Subtask *> *> * path){
    this->paths = path;
  }

  /** 
      Getter of Graph Graph structure 
  */ 
  int **Task::_graph(){
    return this->graph;
  }

  
  
  /**  
   * setter of Graph The graph structure 
   * @param Graph The  structure to set 
   */
  void Task::_graph(int **g){
    this->graph = g;
  }

  

  /**
   * Link 2 subtasks
   * @param v1 The source subtask
   * @param v2 The destination substask
   * @return The link has been made
   */
  bool Task::link_two_subtasks(common::Node<Subtask *> *v1, common::Node<Subtask *> *v2){
    if (!subtasks->contains(v1->el) || !subtasks->contains(v2->el))
      {
	std::cerr<<"Unable to link subtasks "+v1->el->_label()+" and "+v2->el->_label()<<std::endl;
	std::cerr<<"Please check that both are added to the task before linking them "<<std::endl;
	exit(-1);
      }
    graph[v1->t_id][v2->t_id]=1;
    return true;
  }


  
  /**
   * Add an isolated Subtask the current task 
   * @param s The Subtask to add
   */
  void Task::add_subtask(Subtask *s){
    subtasks->add_at_tail(new common::Node<Subtask *>(s));
    common::Node<Subtask *> * tail = subtasks->tail();
    tail->t_id = subtasks->size -1;
    int ** graph_2 = (int **)malloc(subtasks->size * sizeof(int *));
    for (int i=0; i<_size(); i++)
      graph_2[i] = (int *)malloc(subtasks->size * sizeof(int));

    for (int i=0;i<subtasks->size-1;i++)
      for (int j=0;j<subtasks->size-1;j++)
	graph_2[i][j] = graph[i][j];
    graph = graph_2;

    // do not forget to free the original graph structure/

  }

  // functions used by the grammar
  /**
   * Add one new entry Subtask to the task
   * @param s The subtask to add to the task
   */
  void Task::link_new_entry(Subtask * s){
    add_subtask(s);
    common::Node<Subtask *> * tail = subtasks->tail();
    common::List<Subtask *>  * L = list_entries();
    common::Node<Subtask *> * curr = L->head;
    for (int i=0;i<L->size;i++){
      if (tail->t_id!=curr->t_id)
	link_two_subtasks(tail,curr);
      curr = curr->next;
    }
  }

  /**
   * Add on exit Subtasks to the task and linking it with all current exits
   * @param s The subtask to add
   */
  void Task::link_new_exit(Subtask *s){
    add_subtask(s);
    common::Node<Subtask *> * tail = subtasks->tail();
    common::List<Subtask *>  * L = list_exits();

    common::Node<Subtask *> * curr = L->head;
    for (int i=0;i<L->size;i++){
      if (tail->t_id!=curr->t_id)
	link_two_subtasks(curr,tail);
      curr = curr->next;
    }
  }


    
  // I need to write this functions
  /**
   * Merge two tasks without linking them : just putting them in the same object 
   * @param tau The task to merge
   */
  void Task::merge_task(Task * tau){


    int ** graph_2 = (int **)malloc((subtasks->size + tau->subtasks->size) * sizeof(int *));
    for (int i=0; i<subtasks->size + tau->subtasks->size; i++)
      graph_2[i] = (int *)malloc((subtasks->size + tau->subtasks->size) * sizeof(int));

    for (int i=0;i<subtasks->size;i++)
      for (int j=0;j<subtasks->size;j++)
	graph_2[i][j] = graph[i][j];
    graph = graph_2;


    int shift = subtasks->size;
    for (int i=0;i<tau->subtasks->size;i++)
      for (int j=0;j<tau->subtasks->size;j++)
	graph[i+shift][j+shift] = tau->graph[i][j];

    if (subtasks->size == 0) {
      subtasks->head = tau->subtasks->head;
    }
    else {
      subtasks->tail()->next = tau->subtasks->head;
    }
    subtasks->size +=tau->subtasks->size;

    common::Node<Subtask *> * cur = tau->subtasks->head;
    for (int i=0;i<tau->subtasks->size;i++){
      cur->t_id += shift;
      cur = cur ->next;
    }

  }


  


  /**
   * Link 2 tasks: connecting the entries of tau to the exits of the current task 
   * @param tau The task to add at the end
   */
  void Task::link_task_after(Task * tau ){
    printf("LL GG\n");
    common::List<Subtask *> * entries = tau->list_entries();
    printf("LL \n");
    common::List<Subtask *> * exits = list_exits();
    merge_task(tau);
    printf("here \n");    common::Node<Subtask *>  * curr_en = entries->head;
    for (int i=0;i<entries->size;i++){
      common::Node<Subtask *>  * curr_ex = exits->head;
      for (int i=0;i<exits->size;i++){
	link_two_subtasks(curr_ex,subtasks->find_element(curr_en->el));
	curr_ex = curr_ex->next;
      }
      curr_en = curr_en ->next;
    }
  }

  

 
  
  // calculate succesors and predecessors of a given subtask
  /**
   * Find the successors of a given subtask
   * @param v The given subtask node
   * @return The list of succesors of the given subtask
   */
  common::List<Subtask *> * Task::successors(common::Node<Subtask *> *v){
    common::List<Subtask * > *L = new common::List<Subtask *>();
    common::Node<Subtask *> *current = subtasks->head;
    for (int i=0;i<_size();i++){
      if (graph[v->t_id][current->t_id] == 1)
	L->add_at_head(new common::Node<Subtask *>(current,SAVE));
      current = current->next;
    }
    return L;
  }



  

  

  /**
   * List the task sources (entry point subtasks)
   * @return List of subtask corresponding to the task entry points
   */
  common::List<Subtask *> *  Task::list_entries(){
    common::List<Subtask *> *l = new common::List<Subtask *> ();
    common::Node<Subtask *> * current = subtasks->head;
    for(int i=0;i<_size();i++){
      if (!has_predecessors(current))
	l->add_at_head(new common::Node<Subtask *>(current,SAVE));
      current= current->next;
    }
    return l;
  }





  /**
   * List the task sinks (exit point subtasks) 
   * @return The list of subtask corresponding to the task exits
   */
  common::List<Subtask *> *  Task::list_exits(){
    common::List<Subtask *> *l = new common::List<Subtask *> ();
    common::Node<Subtask *> * current = subtasks->head;
    for(int i=0;i<_size();i++){
      if (!has_successors(current))
	l->add_at_head(new common::Node<Subtask *>(current,SAVE));
      current= current->next;
    }
    return l;
  }


  

  // need to rewrite has_predecessors and has successors that takes only Subtask * !
  // the current version if for optimisation
  /**
   * Check if given subtask has predecessors or not
   * @param v The given subtask Node
   * @return true if the subtask has predecessors, false otherwise
   */
  bool Task::has_predecessors(common::Node<Subtask *> *v){
    for (int i = 0 ; i<_size(); i++){
      if (graph[i][v->t_id]==1)
	return true;
    }
    return false;
  }
  

  /**
   * Check if given subtask has successors or not
   * @param v The given subtask Node
   * @return true if the subtask has successors, false otherwise
   */
  bool Task::has_successors(common::Node<Subtask *> *v){
    for (int i = 0 ; i<_size(); i++){
      if (graph[v->t_id][i]==1)
	return true;
    }
    return false;
  }  

  // looks for a given task using one of its subtasks
  /**
   * Looks for a task using one of its subtasks
   * @param e The subtasks used to find the Task
   * @param ts The tasks list
   * @return The found task or NULL if no task found
   */
  Task * Task::find_task_by_subtask(Subtask *e, common::List<Task *> * ts){
    common::Node<Task *> * tau_curr = ts->head;
    for (int i=0;i<ts->size;i++){
      if (tau_curr->el->subtasks->contains(e))
	return tau_curr->el;
      tau_curr=tau_curr->next;
    }
    return NULL;
  }

  // Splits a task according to two and only two  successors
  /**
   * Generate a list of task starting from the given subtask.
   *
   * @param c  The given subtask
   * @return The list of task starting from the given subtask
   */
  common::List<Task *> * Task::generate_one(common::Node<Subtask *> *c){
    common::List<Task *> *ts = new common::List<Task *>();
    // 1.2 creating concrete tasks
    common::Node <Subtask *> * current = subtasks->head;
    for (int k=0;k<subtasks->size;k++){
      if (graph[c->t_id][current->t_id]==1){
	common::List<Subtask *> * all_next = children(c);
	common::List<Subtask *> * set_minus = subtasks->set_minus(all_next);
	common::List<Subtask *> * successors = children(current);
	successors->merge(set_minus);
	successors->add_at_head(new common::Node<Subtask *>(current->el));
	successors->remove(c->el);
	Task *tau = new Task(id,successors);
	common::Node<Subtask *> *current_r = tau->subtasks->head;
	for (int i = 0 ; i<tau->subtasks->size; i++){
	  common::Node<Subtask *> *current_c = tau->subtasks->head;
	  for (int j = 0 ; j<tau->subtasks->size; j++){
	    common::Node<Subtask *> *src_o = subtasks->find_element(current_r->el);
	    common::Node<Subtask *> *dst_o = subtasks->find_element(current_c->el);
	    if (graph[src_o->t_id][dst_o->t_id]==1){
	      tau->graph[current_r->t_id][current_c->t_id]=1;
	    }
	    current_c = current_c->next;
	  }
	  current_r = current_r->next;
	}
	common::List<Subtask *> * preds = predecessors(c);
	common::Node<Subtask *> * next = tau->subtasks->find_element(current->el);
	common::Node<Subtask *> *curr = preds->head;
	for (int f=0;f<preds->size;f++){
	  common::Node<Subtask *> *equi = tau->subtasks->find_element(curr->el);
	  tau->graph[equi->t_id][next->t_id]=1;
	  curr = curr->next;
	}
#ifdef DEBUG
	std::cout<<"A task has been generated and added \n";
#endif
	ts->add_at_head(new common::Node<Task *>(tau));
      }
      current = current->next;
    }
#ifdef DEBUG
    std::cout<<"Exitting the generating function\n";
#endif
    return ts;
  }
  
  /**
   * Generate concrete or elementary task
   * @param type the type of task you want (ALTERNATIVE or CONDITION)
   */
  void Task::generate_all_conc_tag_el(int type){
    common::List<Subtask *>  *L=new common::List<Subtask *>();
    common::Node<Subtask *> * curr = subtasks->head;
    for (int i=0;i<subtasks->size;i++){
      if ( curr->el->_type() == type)
	L->add_at_head(new common::Node<Subtask *>(curr, SAVE));
      curr = curr->next;
    }
    common::List<Task * > * ts_gen = new common::List<Task *>();
    if (L->size == 0 ){
      std::cout<<"this task is already as you want"<<std::endl;
      // Houssam : I need to check this, I think it does not work, I
      // need may be to do it with a copy function
      ts_gen->add_at_tail(new common::Node<Task *>(this));
      if(type == ALTERNATIVE){
	concretes = ts_gen;
      }else{
	elems = ts_gen;
      }
      return;
    }
    curr = L->head;
    ts_gen = generate_one(curr);
    if (L->size>1)
      curr = L->head->next;
    for (int i=0;i<L->size-1;i++){
      Task * selected = find_task_by_subtask(curr->el,ts_gen);
      ts_gen->remove(selected);
      common::List<Task * > *ts = selected->generate_one(selected->subtasks->find_element(curr->el));
      ts_gen->merge(ts);
      curr= curr->next;
    }
    if (type == ALTERNATIVE)
      concretes = ts_gen;
    else if (type == CONDITION)
      elems=ts_gen;
  }

  // calculating the exact dbf
  /**
   * Calculate the exact premptif dbf for the given Tasklist
   * @param t The given time
   * @param ts the tasks to test
   * @return The calculate dbf
   */
  int Task::dbf_exact(int t, common::List<Task *> * ts){
    int dbf = 0;
    if (is_elementary()){
      // calcul de la dbf
      common::Node<Subtask *> * curr = subtasks->head;
      for (int i =0;i<subtasks->size;i++){
	int t_dbf = 0;
	if (curr->empty)
	  continue;
	common::Node<Subtask *> * curr_j = subtasks->head;
	for (int j=0;j<subtasks->size;j++){
	  int _O=  0;
	  if (curr->O > curr_j->O)
	    _O = T - curr->O + curr_j->O ;
	  else
	    _O =  curr_j->O - curr->O;
	  if (!curr_j->empty){
	    t_dbf += std::floor((t- _O - curr_j->D + T)/T) * (curr_j->el->_C() + compute_vertex_pc(curr_j,ts));
	  }
	  curr_j = curr_j ->next;
	}
	dbf = std::max(dbf,t_dbf);
	curr = curr->next;
      }
    }
    else {
      common::Node<Task *> * current_task = elems->head;
      for (int i=0;i<elems->size;i++){
	dbf=std::max(dbf,current_task->el->dbf_exact(t,ts));
      }
    }
    return dbf;
  }

  // calculate the vertex preemption cost
  /**
   * Calculate the premption cost the the given Subtask
   * @param v The given subtask Node
   * @param gs The Task
   * @return The premption cost of the subtask
   */
  int Task::compute_vertex_pc(common::Node<Subtask  *> * v, common::List<Task *>  *gs){
    if (v-> empty)
      return 0;
    if (not_maximal_sub_set_head(v))
      return 0;
    return preemption_cost_shorter_deadlines(v->D,gs);
  }

  /**
   * Looks if the subtask has to be prempt (has non-empty predeccesor ) or not
   * @param v The given subtask node
   * @return True if the task has to be preempt
   */
  bool Task::not_maximal_sub_set_head(common::Node<Subtask  *> *v){
    common::List<Subtask *> *v_l = predecessors(v);
    if (v_l->size == 0)
      return false;
    common::Node<Subtask *> * curr = v_l->head;
    for (int i=0;i<v_l->size;i++){
      if (curr-> empty)
	return false;
      curr = curr -> next;
    }
    return true;
  }

  // The taskset passed here should not contain the current one
  /**
   * Calculate the preemption cost.
   *
   * @attention The taskset passed here should not contain the current one
   * @param D the subtask deadline
   * @param g_s the Tasks list
   * @return The premption cost
   */
  int Task::preemption_cost_shorter_deadlines(int D,  common::List<Task *>  *g_s){
    int max = 0;
    common::Node<Task *> * curr_tau = g_s->head;
    for (int i=0;i<g_s->size;i++){
      common::Node<Subtask *> * curr_subtask = curr_tau->el->subtasks->head;
      for (int j=0;j<curr_tau->el->subtasks->size;j++){
	if (!curr_subtask->empty && curr_subtask->D > D)
	  max=std::max(max, curr_subtask->el->_PC());
	curr_subtask = curr_subtask->next;
      }
      curr_tau = curr_tau->next;
    }
    return max;
  }

  // The dbf approximation of baruah
  /**
   * Calculate the baruah approximation dbf of the task.
   * Calculate the  baruah approximation dbf of the task if the task is approximable, calculate the exact dbf otherwise.
   * @param t The time
   * @param ts The tasks
   * @return
   */
  int Task::dbf_approxim_baruah(int t,  common::List<Task *> * ts){
    if (is_approximable()){
      // calculate the dbf approximation
      if (t< D)
	return 0;
      int pc_c = 0;
      common::Node<Subtask *> * curr = subtasks->head;
      for (int i = 0; i< subtasks->size;i++){
	pc_c += compute_vertex_pc(curr, ts);
	curr = curr->next;
      }
      return ceil(volume() + pc_c  + (utilization()+ (pc_c / ((double) _T())))*(t-D));
    }
    printf("Not approximable\n");
    return dbf_exact(t, ts);
  }

  /**
   * Calculate the non preemptif dbf for the given task
   * @param t The time
   * @param ts The task list
   * @return The compute dbf
   */
  int Task::dbf_exact_non_preemptif(int t, common::List<Task *> *ts){
    int dbf = 0;
    // Houssam: J'ai besoin de faire ça 
    return dbf;
  }

  // EDF : preempttif and non preemptif call
  /**
   * Calculate the dbf using the wanted method
   * @param t The time
   * @param METHOD The type of the wanted dbf calculus (EXACT_PREEMP, APROX_PREEMP or EXACT_NPEEMP)
   * @param ts The list of task
   * @return The computed dbf
   */
  int Task::dbf(int t, int METHOD, common::List<Task *> *ts){
    // Remove the current tested task from the list
    common::List<Task *> *ts_clear = ts->copy();
    if(!ts_clear->remove(this)){
      std::cout << "Task not found in the list" << '\n';
    }

    switch (METHOD)
      {

      case EXACT_PREEMP:
	return dbf_exact(t,ts_clear);
	break;
      case APROX_PREEMP:
	return dbf_approxim_baruah(t,ts_clear);
	break;
      case EXACT_NPEEMP:
	return dbf_exact_non_preemptif(t,ts_clear);
	break;
      default:
	std::cout<<"UNKNOW OPTION.. EXITTING"<<std::endl;
	exit(-1);
      }
  }
  
  /**
   * Return the preempt index of the task
   *
   * TODO : NOT IMPLEMENTED YET
   * @note TO BE IMPLEMENTED
   * @return The preempt index
   */
  double Task::preemp_index(){
    return 0;
  }

  // task utilization
  /**
   * Calculate the utilization of the task.
   *
   * Calculate the utilization of the task by dividing the task volume by its period
   * @return The task utilization
   */
  double Task::utilization(){
    return (volume()/(double)T);
  }



  /**
   * Calculate the task execution time.
   *
   * Calculate the task execution time by adding each non-empty subtask execution time.
   *
   * @return The task total execution time
   */
  int Task::exec_time(){
    int c = 0;
    common::Node<Subtask *> * curr = subtasks->head;
    for (int i = 0; i< subtasks->size;i++){
      if (!curr -> empty)
	c+= curr->el->_C();
      curr = curr -> next;
    }
    return c;
  }

  /**
   * Calculate the task volume by taking the max possible subtask execution time.
   *
   * @return The task volume
   */
  int Task::volume(){
    int C = 0;
    common::Node<Task *> * curr = elems->head;
    for (int i=0;i< elems->size;i++){
      C= std::max(C, curr->el->exec_time());
      curr = curr -> next;
    }
    return C;

  }

  
  // This function generates the paths starting from a  node
  /**
   * Generate the paths starting from a subtask node and an path
   *
   * Recursively generate the paths from a subtask node. The algorithm :
   *  1. Add the subtask to the path if it's neither an Conditionnal node nor Alternative node
   *  2. Look the number of succesors of this node and :
   *      - If its 0 (sink node) add the path to the paths list
   *      - If its 1 recursively call this function with the successor node and the updated path
   *      - If ist more than 1 recursively call this function for each successor node and an copy af the updated path.
   *
   * @param v The starting subtask node
   * @param p The already existing path (can be empty)
   */
  void Task::generate_single_path(common::Node<Subtask *> *v, common::List<Subtask *> *p){
    if(v->el->_type() != CCONDITION && v->el->_type() != CONDITION && v->el->_type() != ALTERNATIVE)
      p->add_at_tail(new common::Node<Subtask *>(v, SAVE));
    common::List<Subtask *> *succs = successors(v);
    if (succs->size == 0){
      common::Node<common::List<Subtask *> *> *node = new common::Node< common::List<Subtask *> *>(p);
      paths->add_at_head(node);
      delete succs;
      return;
    }
    else {
      if (succs->size==1){
	generate_single_path(succs->head,p);
	delete succs;
	return;
      } else {
	common::Node<Subtask *>* current = succs->head;
	for (int i=0;i<succs->size;i++){
	  common::List<Subtask *> *p_= p->copy();
	  generate_single_path(new common::Node<Subtask *>(current, SAVE),p_);
	  current = current->next;
	}
      }
    }
    delete p;
    delete succs;
  }

  // This function generates the paths starting from a  node
  /**
   * Generate the paths starting from a subtask node and an path
   *
   * Recursively generate the paths from a subtask node. The algorithm :
   *  1. Add the subtask to the path if it's neither an Conditionnal node nor Alternative node
   *  2. Look the number of succesors of this node and :
   *      - If its 0 (sink node) add the path to the paths list
   *      - If its 1 recursively call this function with the successor node and the updated path
   *      - If ist more than 1 recursively call this function for each successor node and an copy af the updated path.
   *
   * @param v The starting subtask node
   * @param p The already existing path (can be empty)
   */
  void Task::filter_subtasks_between(common::Node<Subtask *> *v_s,
				     common::Node<Subtask *> *v_d,
				     common::List<Subtask *> *p, common::List<common::List<Subtask *> *> * pp){
    p->add_at_tail(new common::Node<Subtask *>(v_s->el));
 
    common::List<Subtask *> *succs = successors(v_s);
    if (succs->size == 0 ){
      common::Node<common::List<Subtask *> *> *node = new common::Node< common::List<Subtask *> *>(p);
      if (v_s->el ==v_d->el)
	{
	  pp->add_at_head(node);
	}
      delete succs;
      return;
    }
    else {
      if (succs->size==1){
	if (succs->head->el==v_d->el){
	  common::Node<common::List<Subtask *> *> *node = new common::Node< common::List<Subtask *> *>(p);
	  pp->add_at_head(node);
	  delete succs;
	  return;
	}else {
	  filter_subtasks_between(new common::Node<Subtask *>(succs->head, SAVE),v_d,p, pp);
	   //	  generate_single_path(succs->head,p);
	  delete succs;
	  return;
	}
	
      } else {
	common::Node<Subtask *>* current = succs->head;
	for (int i=0;i<succs->size;i++){
	  if (current->el == v_d->el){
	    common::Node<common::List<Subtask *> *> *node = new common::Node< common::List<Subtask *> *>(p);
	    pp->add_at_head(node);
	    delete succs;
	    return;
	  }
	  else {
	    common::List<Subtask *> *p_= p->copy();
	    filter_subtasks_between(new common::Node<Subtask *>(current, SAVE),v_d,p_, pp);
	    current = current->next;
	  }
	}
      }
    }
    delete p;
    delete succs;
  }
  
  /**
   * Generate all the paths for the task.
   * @return The paths generation succeed
   */
  bool Task::generate_paths(){
    paths = new common::List<common::List<Subtask *> *>();
    common::List< Subtask *>* entries = list_entries();
    common::Node<Subtask *>* current = entries->head;
    //entries->display();
    for (int i=0;i<entries->size;i++){
      common::List <Subtask *> *p = new common::List<Subtask *>();
      generate_single_path(current,p);
      //printf("size of paths %d %d \n", paths->size, entries->size);
      current = current->next;
    }
    //  free(entries);
    return true;
  }

    
  /**
   * Generate all the children of the given subtask.
   *
   * @param v The subtask node
   * @return The list of all the children subtasks of the given one
   */
  common::List<Subtask *> * Task::children(common::Node<Subtask *> *v){
    common::List<Subtask *> * L = new common::List<Subtask *>();
    _children(v,L);
    return L;
  }


  /**
   * Recursively generate the the children of the given.
   *
   * The algorithm :
   *  1. Get the successors of the given subtask and add those to the list
   *  2. Recursively call this function for each successors and the list.
   *
   * @param v The given subtask
   * @param l The childrens list to update
   */
  void Task::_children(common::Node<Subtask *> *v, common::List<Subtask *> * l){

#ifdef DEBUG
    std::cout<<"Calling sub function _children for subask"<<std::endl;
    v->display();
#endif
    common::List<Subtask *> * child_l = successors(v);
    l->merge_without_duplicates(child_l);
    common::Node<Subtask *> * curr = child_l->head;
    for (int i=0;i<child_l->size;i++){
      _children(curr,l);
      curr = curr->next;
    }
  }

  // generates the predecessors of a given subtask
  /**
   * Generate predecessor subtask list of the given subtask
   * @param v The given subtask
   * @return The list of predecessor of the subtask
   */
  common::List<Subtask *> * Task::predecessors(common::Node<Subtask *> *v){
    common::List<Subtask * > *L = new common::List<Subtask *>();
    common::Node<Subtask *> *current = subtasks->head;
    for (int i=0;i<_size();i++){
      if (graph[current->t_id][v->t_id] == 1)
	L->add_at_head(new common::Node<Subtask *>(current,SAVE));
      current = current->next;
    }
    return L;
  }

  // generates all ancetors of a given subtask
  /**
   * Generate all the ancestors of the given subtask
   * @param v The subtask node
   * @return The list of all the ancestors subtasks of the given one
   */
  common::List<Subtask *> * Task::ancetors(common::Node<Subtask  *> *v){
    common::List<Subtask *> * L = new common::List<Subtask *>();
    _ancetors(v,L);
    return L;
  }

  /**
   * Recursively generate the ancestors of the given.
   *
   * The algorithm :
   *  1. Get the predecessors of the given subtask and add those to the list
   *  2. Recursively call this function for each predecessors and the list.
   *
   * @param v The given subtask
   * @param l The ancestors list to update
   */
  void Task::_ancetors(common::Node<Subtask *> *v, common::List<Subtask * > * l){
    common::List<Subtask *> * anc_l = predecessors(v);
    l->merge_without_duplicates(anc_l);
    common::Node<Subtask *> * curr = anc_l->head;
    for (int i=0;i<anc_l->size;i++){
      _ancetors(curr,l);
      curr = curr->next;
    }
  }

  // This function is to generate taggged tasks
  /**
   * Generate the taggeds task.
   */
  void Task::generate_tagged(){
    taggeds = new common::List<Task *>();
    common::List<int> * TAGS = new common::List<int>();
    common::Node<Subtask *> * curr = subtasks->head;
    for (int i=0;i<subtasks->size;i++){
      if (TAGS->contains(curr->el->_TAG())){
	curr = curr->next;
	continue;
      }
      extract_task(curr->el->_TAG());
      TAGS->add_at_head(new common::Node<int>(curr->el->_TAG()));
      curr = curr->next;
    }
  }


  /**
   * Extract a tagged task from the task and add it to the taggeds list.
   *
   * @param tag The wanted tag
   */
  void Task::extract_task(int tag ){
    Task *taggedtask = copy();
    common::Node<Subtask *> *curr = taggedtask->_subtasks()->head;
    taggedtask->_tag(tag);
    for(int i=0;i<taggedtask->_size();i++){
      if(curr->el->_TAG() == tag){
	curr->empty = false;
      }else{
	curr->empty = true;
      }
      curr = curr->next;
    }
    taggeds->add_at_tail(new common::Node<Task *>(taggedtask));
  }


  // Houssam : I need to check if we really need to copy all that 
  /**
   * Create a copy of this task.
   * A complete copy including the tagged, concrete tasks  
   * @return The copy of the task
   */
  Task* Task::copy(){
    Task *copy = new Task(this->id,this->subtasks->copy());
    if(elems!=NULL)
      copy->_elems(elems->copy());
    if(taggeds!=NULL)
      copy->_taggeds(taggeds->copy());
    if(concretes!=NULL)
      copy->_concretes(concretes->copy());
    if(paths!=NULL)
      copy->_paths(paths->copy());
    copy->_tag(TAG);
    copy->_D(D);
    copy->_T(T);
    int** graphcpy;
    graphcpy = (int **)malloc(subtasks->size * sizeof(int *));
    for (int i=0; i<_size(); i++){
      graphcpy[i] = (int *)malloc(subtasks->size * sizeof(int));
      for(int j=0;j<_size();j++){
	graphcpy[i][j] = graph[i][j];
      }
    }
    copy->_graph(graphcpy);
    return copy;
  }
  
  
  // is the dbf approximable
  /**
   * Look if the task dbf is approximable.
   *
   * Check if the task contains a subtask not executed on the same processor (an empty subtask).
   * @return True if the task is dbf approximable, false otherwise
   */
  bool Task::is_approximable(){
    common::Node<Subtask *> * curr = subtasks->head;
    for (int i=0;i<subtasks->size;i++){
      if (curr->empty)
	return false;
      curr = curr -> next;
    }
    return true;
  }

  // is the task elementary
  /**
   * Check if the task is elementary (No conditionnal node)
   *
   * @return True is the task is elementary, false otherwise
   */
  bool Task::is_elementary(){
    common::Node<Subtask *> * curr = subtasks->head;
    for (int i=0;i<subtasks->size;i++){
      if (curr->el->_type() == CONDITION)
	return false;
      curr = curr -> next;
    }
    return true;
  }

  /**
   * Set the deadlines to the subtasks according to the given method.
   *
   * The algorithm :
   *  1. Set all the deadlines to -1
   *  2. Generate and order the paths
   *  3. For each path compute the slack and if the slack is not < 0 call the assignment method of the given method
   *
   * @param METHOD the wanted method (PROP or FAIR)
   * @return true if the assignment end well, false otherwise
   */
  bool Task::deadline_single_task(int METHOD){
    // Houssam: Assign deadline 0 to tasks having a null execution time to
    // Houssam: Avoid reducing the performances of the fair method 
    for (int i=0;i<subtasks->size;i++){
      // Houssam : Optimize this one(list->get(int)), get(i) keeps the current index
      // Houssam : and continues onward (possible acces to i+1) in next
      // Houssam : iterations
      common::Node<Subtask *> *curr_subtask = subtasks->get(i);
      if (curr_subtask->el->_C() == 0)
	{
	  curr_subtask->D=0;
	  printf("what the fuck are you doing \n");
	  curr_subtask->display();
	}
    }
    generate_paths();
    order_paths();
    for (int i=0;i< paths->size; i++){
      common::List<Subtask *> *curr_path = paths->get(i)->el;
      int sl= compute_slack(_D(), curr_path);
      printf("********************************************** \n");
      curr_path->display();
      printf("sl %d",sl);
      printf("********************************************** \n");
      if (sl < 0)
	{
	  std::cerr << "The slack is negative, deadlines are not assigned " << '\n';
	  return false;
	}
      

      switch (METHOD) {
      case PROP:
	prop_assignment(curr_path,sl);
	break;
      case FAIR:
	fair_assignment(curr_path,sl);
	break;
      default:
	std::cerr << "Undefined assignement method" << std::endl;
	return false;
      }
    }
    return true;
  }

  /**
   * Assign the subtasks deadline fairly.
   *
   * The fair assignment is done by calculating the contributors of the path and by set the deadline of the non-assigned subtasks
   * the addition of the exection time of the subtask and the result of the division of the slack by the contributors.
   *
   * \f$D = C() + (\frac{slack}{contributors})\f$.
   *
   * @param curr_path The current used path to assign the deadlines
   * @param sl The slack of the path
   */
  void Task::fair_assignment(common::List<Subtask *> *curr_path,int sl){
    int nbu = 0;
    double n = (double) compute_contributors(curr_path);
    for (int j=0;j<curr_path->size; j++){
      if (curr_path->get(j)->D == -1){
	nbu++;
	double to_add = (sl/n);
	if(nbu == n){
	  to_add = std::ceil(to_add);
	}
	int new_D = curr_path->get(j)->el->_C() +  to_add;
	update_deadline(new_D,curr_path->get(j)->el);
      }
    }
  }

  /**
   * Update the deadline of a Subtask to every Node containing it.
   *
   * @param new_D The new deadline
   * @param to_find The subtask to update everywhere in the task
   */
  void Task::update_deadline(int new_D,Subtask * to_find){
    common::Node<Subtask *> *find_element = subtasks->find_element(to_find);
    find_element->D = new_D;
    for (int k = 0; k < paths->size; k++) {
      if(paths->get(k)->el->contains(to_find)){
	common::Node<Subtask *> *find_element = paths->get(k)->el->find_element(to_find);
	find_element->D = new_D;
      }
    }
    if(concretes != NULL){
      for (int k = 0; k < concretes->size; k++) {
	if(concretes->get(k)->el->subtasks->contains(to_find)){
	  common::Node<Subtask *> *find_element = concretes->get(k)->el->subtasks->find_element(to_find);
	  find_element->D = new_D;
	}
      }
    }
  }

  /**
   * Proportionnaly assign deadlines to the path using the contributing charge.
   *
   * Assigns slack according to the contribution of the sub-task execution time in the path.
   *
   * \f$D = C() + (\lceil \frac{C()}{compute_contributing_charge()}\rceil * slack)\f$
   *
   * @param curr_path: The current path
   * @param sl:  the Slack of the path
   **/
  void Task::prop_assignment(common::List<Subtask *> *curr_path,int sl){
    int nbu = 0;
    double n = (double) compute_contributing_charge(curr_path);
    for (int j=0;j<curr_path->size; j++){
      if (curr_path->get(j)->D == -1){
	nbu++;
	double to_add = std::ceil((curr_path->get(j)->el->_C()/n) * sl);
	int new_D = curr_path->get(j)->el->_C() +  to_add;
	update_deadline(new_D,curr_path->get(j)->el);
      }
    }
  }

  /**
   * Compute the execution time of the given list of cubtask (i.e. the path)
   *
   * @param L the path to use for computing the execution time
   * @return the total execution time for the path
   */
  int Task::path_exec_time(common::List<Subtask *> * L){
    common::Node<Subtask *> * curr = L->head;
    int C=0;
    for (int i=0;i<L->size;i++){
      C+=curr->el->_C();
      curr = curr ->next;
    }
    return C;
  }

  /**
   * Order the path using the decreasing order of execution time.
   * TODO :Bubble sort   : May be we should do quick-sort
   * @return The path has been ordered
   */
  bool Task::order_paths(){
    common::List<common::List<Subtask *> *> * l_p = new common::List<common::List<Subtask *> *> ();
    while (paths->size > 0){
      common::List<Subtask *> * max_p=paths->head->el;
      int max_c= path_exec_time(max_p);
      common::Node<common::List<Subtask *> *> * curr = paths->head;
      for (int j=0;j<paths->size;j++){
	int ex_t  = path_exec_time(curr->el);
	if ( ex_t> max_c){
	  max_c  = ex_t;
	  max_p = curr->el;
	}
	curr = curr->next;
      }
      paths->remove(max_p);
      l_p->add_at_tail(new common::Node<common::List<Subtask *> * >(max_p));
    }
    paths = l_p;
    return true;

  }
    
  /**
   * Sort the concretes task using the given order
   * @param order The order to use ( PARTIAL OR RELATION)
   * @param processors The List of the processor (Used in RELATION ordering)
   * @return The list has been ordered
   */
  bool Task::sort_concretes(int order,common::List<int> *tags) {
    bool ret ;
    if(order==PARTIAL){
      ret = sort_concretes_partial();
    }else if(order == RELATION){
      ret = sort_concretes_relation(tags);
    }else{
      printf("CONCRETE SORTING ORDER DON'T EXISTS...EXITINg\n");
      exit(-1);
    }
    return ret;
  }

  /**
   * Sort the concretes task using the partial ordering (i.e. by decreasing order)
   * @return The list has been sorted
   */
  bool Task::sort_concretes_partial(){
    common::List<Task *> *l_p = new common::List<Task *>();
    while (concretes->size > 0) {
      Task *max_p = concretes->head->el;
      int max_c = max_p->exec_time();
      common::Node<Task *> *curr = concretes->head;
      for (int j = 0; j < concretes->size; j++) {
	int ex_t = curr->el->exec_time();
	if (ex_t > max_c) {
	  max_c = ex_t;
	  max_p = curr->el;
	}
	curr = curr->next;
      }
      concretes->remove(max_p);
      l_p->add_at_tail(new common::Node<Task *>(max_p));
    }
    concretes = l_p;
    return true;
  }


  // Houssam: I need to check this function 
  /**
   * Sort the concretes tasks using the relationship order >>
   * @param tags the scarce-ordered list (the rarest first) of tags of the architecture
   * @return the list has been ordered
   */
  bool Task::sort_concretes_relation(common::List<int>*tags){
    common::List<Task *> *l_p = new common::List<Task *>();
    while(concretes->size >0) {
      Task *max_p = concretes->head->el;
      max_p->generate_tagged();
      common::Node<Task *> *curr = concretes->head;
      for(int j = 0;j < concretes->size;j++){
	curr->el->generate_tagged();
	for (int i = 0; i < tags->size; i++) {
	  int tag = tags->get(i)->el;
	  if (curr->el->get_tagged_task(tag) != NULL && max_p->get_tagged_task(tag) != NULL) {
	    if (curr->el->get_tagged_task(tag)->exec_time() < max_p->get_tagged_task(tag)->exec_time()) {
	      max_p = curr->el;
	      break;
	    }
	  }else{
	    if(curr->el->get_tagged_task(tag) == NULL){
	      max_p = curr->el;
	    }
	    break;
	  }
	}
	curr = curr->next;
      }
      concretes->remove(max_p);
      l_p->add_at_tail(new common::Node<Task *>(max_p));
    }
    concretes = l_p;
    return true;
  }

  /**
   * 
   * A getter for the one tagged task 
   * (This function should be used after calling the tagged tasks generations )
   * @param TAG is the tag to get 
   * @return the tagged task  
   **/  
  Task * Task::get_tagged_task(int TAG) {
    if(taggeds->size == 0){
      return  NULL;
    }
    for(int i =0; i<taggeds->size;i++){
      if(taggeds->get(i)->el->_tag()==TAG){
	return taggeds->get(i)->el;
      }
    }
    return NULL;
  }

  
  /**
   * Compute the slack for the given list of subtasks.
   *
   * @param D the Task deadline
   * @param l The list of subtasks
   * @return The computed slack
   **/
  int Task::compute_slack(int D, common::List<Subtask *> *l){
    int curr_D = 0;
    int curr_C = 0;
    for (int i=0;i<l->size;i++){
      common::Node<Subtask *>*task = l->get(i);
      if (task->D != -1){
	curr_D += task->D;
      }
      else{
	if (task->el->_C()>0){
	  curr_C+= task->el->_C();
	}
      }
    }
    return D - curr_D - curr_C;
  }

  
    
  /**
   * Compute the numbers of contributors for the given list of subtasks.
   *
   * @param l The list of subtasks used to compute the contributors
   * @return The computed numbers of contributors
   **/
  int Task::compute_contributors(common::List<Subtask *>*l){
    int to_ret=0;
    for (int i=0;i<l->size;i++){
      common::Node<Subtask *>*task = l->get(i);
      if (task->D == -1 )
	to_ret++;
    }
    return to_ret;
  }

  /**
   * Compute the contributing charge for the given list of subtasks.
   *
   * @param l List of subtasks used to compute the contributing charge
   * @return the computed contributing charge
   **/
  int Task::compute_contributing_charge(common::List<Subtask *>*l){
    int to_ret=0;
    for (int i=0;i<l->size;i++){
      common::Node<Subtask *>*task = l->get(i);
      if (task->D == -1)
	to_ret+=l->get(i)->el->_C();
    }
    return to_ret;
  }

  /**
   * Gives the number of subtasks
   *
   * @return the number of subtasks
   **/
  int Task:: _size(){
    return subtasks->size;
  }

  
  /**
   * Create the dot representation of the task.
   * @param path The path the file will be writen to
   * @return The dot file has been successfully created
   */

  bool Task::to_dot(std::string path){
    
#ifdef DEBUG
    std::cout<<"-> Calling to dot for task: "<<id<<"\n";
#endif
    std::ofstream outdata;
      
    outdata.open(path); // opens the file
    if( !outdata ) { // file couldn't be opened
      std::cerr << "Error: File can not be openned: Writting failed" << std::endl;
      exit(-1);;
    }

    outdata << "digraph mon_graphe {\n" << std::endl;

    common::Node<Subtask *> *current = subtasks->head;

    for (int i = 0 ; i<_size(); i++){
      if (current->el->_type() == CONDITION)
	outdata<< current->el->_label()<<" [shape=diamond]"<<std::endl;
      else if (current->el->_type() == CCONDITION)
	outdata<< current->el->_label()<<" [shape=diamond style=filled]"<<std::endl;
      else if (current->el->_type()==ALTERNATIVE)
	outdata<< current->el->_label() <<" [shape=rectangle]"<<std::endl;
      else
	outdata<< current->el->_label() <<" [shape=circle]"<<std::endl;
      current = current->next;
    }

    common::Node<Subtask *> *current_r = subtasks->head;
    for (int i = 0 ; i<_size(); i++){
      common::Node<Subtask *> *current_c = subtasks->head;
      for (int j = 0 ; j<_size(); j++){

	if (graph[current_r->t_id][current_c->t_id]==1)
	  outdata<< current_r->el->_label() << "->"<<current_c->el->_label()<<std::endl;
	current_c = current_c->next;
      }
      current_r = current_r->next;
    }
    outdata<<"}"<<std::endl;
    outdata.close();

#ifdef DEBUG
    printf("End of to_dot call \n");
#endif
    return 0;
  }
    
  /**
   * Display the task informations and content
   */
  void Task::display(){
    std::cout<<"[Task ID:"<<id<<std::endl;
    subtasks->display();
    for (int i=0;i<subtasks->size;i++){
      std::cout<<std::endl;
      for (int j=0;j<subtasks->size;j++)
	std::cout<<graph[i][j]<<"\t";
    }
    std::cout<<std::endl;
  }
  Sema_res::Sema_res(Subtask *t, bool left){
    this->t = t;
    this->left=left;
  }
  Sema_res::~Sema_res(){
  }
  void  Sema_res::display(){
    std::cout<<"["+std::to_string(t->_id())+" "+ std::to_string(left)+"]"<<std::endl;
  }
}
