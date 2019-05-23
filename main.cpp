#include "task/subtask.hpp"
#include "common/list.hpp"
#include "task/task.hpp"
// <<<<<<< HEAD
// #include "platform/processor.hpp"

// #define GPU 1



// using namespace std;


// int main(int argc, char ** argv){
 
//   common::Node<task::Subtask *> *v1=new common::Node<task::Subtask *>( new task::Subtask(1,5,1,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v2=new common::Node<task::Subtask *>( new task::Subtask(2,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v3=new common::Node<task::Subtask *>( new task::Subtask(3,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v4=new common::Node<task::Subtask *>( new task::Subtask(4,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v5=new common::Node<task::Subtask *>( new task::Subtask(5,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v6=new common::Node<task::Subtask *>( new task::Subtask(6,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v7=new common::Node<task::Subtask *>( new task::Subtask(7,5,2,CONDITION,GPU));
//   common::Node<task::Subtask *> *v8=new common::Node<task::Subtask *>( new task::Subtask(8,5,2,ALTERNATIVE,GPU));
//   common::Node<task::Subtask *> *v9=new common::Node<task::Subtask *>( new task::Subtask(9,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v10=new common::Node<task::Subtask *>( new task::Subtask(10,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v11=new common::Node<task::Subtask *>( new task::Subtask(11,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v12=new common::Node<task::Subtask *>( new task::Subtask(12,5,2,COMPUTE,GPU));




//   common::Node<task::Subtask *> *v14=new common::Node<task::Subtask *>( new task::Subtask(14,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v15=new common::Node<task::Subtask *>( new task::Subtask(15,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v16=new common::Node<task::Subtask *>( new task::Subtask(16,5,2,COMPUTE,GPU));
//   common::Node<task::Subtask *> *v17=new common::Node<task::Subtask *>( new task::Subtask(17,5,2,COMPUTE,GPU));


//   common::List<task::Subtask *> *l=new common::List<task::Subtask *>();
//   common::List<task::Subtask *> *l2=new common::List<task::Subtask *>();

//   common::List<task::Subtask *> *l3=new common::List<task::Subtask *>();
//   l3->add_at_head(v14);
//   l3->add_at_head(v15);
//   l3->add_at_head(v16);
//   l3->add_at_head(v17);

//   l2->add_at_head(v1);
//   l2->add_at_head(v2);
//   l->add_at_head(v3);
//   l->add_at_head(v4);
//   l->add_at_head(v5);
//   l->add_at_head(v6);
//   l->add_at_head(v7);
//   l->add_at_head(v8);
//   l->add_at_head(v9);
//   l->add_at_head(v10);
//   l->add_at_head(v11);
//   l->add_at_head(v12);

//   //   l->display();
 

//   task::Task *tau = new task::Task(1,l);
//   task::Task *tau2 = new task::Task(2,l2);
//   task::Task *tau3 = new task::Task(3,l3);


//   tau3->link_two_subtaks(v14,v15);
     
//   tau3->link_two_subtaks(v15,v16);
      
//   tau3->link_two_subtaks(v16,v17);

//   tau2->link_two_subtaks(v1,v2);
//   // tau2->link_two_subtaks(v2,v3);
//   //  tau->link_two_subtaks(v2,v4);
//   tau->link_two_subtaks(v4,v5);
//   tau->link_two_subtaks(v3,v6);
//   tau->link_two_subtaks(v5,v8);
//   tau->link_two_subtaks(v8,v9);
//   tau->link_two_subtaks(v8,v10);
//   tau->link_two_subtaks(v10,v7);
//   tau->link_two_subtaks(v9,v7);
//   tau->link_two_subtaks(v6,v7);
//   tau->link_two_subtaks(v7,v11);
//   tau->link_two_subtaks(v7,v12);


  
//   // tau->to_dot("/tmp/tau.dot");

//   // tau3->to_dot("/tmp/tau3.dot");

