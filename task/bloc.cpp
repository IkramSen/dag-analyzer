#include "bloc.hpp"
#include <string>
namespace task {
  /** 
   * The constructor of the subtask 
   * @param id The subtask id 
   * @param C The subtask execution time 
   * @param PC the subtask preemption cost 
   * @param type The subtask type : it can be either CONDITION, ALTERNATIVE, COMPUTE
   * @param tag The task tag 
   */
  Bloc::Bloc(int idd, int Leng, int Pc, int BlocT){
    this->id=idd;
    this->Len=Leng;
    this->PC=Pc;
    this->BlocTime=BlocT;
  }


  /** 
   * The desctructor of the subtask 
   */ 
  Bloc::~Bloc(){}

  /**
   * Displays the current subtask 
   */
  void Bloc::display(){
    std::cout<<"[ID:"<<id<<" length bloc:"<<Len<<", PC:"<<PC<<", blocage:"<<BlocTime << std::endl;
  }

  /** 
 Getter of id 
*/ 
  int Bloc::_id(){
    return id;
  }
  /** 
 Getter of Len
*/ 
  int Bloc::_Len(){
    return Len;
  }
  /** 
 Getter of PC 
*/ 
  int Bloc::_PC(){
    return PC;
  }

  /** 
 Getter of BlocTime 
*/ 
  int Bloc::_BlocTime(){
    return BlocTime;
  }

  // int Subtask::_D(){return D;}
  // int Subtask::_O(){return O;} 

  /**  
   * setter of Len 
   * @param Len The Len to set 
   */
  void Bloc::_Len(int L){
    Len=L;
  }
  /**  
   * setter of PC 
   * @param PC The PC to set 
   */
  void Bloc::_PC(int p){
    PC=p;
  }

 /**  
   * setter of _BlocTime
   * @param _BlocTime The PC to set 
   */
  void Bloc::_BlocTime(int b){
    BlocTime= b;
  }

}
