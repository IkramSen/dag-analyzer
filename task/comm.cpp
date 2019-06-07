#include "comm.hpp"


namespace task {
  
  /**
   * Constructor of the class Communication
   * @param src The source subtask 
   * @param dst The destination subtask 
   * @param buff the communication buffer 
   */
  Communication::Communication(Subtask  * src,Subtask  * dst, Buffer * buff){
    this-> src = src;
    this->dst = dst;
    this->buff = buff;
  }
  
  /** 
   * The destructor 
   */
  Communication::~Communication(){

  }

  /** 
      Getter of buff 
  */ 
  Buffer * Communication::_buff(){
    return buff;
  }

  /**  
   * setter of buff 
   * @param buff The buffer to set 
   */
  void Communication::_buff(Buffer * s){
    this->buff =s ; 
  }
  
  /**
   * getter of src 
   */
  Subtask * Communication::_src(){
    return this->src;
  }

  
  /**
   * setter of src 
   * @param s The source subtask 
   */
  void Communication::_src(Subtask * s){
    this->src  =s;
  }


  
  /**
   * getter of dst 
   */
  Subtask * Communication::_dst(){
    return this->dst;
  }

  /**
   * setter of dst
   * @param s The dst subtask 
   */
  void Communication::_dst(Subtask * s){
    this->dst  =s;
  }

  void Communication::display(){
    std::cout<<"[" +src->_label()+"---"+buff->_name()+"-->"+dst->_label()+"]\n";

  }
}