//   // task::Subtask *s13=new task::Subtask(13,5,2,COMPUTE,GPU);
//   // tau->link_new_exit(s13);
//   // tau->to_dot("/tmp/after1.dot");
//   // tau2->link_task_after(tau);
//   // tau2->to_dot("/tmp/after.dot");


//   // tau2-> sub_task_heavness(v2);
//   // tau2->heavy_sub_tasks(l2, 0.4);
//   // tau2->source_sub_tasks(l2);
//   // tau->path_NB_subtask(l);
   
//   // tau2->Max_path_NB_subtask();
//   // double avgr=0;
//   // avgr=  tau2-> average_artificial_deadlines(5,9) ;




 

//   // common::List<task::Subtask *> *l=new common::List<task::Subtask *>();
//   common::List<task::Task *>  *tasks= new common::List<task::Task *> ();
//   tasks->add_at_head(new common::Node<task::Task *>(tau2));
//   tasks->add_at_head(new common::Node<task::Task *>(tau3));
  

//   std::cout<<  "task s" <<std::endl;
//   std::cout<<  tasks->size <<std::endl;
//   std::cout<<  tau2->_elems() <<std::endl;
//   tau2->_T(20);
//   // tau2->_D(3);
    
//   std::cout<<tau2->_T()<<std::endl;
//   // std::cout<<tau2->_D()<<std::endl;

//   tau2->to_dot("/tmp/testing.dot");
//   tau2->generate_all_conc_tag_el(CONDITION);
//   printf("here \n");
//   std::cout<<"volume :"<<tau2->volume()<<std::endl;
//   //   tau2->allocat(tasks, 3);
    
//   //double  d_b_min=tau2->min_avr_arti_deadline(tasks);
//   // std::cout<<" d_b_min in the main" <<std::endl;
//   // std::cout<< d_b_min <<std::endl;
//   // tau2->generate_paths();

//   // tau2->utilization();
//   //  std::cout<<"  tau2->utilization()" <<std::endl;
//   // std::cout<<  tau2->utilization() <<std::endl;
//   // L->add_at_tail(t);
    
  
    




// =======
#include "analysis/analysis.hpp"
#include "platform/platform.hpp"

