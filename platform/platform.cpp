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
}
