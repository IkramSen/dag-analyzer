#include "subtask.hpp"
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
  Subtask::Subtask(int id, int C, int PC, int type, int tag){
    this->id=id;
    this->C=C;
    this->PC=PC;
    this->type=type;
    this->TAG=tag;
    this->label = "v"+ std::to_string(id) ;
  }
  
  /** 
   * The desctructor of the subtask 
   */ 
  Subtask::~Subtask(){}

  /**
   * Displays the current subtask 
   */
  void Subtask::display(){
    std::cout<<"[ID:"<<id<<"-"<<label<<" ,C:"<<C<<", PC:"<<PC<<", type:"<<type<<", TAG:"<<TAG<<"]"<<std::endl;
  }

  /** 
   * This function creates a new subtask and copy the same parameters as the current 
   */ 
  Subtask * Subtask::clone() {
    return new Subtask(this->id,this->C,this->PC,this->type,this->TAG);
  }
/**  
   * setter of label 
   * @param label The label to set 
   */
  void Subtask::_label(std::string str){
    this->label=str;
  }
  /** 
 Getter of label 
*/ 
  std::string  Subtask::_label(){
    return label;
  }
  /** 
 Getter of id 
*/ 
  int Subtask::_id(){
    return id;
  }
  /** 
 Getter of G 
*/ 
  int Subtask::_C(){
    return C;
  }
  /** 
 Getter of PC 
*/ 
  int Subtask::_PC(){
    return PC;
  }
  /** 
 Getter of type 
*/ 
  int Subtask::_type(){
    return type;
  }
  
  // int Subtask::_D(){return D;}
  // int Subtask::_O(){return O;} 

  /** 
 Getter of TAG 
*/ 
  int Subtask::_TAG(){
    return TAG;
  }

  /**  
   * setter of C 
   * @param C The C to set 
   */
  void Subtask::_C(int c){
    C=c;
  }
  /**  
   * setter of PC 
   * @param PC The PC to set 
   */
  void Subtask::_PC(int pc){
    PC=pc;
  }
  /**  
   * setter of TAG 
   * @param TAG The TAG to set 
   */
  void Subtask::_TAG(int tag){
    TAG=tag;
  }

  /**  
   * setter of type 
   * @param type The type to set 
   */
  void Subtask::_type(int t){
    type=t;
  }
}
