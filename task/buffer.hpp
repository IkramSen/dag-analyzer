#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include "subtask.hpp"
#include "task.hpp"

namespace task {

  class Buffer {

  private :
    std::string name;
    std::string type;
    int size;
    std::string mutex_name;
    
  public: 

    Buffer(std::string name,  std::string type,  int size);
    ~Buffer();


    
    std::string _mutex_name();
    void _mutex_name( std::string str);

    
    std::string _name();
    void _name( std::string str);

    std::string _type();
    void _type( std::string str);

    int _size();
    void _size(int size);
    void display();

    
  };


}


#endif 
