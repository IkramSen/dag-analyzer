#include "analysis.hpp"
namespace analysis{
    task::Taskset* ts;
    platform::Platform *platform;

    /**
    * The analyse and allocation algorithm.
    *
    * This algorithm try to allocate all the task on the engines in his taskset using the given order ( Order Relationship a.k.a >> or Partial Order Relation a.k.a ≻),
    * slack (FAIR or PROPortional), alloc (BestFit or WorstFit) and omit (RANDOM or PARRallel). It try at first to allocate the task sequentally and if it doesn't succeed
    * it try to parrallelizedthe allocation. The algorithm gives priority to single-engine allocations because they reduce preemption cost.
    * @param archi : The target architecture i.e. the list of processors
    * @param tasks : The to-be allocated tasks specifications
    * @param order (>> or ≻): used to sort the concretes task of a taskset's task (use RELATION or PARTIAL macro).
    * @param slack (FAIR or PROPortional): used to sort the paths of a concrette task (use FAIR or PROP macro).
    * @param alloc (BestFit or WorstFit): used to sort the engines (use BF or WF macro).
    * @param omit (RANDOM or PARRallel): if the allocation must be parralellized, the omit is used to know how we choose the subtask to remove (use RANDOM or PARR macro).
    * @return True if the allocation is successfull, False otherwise
    **/
  bool analyse(platform::Platform *archi,task::Taskset* tasks,int order,int slack,int alloc, int omit){
    platform = archi;
    platform->order_processors();
    ts = tasks;

    for(int i=0 ;i < ts->_size();i++){
      task::Task *current = ts->get(i); 

      current->generate_all_conc_tag_el(ALTERNATIVE);
      current->sort_concretes(order,platform->list_tag());
	  
      for(int j = 0 ; j < current->_concretes()->_size(); j++){
	task::Task *curconcrete = current->_concretes()->get(j);
	if(!curconcrete->deadline_single_task(slack))
	  return false;
	curconcrete->generate_tagged();
      }
	    
      bool allocated = false;
      for(int j = 0 ; j < current->_concretes()->_size(); j++){
	task::Task * curconcrete = current->_concretes()->get(j);
	if(is_feasible_sequential(alloc,curconcrete)){
	  allocated=true;
	  break;
	}
      }
	    
      if(!allocated){  
	for(int j = 0 ; j < current->_concretes()->_size(); j++){
	  task::Task *  curconcrete = current->_concretes()->get(j);
	  task::Task* parr = parallelize(alloc,omit,curconcrete);
	  if(parr != curconcrete){
	    ts->add(parr);
	    allocated = true;
	    break;
	  }
	}
	if (!allocated){
	  return false;
	}
      }
    }
    return true;
  }

    /**
    * Try to sequentally allocate the different tagged task of the given task to corresponding engines.
    * Try to allocate the task by allocating each tagged task to one tag-corresponding engine (i.e. all CPU subtasks to 1 CPU )
    *
    * @param alloc is the alloc type (BestFit or WorstFit) to use when sorting the engines
    * @param task is the Task to alloc on the different engines
    * @return True if the task has been entirelly allocate sequentally, False otherwise
    **/
  bool is_feasible_sequential(int alloc,task::Task* task){
    common::Node<task::Task *> *  curr = task->_taggeds()->_list()->_get(0);
    int nfeas = 0;
    common::List<platform::Processor *> *engine_list = select_engine(curr->el->_tag());
    for(int i =0;i<task->_taggeds()->_size();i++){
      curr = task->_taggeds()->_list()->_get(i);
      engine_list = sort_engines(engine_list,alloc);
      bool f = false;
      for(int j = 0; j< engine_list->size;j++){
	platform::Processor * curreng = engine_list->get(j);
	task::Taskset *copy = taskset_union(curr->el,curreng->_ts());
	f = dbf_test(copy);
	copy->~Taskset();
	if(f){
	  curreng->_ts()->_list()->add_at_tail(new common::Node<task::Task *>(curr,SAVE));
	  nfeas++;
	  break;
	}
      }
      if(!f)
	return false;
    }
    if(nfeas == task->_taggeds()->_size()){
      platform->_engines(engine_list);
      return true;
    }
    return false;
  }

    /**
    * Get the list of engine with the given tag (e.g. all the CPU)
    *
    * @param TAG the wanted engines tag
    * @return The list of tag-corresponding engines
    **/
    common::List<platform::Processor *>* select_engine(int TAG){
        common::List<platform::Processor *> *engines = new common::List<platform::Processor *>();
	for(int i=0; i < platform->_engines()->size;i++){
	  common::Node<platform::Processor *> * current = platform->_engines()->_get(i);
	  if(current->el->_TAG() == TAG){
                common::Node<platform::Processor *> * newnode = new common::Node<platform::Processor *>(current,SAVE);
                newnode->el = newnode->el->copy();
                engines->add_at_tail(newnode);
            }
        }
        return engines;
    }

    /**
    * Sort the engine list according the alloc (BestFit or WorstFit)
    *
    * Best Fit : decreasing order of utilization
    * Worst Fit : increasing order of utilization
    * @attention TODO : Bubble sort   : May be we should do quick-sort
    * @param engines is the list of available engines to be sort
    * @param alloc is the type of alloc you want to use (use BF or WF macro)
    * @return The sorted list of available engine according the used alloc
    */
  common::List<platform::Processor*> *sort_engines(common::List<platform::Processor*> *engines, int alloc){
    common::List<platform::Processor*> *l_p = new common::List<platform::Processor*>();
    while (engines->size > 0){
      platform::Processor *max_p=engines->head->el;
      int max_c= max_p->_ts()->utilization();
      
      for (int j=0;j<engines->size;j++){
	platform::Processor * curr = engines->get(j);
	int ex_t  = curr->_ts()->utilization();
	bool ok = alloc == BF ? ex_t> max_c : ex_t < max_c;
	if (ok){
	  max_c  = ex_t;
	  max_p = curr;
	}
      }
      engines->remove(max_p);
      l_p->add_at_tail(new common::Node<platform::Processor*>(max_p));
    }
    return l_p;
  }


