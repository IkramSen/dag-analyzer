#include "task/subtask.hpp"
#include "common/list.hpp"
#include "task/task.hpp"
#include "task/bloc.hpp"
#include "analysis/analysis.hpp"
#include "analysis/limited_preempt.hpp"
#include "platform/platform.hpp"
   
            
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>

void SortD(int *deadlines, int nbr)
{ 
  /* loop index */ 
  int i=0;
  int j = 0; 
  /* intermediate variable*/
  int tmp =0;

  for(i = 1; i <nbr; i++)          //On veut remplir la case i du tableau                            
    {                                                                          
      for(j = i+1; j <= nbr; j++)    //On vérifie s'il n'y a pas de nombre inférieur                    
        {  
	  if(deadlines[i]>deadlines[j]){
	    tmp = deadlines[i];
	    deadlines[i]= deadlines[j];
	    deadlines[j] = tmp;
	  }
   
	}
    }
}
 

int main(int argc, char ** argv){

  int nb=5; 
  //bloc ppp1[1]= {{1,2,0}};
  common::List<task::Bloc *>  *blocs1= new common::List<task::Bloc *> ();
  task::Bloc * bb11= new task::Bloc(1,2,100,0); // id, lengh, pc, blocage
  //task::Bloc * bb12= new task::Bloc(2,3,100,0);
  // task::Bloc * bb13= new task::Bloc(3,2,1,0);
  // task::Bloc * bb14= new task::Bloc(4,2,1,0);
  // task::Bloc * bb15= new task::Bloc(5,1,100,0);
  blocs1->add_at_tail(new common::Node<task::Bloc *>(bb11));
  //blocs1->add_at_tail(new common::Node<task::Bloc *>(bb12));
  // blocs1->add_at_tail(new common::Node<task::Bloc *>(bb13));
  // blocs1->add_at_tail(new common::Node<task::Bloc *>(bb14));
  // blocs1->add_at_tail(new common::Node<task::Bloc *>(bb15));
 
 
  task::Task * tau_1 = new task::Task(1,2,8,8,0, blocs1); //int id, int C, int D, int T, int q, bloc *ppp 
  // bloc ppp2[2]= {{1,3,3}, {2,1,0}}; 
  common::List<task::Bloc *>  *blocs2= new common::List<task::Bloc *> ();
  task::Bloc * bb21= new task::Bloc(1,1,1,0);
  task::Bloc * bb22= new task::Bloc(2,3,100,0);
  // task::Bloc * bb23= new task::Bloc(3,2,100,0);
  // task::Bloc * bb24= new task::Bloc(4,2,100,0);
  blocs2->add_at_tail(new common::Node<task::Bloc *>(bb21));
  blocs2->add_at_tail(new common::Node<task::Bloc *>(bb22));
  // blocs2->add_at_tail(new common::Node<task::Bloc *>(bb23));
  // blocs2->add_at_tail(new common::Node<task::Bloc *>(bb24));
  task::Task *tau_2 = new task::Task(2,4,10,20,0,blocs2);

  // bloc ppp3[1]= {{1,2,0}};
  common::List<task::Bloc *>  *blocs3= new common::List<task::Bloc *> ();
  task::Bloc * bb31= new task::Bloc(1,2,100,0);
  // task::Bloc * bb32= new task::Bloc(2,2,0,0);
  // task::Bloc * bb33= new task::Bloc(3,1,100,0);
  //task::Bloc * bb34= new task::Bloc(4,2,100,0);
  blocs3->add_at_tail(new common::Node<task::Bloc *>(bb31));
  //blocs3->add_at_tail(new common::Node<task::Bloc *>(bb32));
  //blocs3->add_at_tail(new common::Node<task::Bloc *>(bb33));
  // blocs3->add_at_tail(new common::Node<task::Bloc *>(bb34));
  task::Task *tau_3 = new task::Task(3,2,15,25,0,blocs3);

 
  // // bloc ppp4[4]= {{1,2,1}, {2,2,0}, {3,2,2}, {4,1,0}};
   // common::List<task::Bloc *>  *blocs4= new common::List<task::Bloc *> ();
   // task::Bloc * bb41= new task::Bloc(1,2,1,0);
   // task::Bloc * bb42= new task::Bloc(2,2,2,0);
   // task::Bloc * bb43= new task::Bloc(3,2,3,0);
   // task::Bloc * bb44= new task::Bloc(4,1,3,0);
   // task::Bloc * bb45= new task::Bloc(5,2,1,0);
   // task::Bloc * bb46= new task::Bloc(6,3,100,0);
 
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb41));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb42));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb43));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb44));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb45));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb46));
   // task::Task *tau_4 = new task::Task(4,12,30,35,0,blocs4);


 common::List<task::Bloc *>  *blocs4= new common::List<task::Bloc *> ();
   task::Bloc * bb41= new task::Bloc(1,2,1,0);
   task::Bloc * bb42= new task::Bloc(2,2,100,0);
   // task::Bloc * bb43= new task::Bloc(3,2,3,0);
   // task::Bloc * bb44= new task::Bloc(4,1,3,0);
   // task::Bloc * bb45= new task::Bloc(5,2,1,0);
   // task::Bloc * bb46= new task::Bloc(6,3,100,0);
 
   blocs4->add_at_tail(new common::Node<task::Bloc *>(bb41));
   blocs4->add_at_tail(new common::Node<task::Bloc *>(bb42));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb43));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb44));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb45));
   // blocs4->add_at_tail(new common::Node<task::Bloc *>(bb46));
   task::Task *tau_4 = new task::Task(4,4,30,35,0,blocs4);

  // //bloc ppp5[2]= {{1,2,4}, {2,1,0}};
   common::List<task::Bloc *>  *blocs5= new common::List<task::Bloc *> ();
   task::Bloc * bb51= new task::Bloc(1,2,4,0);
   task::Bloc * bb52= new task::Bloc(2,1,100,0);
   blocs5->add_at_tail(new common::Node<task::Bloc *>(bb51));
   blocs5->add_at_tail(new common::Node<task::Bloc *>(bb52));
   task::Task *tau_5 = new task::Task(5,3,50, 50,0,blocs5);

 
  // int Q1= tau_1->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_1->_q(Q1);
  // int Q2= tau_2->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_2->_q(Q2);
  // int Q3= tau_3->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_3->_q(Q3);
  // int Q4= tau_4->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_4->_q(Q4);
  // int Q5= tau_5->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_5->_q(Q5);
  // int Q6= tau_6->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_6->_q(Q6);
  // int Q7= tau_7->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_7->_q(Q7);
  // int Q8= tau_8->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_8->_q(Q8);
  // int Q9= tau_9->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_9->_q(Q9);
  // int Q10= tau_10->compute_LEN_NPR(tasks, deadlines, nb);
  // tau_10->_q(Q10);

  //std::cout<< "Q1  = " << Q1  <<"** "<< "Q2  = "<<Q2 <<"** "<<"Q3  = "<<Q3<< std::endl;
 
  
  // int Q1= tau_1->Optimal_Selection_PPP(tau_1->_q(Q1));
  
  // int Q2= tau_2->Optimal_Selection_PPP(tau_2->_q(Q2));
  //  bool OpSel2= tau_2->Optimal_Selection_PPP(tau_2->_q(),blocs2);
  // printf("le resultat de la selection optimal des points des preemption est :  %d \n", OpSel2);
  
  // int Q3= tau_3->Optimal_Selection_PPP(tau_3->_q(Q3));

   //  int OpSel= tau_4->Optimal_Selection_PPP(8,blocs4);
   // printf("le resultat de la selection optimal des points des preemption pour la tache 4 est :  %d \n", OpSel);
  
  // int Q5= tau_5->Optimal_Selection_PPP(tau_5->_q(Q5));
  
  // int Q6= tau_6->Optimal_Selection_PPP(tau_6->_q(Q6));
  
  // int Q7= tau_7->Optimal_Selection_PPP(tau_7->_q(Q7));
  
  // int Q8= tau_8->Optimal_Selection_PPP(tau_8->_q(Q8));
  // bool OpSel8= tau_8->Optimal_Selection_PPP(tau_8->_q(),blocs8);
  //  printf("le resultat de la selection optimal des points des preemption est :  %d \n", OpSel8);
  
  // int Q9= tau_9->Optimal_Selection_PPP(tau_9->_q(Q9));
  
  // int Q10= tau_10->Optimal_Selection_PPP(tau_10->_q(Q10));
  


   
  // std::cout<< "Q2  = " << Q2  <<std::endl;
  // std::cout<< "Q3  = " << Q3  <<std::endl;
  // std::cout<< "Q4  = " << Q4  <<std::endl;
  // std::cout<< "Q5  = " << Q5  <<std::endl;
  // std::cout<< "Q6  = " << Q6  <<std::endl;
  // std::cout<< "Q7  = " << Q7  <<std::endl;
  // std::cout<< "Q8  = " << Q8  <<std::endl;
  // std::cout<< "Q9  = " << Q9  <<std::endl;
  // std::cout<< "Q10  = " << Q10 <<std::endl;
 
