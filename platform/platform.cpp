#include "platform.hpp"
namespace platform{
  common::List<Processor *> *Platform::_engines(){
    return engines;
  }




  Platform * Platform::copy(){
    Platform * pl = new Platform();
    pl->engines = new common::List<Processor *>();
    for (int i=0;i<this->engines->size;i++){
      pl->engines->add_at_head(new common::Node<Processor *> (new Processor(engines->get(i)->_id())));
      task::Taskset *tsss = this->engines->get(i)->_ts()->params_task_pointers();
      pl->find_processor(engines->get(i)->_id())->_ts(tsss);
    }
    return pl;
  }


  void Platform::print_alloc(){
   
    for (int i=0;i<engines->size;i++)
      {
	//	printf("staring %p \n", engines->get(i));
	engines->get(i)->print_ts();
	//	printf("ye p \n");
      }
    // printf("finished \n");
  }
  Processor * Platform::find_processor(int id){

    for (int i=0;i<engines->size;i++)
      if (engines->get(i)->_id()==id)
	return engines->get(i);
    return NULL;
  }


  bool Platform::check_utilization(){
    for (int i=0;i<engines->size;i++)
	if (engines->get(i)->_ts()->Liu_U()>1)
	  return false;
    return true;
  }
  void Platform::_engines(common::List<Processor *> * engines){
    this->engines = engines;
  }

  bool Platform::order_processors(){
    common::List<Processor *> * l_p = new common::List<Processor *> ();
    common::List<int> *l_t = list_tag();
    while (l_t->size > 0) {
      int tag = l_t->head->el;
      int max_c = nb_proc_tag(tag);
      for (int j = 0; j < l_t->size; j++) {
	int ex_t = nb_proc_tag(l_t->get(j));
	if (ex_t < max_c) {
	  max_c = ex_t;
	  tag = l_t->get(j);
	}
      }
      for (int i = 0; i < engines->size; i++) {
	if (tag == engines->get(i)->_TAG()) {
	  l_p->add(engines->get(i));
	}
      }
      for(int i = 0 ; i< l_p->size; i++){
	engines->remove(l_p->get(i));
      }
      l_t->remove(tag);
    }
    engines = l_p;
    return true;
  }

  Processor * Platform::get(int i){
    return engines->get(i);
  }
  
  
  common::List<int> * Platform::list_tag(){
    common::List<int> * ret = new common::List<int>();
    for (int i = 0; i < engines->size ; i++) {
      if(!ret->contains(engines->get(i)->_TAG())){
	ret->add(engines->get(i)->_TAG());
      }
    }
    return ret;
  }

  int Platform::nb_proc_tag(int tag){
    int ret = 0;
    for (int i = 0; i < engines->size; i++)
      if(engines->get(i)->_TAG() ==tag )
	ret++;
    return ret;
  }

  /**** eliminer zero solution processor *****/
  void Platform::eliminer_zero_proc(common::List<platform::Platform *> * sols) {
  
  printf(" ** ---------------elimi processor vide------------------------** \n");
  int hhh=-1;
     
  for (int i=0;i<sols->size;i++) //sols->size
    {
      int removed=0;
      printf(" \\\\\\\\\****************************PLATFORM %d*********************/////// \n", i); 
      hhh=hhh+1; 
      
       platform::Platform * plat= sols->get(i); //une platform
       printf("voici la platform etudiee avec plat, size de la platforme %d\n", sols->size);
       plat->print_alloc(); 
       
       for (int k=0;k<plat->_engines()->size;k++)
	 {
	   if(plat->_engines()->get(k)->_ts()->_list()->size == 0) {
	     // plat->print_alloc();
	     sols->remove(plat);
	     printf("PLATFORM numero %d is Removed \n", hhh);
	     break;
	   }
	 
	 }
       
     }

}



  /****** compute cost for one platform (solution ******/

  int Platform::compute_cost(int *deadlines,int nb){
    int Q=0;
    for (int i=0;i<this->_engines()->size;i++)   {
      // printf("staring %p \n", engines->get(i));
      // task::Taskset *tsss = this->engines->get(i)->_ts()->params_task_pointers();
      common::List<task::Task *> *task_list= this->_engines()->get(i)->_ts()->_list();
      for (int j=0;j<task_list->size;j++)   {
	printf("****** Compute lenght of non preemption region Method ****** \n");
     	Q=task_list->get(j)->compute_LEN_NPR( task_list, deadlines, nb);
 	this->_engines()->get(i)->_ts()->_list()->get(j)->_q(Q);
	std::cout<< "Q[" << j <<" ]="<<  Q  << std::endl;

        printf("****** Applay optimal selection Method ****** \n");
        common::List<task::Bloc *>* blocss= this->_engines()->get(i)->_ts()->_list()->get(j)->_blocs();
        int OpSel= task_list->get(j)->Optimal_Selection_PPP(this->_engines()->get(i)->_ts()->_list()->get(j)->_q(),blocss);
        printf(" cout de premeption  %d \n", OpSel);
      }
     
    }
  }