int main(int argc, char ** argv){
  std::cout<<"Hello"<<std::endl;

  task::Taskset *tset = new task::Taskset(5);
  common::List<task::Task *> *list = new common::List<task::Task *>();
//   common::Node<task::Subtask *> *v1=new common::Node<task::Subtask *>( new task::Subtask(1,5,1,COMPUTE,GPU));
// common::Node<task::Subtask *> *v2=new common::Node<task::Subtask *>( new task::Subtask(2,5,2,ALTERNATIVE,GPU));
// common::Node<task::Subtask *> *v3=new common::Node<task::Subtask *>( new task::Subtask(3,5,2,COMPUTE,GPU));
// common::Node<task::Subtask *> *v4=new common::Node<task::Subtask *>( new task::Subtask(4,5,2,COMPUTE,GPU));
// common::Node<task::Subtask *> *v5=new common::Node<task::Subtask *>( new task::Subtask(5,5,2,COMPUTE,GPU));
// common::Node<task::Subtask *> *v6=new common::Node<task::Subtask *>( new task::Subtask(6,5,2,COMPUTE,GPU));
// common::Node<task::Subtask *> *v7=new common::Node<task::Subtask *>( new task::Subtask(7,5,2,CONDITION,GPU));
// common::Node<task::Subtask *> *v8=new common::Node<task::Subtask *>( new task::Subtask(8,5,2,ALTERNATIVE,GPU));
// common::Node<task::Subtask *> *v9=new common::Node<task::Subtask *>( new task::Subtask(9,5,2,COMPUTE,GPU));
// common::Node<task::Subtask *> *v10=new common::Node<task::Subtask *>( new task::Subtask(10,5,2,COMPUTE,GPU));
// common::Node<task::Subtask *> *v11=new common::Node<task::Subtask *>( new task::Subtask(11,5,2,COMPUTE,GPU));
// common::Node<task::Subtask *> *v12=new common::Node<task::Subtask *>( new task::Subtask(12,5,2,COMPUTE,GPU));

 common::Node<task::Subtask *> *v1 = new common::Node<task::Subtask *>( new task::Subtask(1,5,1,COMPUTE,GPU));
 common::Node<task::Subtask *> *v3 = new common::Node<task::Subtask *>( new task::Subtask(3,15,1,COMPUTE,CPU));
 common::Node<task::Subtask *> *v4 = new common::Node<task::Subtask *>( new task::Subtask(4,10,1,COMPUTE,GPU));
 common::Node<task::Subtask *> *v5 = new common::Node<task::Subtask *>( new task::Subtask(5,10,1,COMPUTE,DLA));
 common::Node<task::Subtask *> *v6 = new common::Node<task::Subtask *>( new task::Subtask(6,10,1,COMPUTE,GPU));
 common::Node<task::Subtask *> *v7 = new common::Node<task::Subtask *>( new task::Subtask(7,5,1,COMPUTE,CPU));
 common::Node<task::Subtask *> *v2 =new common::Node<task::Subtask *>( new task::Subtask(4,0,2,CONDITION,GPU));
 common::Node<task::Subtask *> *v8 =new common::Node<task::Subtask *>( new task::Subtask(2,0,2,ALTERNATIVE,GPU));
 common::List<task::Subtask *> *l=new common::List<task::Subtask *>();
 l->add_at_head(v1);
 l->add_at_head(v2);
 l->add_at_head(v3);
 l->add_at_head(v4);
 l->add_at_head(v5);
 l->add_at_head(v6);
 l->add_at_head(v7);
 l->add_at_head(v8);
 // l->add_at_head(v9);
 // l->add_at_head(v10);
 // l->add_at_head(v11);
 // l->add_at_head(v12);

 //   l->display();


 task::Task *tau = new task::Task(1,l);
 tau->link_two_subtasks(v1,v2);
 tau->link_two_subtasks(v2,v3);
 tau->link_two_subtasks(v2,v4);
 tau->link_two_subtasks(v4,v5);
 tau->link_two_subtasks(v3,v5);

 tau->link_two_subtasks(v5,v8);
 tau->link_two_subtasks(v8,v6);
 tau->link_two_subtasks(v8,v7);
 // tau->link_two_subtasks(v8,v10);
 // tau->link_two_subtasks(v10,v7);
 // tau->link_two_subtasks(v9,v7);
 // tau->link_two_subtasks(v6,v7);
 // tau->link_two_subtasks(v7,v11);
 // tau->link_two_subtasks(v7,v12);

list->add_at_tail(new common::Node<task::Task *> (tau));
list->add_at_tail(new common::Node<task::Task *> (tau->copy()));
tset->_list(list);
std::cout << "tset = " << tset->_size() << '\n';
  //  common::Node<task::Subtask *> *v1 = new common::Node<task::Subtask *>( new task::Subtask(1,5,2,COMPUTE,GPU));
  //  common::Node<task::Subtask *> *v2 = new common::Node<task::Subtask *>( new task::Subtask(2,10,2,COMPUTE,GPU));
  //  common::Node<task::Subtask *> *v3 = new common::Node<task::Subtask *>( new task::Subtask(3,0,0,ALTERNATIVE,GPU));
  //  common::Node<task::Subtask *> *v4 = new common::Node<task::Subtask *>( new task::Subtask(4,10,2,COMPUTE,GPU));
  //  common::Node<task::Subtask *> *v5 = new common::Node<task::Subtask *>( new task::Subtask(5,15,2,COMPUTE,GPU));
  //  common::Node<task::Subtask *> *v6 = new common::Node<task::Subtask *>( new task::Subtask(6,5,2,COMPUTE,GPU));
  //  common::Node<task::Subtask *> *v8 = new common::Node<task::Subtask *>( new task::Subtask(8,0,2,CONDITION,GPU));
  //  common::Node<task::Subtask *> *v7 = new common::Node<task::Subtask *>( new task::Subtask(7,10,2,COMPUTE,GPU));


   //   l->display();

  //  tau->link_two_subtasks(v5,v8);
  //  tau->link_two_subtasks(v8,v9);
  //  tau->link_two_subtasks(v8,v10);
  //  tau->link_two_subtasks(v10,v7);
  //  tau->link_two_subtasks(v9,v7);
  //  tau->link_two_subtasks(v6,v7);
  //  tau->link_two_subtasks(v7,v11);
  //  tau->link_two_subtasks(v7,v12);

  tau->generate_all_conc_tag_el(ALTERNATIVE);
  tau->generate_all_conc_tag_el(CONDITION);
  // tau->generate_paths();
  // tau->order_paths();
  //  common::List<task::Subtask *> * entries =tau->list_entries();
  //  entries->display();
   //printf("%d\n",entries->size );
   //std::cout<<"HELOOOOOOOOOOOOOOOOOOOO \n";
  //
  //  for (int i=0;i<tau->_paths()->size;i++){
  //
  //    printf("********************************** \n");
  //    current->display();
  //    current = current->next;
  //  }
   //exit(-1);
   tau->_D(45);
   bool oui =tau->deadline_single_task(PROP);
   printf("deadline assignment is %s\n", oui ? "OK": "Not ok");
   printf("after \n");
   common::Node<common::List<task::Subtask *> *> * current = tau->_paths()->head;
   for (int i=0;i<tau->_paths()->size;i++){

     printf("********************************** \n");
     current->display();
     current = current->next;
   }
   printf("display\n");
   tau->display();
   tau->generate_tagged();
   common::Node<task::Task *> *currtag = tau->_taggeds()->head;
   for(int i = 0;i<tau->_taggeds()->size;i++){
     printf("*********************************TAG %d debut*********************\n",i );
     currtag->el->display();
     printf("*********************************TAG %d fin*********************\n",i );
     currtag= currtag->next;
   }
   //  printf( "DBF(60,BARUAH,paths) = %d\n",tau->dbf(60,BARUAH_APPROX,tau->_concretes()) );
   platform::Platform * platform1 = new platform::Platform();
   common::List<platform::Processor *> *processors = new common::List<platform::Processor*>();
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(1,CPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(2,CPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(3,CPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(4,CPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(10,CPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(11,CPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(5,GPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(6,GPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(7,GPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(8,GPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(9,GPU, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(13,DLA, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(12,DLA, new task::Taskset(1))));
   processors->add_at_tail(new common::Node<platform::Processor*>(new platform::Processor(14,PVA, new task::Taskset(1))));
   platform1->_engines(processors);
   analysis::platform = platform1;
   //tau->to_dot("./dot/tau.dot");
   printf("List of tag\n");
    for (int k = 0; k < analysis::platform->list_tag()->size; k++) {
        printf("%d \n",analysis::platform->list_tag()->get(k)->el);
    }
   printf("BEFORE PROC ORDER\n");
    for (int j = 0; j < analysis::platform->_engines()->size; j++) {
        platform::Processor *curproc = analysis::platform->_engines()->get(j)->el;
        printf("ID : %d, TAG : %d\n",curproc->_id(),curproc->_TAG());
    }

    analysis::platform->order_processors();
    printf("AFTER PROC ORDER\n");
    for (int j = 0; j < analysis::platform->_engines()->size; j++) {
        platform::Processor *curproc = analysis::platform->_engines()->get(j)->el;
        printf("ID : %d, TAG : %d\n",curproc->_id(),curproc->_TAG());
    }

    printf("BEFORE CONCRETES ORDERING\n");
    for (int i = 0; i < tau->_concretes()->size; i++) {
        tau->_concretes()->get(i)->display();
    }
    tau->sort_concretes(PARTIAL,platform1->list_tag());
    printf("AFTER CONCRETES ORDERING\n");
    for (int i = 0; i < tau->_concretes()->size; i++) {
        tau->_concretes()->get(i)->display();
    }
   exit(0);
}