printf("******************* begin platforms ******************** \n"); 
  common::List<platform::Platform *> * sols;
  platform::Platform * current_sol;


  sols  = new common::List<platform::Platform *>();  

  //  task::Task * tau_1 = new task::Task(0,6,10,15);
  // task::Task * tau_2 = new task::Task(1,5,10,15);
  // task::Task * tau_3 = new task::Task(2,5,10,15);
    printf("******************* add task to tss ******************** \n"); 
   task::Taskset * tss = new task::Taskset();
   tss->add(tau_1);  
   tss->add(tau_2);
   tss->add(tau_3);   
   tss->add(tau_4);   
   tss->add(tau_5);   
   // tss->add(tau_6);   
   // tss->add(tau_7);   
   // tss->add(tau_8);   
   // tss->add(tau_9);   
   // tss->add(tau_10);   

  
printf("******************* begin processors******************** \n"); 
  common::List<platform::Processor *> *engines = new    common::List<platform::Processor *>();
    
  platform::Processor *p_1 = new platform::Processor(0);
  platform::Processor *p_2 = new platform::Processor(1); 
  

  engines->add_at_head(new common::Node<platform::Processor *>(p_1));
  engines->add_at_head(new common::Node<platform::Processor *>(p_2));
 
  platform::Platform *pl = new platform::Platform();
  pl->_engines(engines) ; 
  current_sol = pl->copy();
  sols = new common::List<platform::Platform *> ();
  generate_all_solutions(tss,pl,2,current_sol,sols);

  /***** eliminer ******/
  pl->eliminer_zero_proc(sols);
  pl->eliminer_zero_proc(sols); 
  for (int i=0;i<sols->size;i++)
      {
      printf("******************* ***************************** \n");  
      sols->get(i)->print_alloc(); 
     }

   common::List<task::Task *>  *tt= new common::List<task::Task *> (); 
   tt->add_at_tail(new common::Node<task::Task *>(tau_1));
   tt->add_at_tail(new common::Node<task::Task *>(tau_2));
   tt->add_at_tail(new common::Node<task::Task *>(tau_3));
   tt->add_at_tail(new common::Node<task::Task *>(tau_4));
   tt->add_at_tail(new common::Node<task::Task *>(tau_5));

  //traitement 
   int nbt=5;
   int *deadlines =  (int *)malloc(nbt * sizeof(int));
   deadlines =  tau_1-> compute_DK(tt, nbt);
   int nbd= nbt*nbt;
   SortD(deadlines,nbd );
   for(int i=1; i<=nbd ; i++){
    std::cout<< "deadlines[i] in the main after sort = " << deadlines[i]  <<std::endl;
   }

  /***** optimal solution *****/

  printf(" ** -----------------Optimal solution ------------------** \n");
  platform::Platform * platessai=  sols->get(1); //une platform
  platform::Platform * optimal_solution= platessai->Optimal_solution(sols ,deadlines,nbt);
  // printf(" ** -----------------The Optimal solution in the main classe ------------------** \n");
  // optimal_solution->print_alloc();

  /***** solution ameliorer ****/
  // printf(" ** -----------------Optimal solution ------------------** \n");
  // platform::Platform * platessai2=  sols->get(1); //une platform
  // platform::Platform * optimal_solution2= platessai2->Optimal_solution_amelior(sols ,deadlines,3 );
  //printf(" ** -----------------The Optimal solution amelior in the main classe ------------------** \n");
  //optimal_solution2->print_alloc();







  /***** delete processeur ******/
  
  // int Q=0;
  // for (int h=0;h<2;h++) //sols->size
  //   {
  //     int C_plat=0;
  //     platform::Platform * plat=  sols->get(h); //une platform

  //     printf("----------------------PLATFORM---------------------------- \n" );
  //     for (int k=0;k<plat->_engines()->size;k++)
  // 	{
  // 	  int C_proc=0;
  // 	  platform::Processor *proc=   plat-> _engines()->get(k);
  // 	  printf(" PROCESSOR [%d] \n",proc->_id() );
  // 	  for (int ik=0;ik<proc->_ts()->_list()->size;ik++)
  // 	    {
  // 	      printf("******* Compute Qi ******* \n");
  // 	      task::Task * ta = proc->_ts()->_list()->get(ik);
  // 	      Q= ta->compute_LEN_NPR(proc->_ts()->_list(), deadlines, 3);
  // 	      proc->_ts()->_list()->get(ik)->_q(Q);
  // 	      std::cout<< "Q[" << ik <<" ]="<<  Q  << std::endl;
 
  // 	      printf("****** Applay optimal selection Method ****** \n");
  // 	      common::List<task::Bloc *>* blocss=   proc->_ts()->_list()->get(ik)->_blocs();
  // 	      int OpSel= ta->Optimal_Selection_PPP( proc->_ts()->_list()->get(ik)->_q(),blocss);
  // 	      C_proc= C_proc+ OpSel;
  // 	    }
  // 	  printf("Comp Time in PROCESSOR [%d]= :  %d \n", proc->_id(), C_proc);
  //         C_plat=C_plat+ C_proc;
  // 	}
  //     printf(" ** ----------------------------------------------------** \n");
  //     printf("Comp Time in PLATFORM [%d]= :  %d \n", h, C_plat);
     
  //   }














  //  printf("*********** MAIN remove_non_feaisible_solutions *************** \n");
  //   remove_non_feaisible_solutions(sols); 
    
  //  for (int j=0;j<sols->size;j++) 
  //    {
  //     printf("***** *******AFTER REMOVE**************** \n");
  //      sols->get(j)->print_alloc();
  //    } 


    
  // This is the original source code !! to be uncommented !!
  // Houssam : Do not delete 
   
   // task::Taskset *tset = new task::Taskset(5);
  // common::List<task::Task *> *list = new common::List<task::Task *>();
    // common::Node<task::Subtask *> *v1 = new common::Node<task::Subtask *>( new task::Subtask(1,5,1,COMPUTE,GPU));
  // common::Node<task::Subtask *> *v2 = new common::Node<task::Subtask *>( new task::Subtask(2,0,1,CONDITION,CPU));
  // common::Node<task::Subtask *> *v2_c = new common::Node<task::Subtask *>( new task::Subtask(22,0,1,CCONDITION,CPU));
  // v2_c->el->_silent_subtask(v2->el);
  // common::Node<task::Subtask *> *v3 = new common::Node<task::Subtask *>( new task::Subtask(3,10,1,COMPUTE,CPU));
  // common::Node<task::Subtask *> *v4 = new common::Node<task::Subtask *>( new task::Subtask(4,10,1,COMPUTE,CPU));
  // common::Node<task::Subtask *> *v5 = new common::Node<task::Subtask *>( new task::Subtask(5,10,1,COMPUTE,CPU));
  // common::Node<task::Subtask *> *v6 = new common::Node<task::Subtask *>( new task::Subtask(6,0,1,ALTERNATIVE,CPU));
  // common::Node<task::Subtask *> *v7 = new common::Node<task::Subtask *>( new task::Subtask(7,0,2,COMPUTE,CPU));
  // common::Node<task::Subtask *> *v8 = new common::Node<task::Subtask *>( new task::Subtask(8,0,2,COMPUTE,CPU));

  // common::List<task::Subtask *> *l=new common::List<task::Subtask *>();
  // l->add_at_head(v1);
  // l->add_at_head(v2);
  // l->add_at_head(v2_c);
  // l->add_at_head(v3);
  // l->add_at_head(v5);
  // l->add_at_head(v6);
  // l->add_at_head(v7); 
  // l->add_at_head(v8);



  // task::Task *tau = new task::Task(1,l);
  // tau->link_two_subtasks(v1,v2);
  // tau->link_two_subtasks(v2,v3);
  // tau->link_two_subtasks(v2,v2_c);
  // tau->link_two_subtasks(v3,v2_c);
  // tau->link_two_subtasks(v2_c,v5);
  // tau->link_two_subtasks(v5,v6);
   // tau->link_two_subtasks(v6,v7);
  // tau->link_two_subtasks(v6,v8);



  // tau->to_dot("/tmp/tt.dot");

  // // Houssam: I need to correct the generaton of the dbf 
  // tau->generate_all_conc_tag_el(ALTERNATIVE);
  // printf("here, passed? 1  \n");
  // task::Taskset *ts = new task::Taskset(-1);
  // tau->_concretes()->get(0)->display();
  // printf("here, passed? 2  Size : %d \n", tau->_concretes()->_size());
  // for (int t=0;t<200;t++){
  //   tau->_concretes()->get(0)->generate_all_conc_tag_el(CONDITION); 
  //   std::cout<<"("<<t<<","<<tau->_concretes()->get(0)->dbf_exact(t,ts)<<")"<<std::endl;     
   
// }
}