  platform::Platform * Platform::Optimal_solution(common::List<platform::Platform *> * sols, int *deadlines, int nb){
  
    int cost =0;
    int cost_opt= sols->get(0)->compute_cost(deadlines, nb);
    platform::Platform * sol_opt=sols->get(0);
    printf(" solution optimale avant \n");
    sol_opt->print_alloc();
    common::List<platform::Platform *> * solss;
   
    sols->remove(sol_opt);
    // printf(" print after remove of sol1\n");
    //  for (int j=1;j<sols->size;j++){
    //   sols->get(j)->print_alloc();
    //  }
   
    for (int i=0;i<sols->size;i++){
      cost = sols->get(i)->compute_cost(deadlines, nb);
      printf(" cost in the function optimal solution %d \n" , cost);
      if(cost< cost_opt){
    	cost_opt=cost; 
    	sol_opt=sols->get(i);
     	sol_opt->print_alloc();
      }
    }
    printf(" solution optimale \n");
    sol_opt->print_alloc();
    return sol_opt;
  }

  // solution ameliorer
  int Platform::compare_Qis( common::List<int > * Q_other, common::List<int > * Qi_Opt){
    //  int cmp=1;
  for (int i=0;i< Q_other->size;i++)   {
      common::List<task::Task *> *task_list= this->_engines()->get(i)->_ts()->_list();
      for (int j=0;j< Qi_Opt->size;j++)   {
        if(Qi_Opt->get(j)!=Q_other->get(i)) {
	  return 0;
	}
    }
  }
  return 1;
  }

 platform::Platform * Platform::Optimal_solution_amelior(common::List<platform::Platform *> * sols, int *deadlines, int nb){
   int Q=0;
   int Q_other=0;
   int comp=0;
   int cost =0;
   int cost_opt= sols->get(0)->compute_cost(deadlines, nb);
    
    platform::Platform * sol_opt=sols->get(0);
    common::List<int > * Qi_Opt= new common::List<int > ();
    common::List<int > * Qi_Other= new common::List<int > ();

    //Qi of the first optimal solution
    for (int i=0;i< sols->get(0)->_engines()->size;i++)   {
      common::List<task::Task *> *task_list= this->_engines()->get(i)->_ts()->_list();
      for (int j=0;j<task_list->size;j++)   {
     	Q=task_list->get(j)->compute_LEN_NPR( task_list, deadlines, nb);
	sol_opt->_engines()->get(i)->_ts()->_list()->get(j)->_q(Q);
	Qi_Opt->add_at_head(new common::Node<int > (Q));
	std::cout<< "Q[" << j <<" ]="<<  Q  << std::endl;

      } 
    }
    sols->remove(sol_opt); //REMOVE THE FIRST ELEMENT 
  
   
    for (int k=0;k<sols->size;k++){

      for (int i=0;i< sols->get(0)->_engines()->size;i++)   {
	common::List<task::Task *> *task_list= this->_engines()->get(i)->_ts()->_list();
	for (int j=0;j<task_list->size;j++)   {
	  Q_other=task_list->get(j)->compute_LEN_NPR( task_list, deadlines, nb);
	  sol_opt->_engines()->get(i)->_ts()->_list()->get(j)->_q( Q_other);
	  Qi_Other->add_at_head(new common::Node<int > ( Q_other));
	  std::cout<< "Q[" << j <<" ]="<<  Q  << std::endl;
	} 
      }

     comp= compare_Qis(Qi_Other,Qi_Opt);
     if ( comp==0) 	sol_opt=sols->get(k);
     else {
       if( comp==2) {
	 cost = sols->get(k)->compute_cost(deadlines, nb);
	 printf(" cost in the function optimal solution seconde solution  %d \n" , cost);

	 if(cost< cost_opt){
	   cost_opt=cost; 
	   sol_opt=sols->get(k);
	   sol_opt->print_alloc();
	 }
       }
     }
    }
    printf(" solution optimale \n");
    sol_opt->print_alloc();
    return sol_opt;
  }
}
