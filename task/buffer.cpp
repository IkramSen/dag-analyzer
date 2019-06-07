#include "buffer.hpp"

namespace task {

  /** 
   * Constructor to create a buffer 
   * @param name The variable name of the buffer 
   * @param type The type of the buffer 
   * @param size The size of the buffer if it is an array.  
   */
  Buffer::Buffer(std::string name,  std::string type,  int size){
    this->name = name;
    this->type = type;
    this->size = size;
    this->mutex_name=name+"_mutex";
  }

  /** 
   * Destructor of the current buffer 
   */
  Buffer::~Buffer(){
  }

  /**
   * getter of name 
   */
  std::string Buffer::_name(){
    return this->name;
  }

  /** 
   *  Getter of mutex name 
   */ 
  std::string Buffer::_mutex_name(){
    return this->mutex_name;
  }


  /**  
   * setter of mutex_name 
   * @param mutex_name The mutex_name to set 
   */
  
  void Buffer::_mutex_name(std::string mutex_name){
    this->mutex_name= mutex_name;
  }


  

  
  /**
   * setter of name 
   * @param str The buffer name 
   */
  void Buffer::_name( std::string str){
    this->name = str;
  }

  /**
   * getter of type
   */
  std::string Buffer::_type(){
    return this->type;
  }
  
  /**
   * setter of type
   * @param str The buffer type  
   */
  void Buffer::_type( std::string str){
    this->type = str;
  }
  
  /**
   * getter of size
   */
  int Buffer::_size(){
    return this->size;
  }
  
  /**
   * setter of size 
   * @param size The buffer size  
   */  
  void Buffer::_size(int size){
    this->size = size;
  }

  void Buffer::display(){
    std::cout<<name <<" "<<std::endl;
  }
}