  //May be it should be move to the taskset class 
    /**
    * DBF test for the given taskset
    *
    * @param ts is the taskset to test
    * @return True if the taskset is schedulable, False otherwise
    */
    bool dbf_test(task::Taskset *ts){
        int hyper = ts->hyperperiod(),dbf;
        for(int t=0 ;t <hyper;t++){
            dbf = 0;
            for(int j =0;j<ts->_list()->size;j++){
	      dbf += ts->_list()->get(j)->dbf(t,BARUAH_APPROX,ts);
            }
            if(dbf>t){
                return false;
            }
        }
        return true;
    }

    /**
    * Try to allocate parrallelly the task on engines
    * Try to allocate the task by allocating each tagged task to one tag-corresponding engine (i.e. all CPU subtasks to 1 CPU ).
    * If it doesn't succeed, until it succeed, one subtasks will be add to the omitted list (using omit) that will be allocate to another engine
    * @param alloc (BestFit or WorstFit): used to sort the engines (use BF or WF macro)
    * @param omit (RANDOM or PARRallel): used to kown which subtask we will omit from the task
    * @param task is the Task to allocate on the engines
    * @return a struct containing : - if the allocation is successfull. -The feasible task to be allocated. -The task to re-allocate later.
    **/
    task::Task *parallelize(int alloc,int omit,task::Task* task){
        task::Task * tp = task->copy();
        task::Task * tsec = task->copy();
        for(int i =0; i<tsec->_subtasks()->size;i++)
	  tsec->_subtasks()->_get(i)->empty=true;
        

        bool allocated = false;
        common::List<platform::Processor *> *engine_list;
        for(int i= 0; i<task->_taggeds()->_size();i++){

	  task::Task * curr = task->_taggeds()->get(i);
	  engine_list = select_engine(curr->_tag())->copy();
            engine_list =sort_engines(engine_list,alloc);
            
            for(int j = 0;j < engine_list->size;j++){
	      platform::Processor * curreng = engine_list->get(j);
	      task::Taskset *copy = taskset_union(curr,curreng->_ts());
	      bool empty = true;
	      bool f = dbf_test(copy);
	      while(!f){
		task::Subtask* removedsubtask = omit_remove(tp->get_tagged_task(curr->_tag()),omit);
		tp->get_tagged_task(curr->_tag())->_subtasks()->find_element(removedsubtask)->empty=true;
		tsec->get_tagged_task(curr->_tag())->_subtasks()->find_element(removedsubtask)->empty=false;
		copy = taskset_union(tp->get_tagged_task(curr->_tag()),curreng->_ts());
		f = dbf_test(copy);
	      }

	      for(int k=0;k<tsec->get_tagged_task(curr->_tag())->_subtasks()->size ;k++ )
		if(!tsec->get_tagged_task(curr->_tag())->_subtasks()->_get(k)->empty){
		  empty = false;
		  break;
		}
   
	     
	      if(!empty){
		curreng->_ts()->_list()->add(tsec->get_tagged_task(curr->_tag()));
		allocated = true;
		break;
	      }
            }
            if(!allocated){
	      return task;
            }
        }
        platform->_engines(engine_list);
        return tsec;
    }

    /**
    * Choose a subtask to add to the omited list in the given task using the given omit.
    *
    * Choose a subtask between all the omitable subtask (i.e. the Node's empty member is false) of the given task. The subtask is choosed according to the omit (Randomlly or using Parallel heuristic).
    * @param tau is the task from which we want to remove a subtask
    * @param omit heuristic used (Random or Parrallel)
    * @return The subtask to add to the omitted list
    **/
    task::Subtask * omit_remove(task::Task *tau, int omit){
        common::List<task::Subtask *> *v_l= new common::List<task::Subtask *>();
      
        for(int i=0;i<tau->_subtasks()->size;i++){
	  common::Node<task::Subtask *>* curr = tau->_subtasks()->_get(i);
	  if(!curr->empty)
	    v_l->add_at_tail(new common::Node<task::Subtask *>(curr,SAVE));
        }
        if(v_l->size)
            return NULL;
        
        switch (omit) {
            case RANDOM: {
                std::srand(std::time(NULL));
                int chosenidx = std::rand() % v_l->size;
                return v_l->get(chosenidx);
            }
            case PARR: {
                return select_preemp_aware(tau);
            }
            default:
	      fatal_error(42, "UNKNOWN OMIT....EXITTING");
        }
	return NULL;
    }

    /**
    * Select a subtask to omit using the parrallel heuristic.
    * Choose an omitable subtask that is not on the critical path of the task.
    * @param tau is the task from which we want to remove a subtask
    * @return The subtask to add to the omitted list
    * @warning TO BE IMPLEMENTED
    **/
    task::Subtask * select_preemp_aware(task::Task *tau){
        return NULL;
    }

    /**
    * Create a Taskset from an existing Taskset and a Task.
    *
    * @param Task to add to the new Taskset
    * @param ts taskset use as basis of the new taskset
    **/
    task::Taskset *taskset_union(task::Task *task , task::Taskset *ts){
        task::Taskset *copy = new task::Taskset(5);
        common::List<task::Task *>*copylist = ts->_list()->copy();
        copylist->add_at_tail(new common::Node<task::Task *>(task));
        copy->_list(copylist);
        return copy;
    }

    common::List<platform::Processor *> *_processors(){
        return platform->_engines();
    }
}
