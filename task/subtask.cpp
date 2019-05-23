#include "subtask.hpp"
#include <string>
namespace task {
  Subtask::Subtask(int id, int C, int PC, int type, int tag){
    this->id=id;
    this->C=C;
    this->PC=PC;
    this->type=type;
    this->TAG=tag;
    this->label = "v"+ std::to_string(id) ;
    }
  Subtask::~Subtask(){}
  void Subtask::display(){
    std::cout<<"[ID:"<<id<<"-"<<label<<" ,C:"<<C<<", PC:"<<PC<<", type:"<<type<<", TAG:"<<TAG<<"]"<<std::endl;
  }

  Subtask * Subtask::clone() {
      return new Subtask(this->id,this->C,this->PC,this->type,this->TAG);
  }

  void Subtask::_label(std::string str){
    this->label=str;
  }
  std::string  Subtask::_label(){return label;}
  int Subtask::_id(){return id;}
  int Subtask::_C(){return C;}
  int Subtask::_PC(){return PC;}
  int Subtask::_type(){return type;}
  // int Subtask::_D(){return D;}
  // int Subtask::_O(){return O;}
  int Subtask::_TAG(){return TAG;}

  void Subtask::_C(int c){C=c;}
  void Subtask::_PC(int pc){PC=pc;}
  void Subtask::_TAG(int tag){TAG=tag;}
  void Subtask::_type(int t){type=t;}

 
}
