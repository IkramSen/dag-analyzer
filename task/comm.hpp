#ifndef COMM_HPP
#define COMM_HPP

#include "subtask.hpp"
#include "buffer.hpp"

namespace task {
  class Buffer;
  
  class Communication {
  private : 
    Subtask  * src;
    Subtask  * dst;
    Buffer * buff; 
  public :
    Communication(Subtask  * src,Subtask  * dst, Buffer * buff);
    ~Communication();    
    Subtask * _src();
    void _src(Subtask * s);
    Subtask * _dst();
    void _dst(Subtask * s);
    Buffer * _buff();
    void _buff(Buffer * s);
    void display();
  };
}
#endif
