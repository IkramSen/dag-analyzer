#ifndef SUB_TASK_HPP
#define SUB_TASK_HPP

#include <map>
#include <iostream>
#include <string.h>
#include <string>

#define CONDITION 0
#define CCONDITION 4
#define ALTERNATIVE 1
#define COMPUTE 2
#define DUMMY 3

namespace task {
  class Subtask {
  private:
    int id, C, PC, type, TAG;
    double w;
    std::string label;
    Subtask * silent_subtask;
    std::string sema_left;
    std::string sema_right;
    
  public:
    std::string _sema_left();
    void _sema_left( std::string sl);
    std::string _sema_right();
    void _sema_right( std::string sl);

    
    Subtask * _silent_subtask();
    void _silent_subtask( Subtask *  v);

    std::map<std::string,std::string>  * properties;
    int _id();
    int _C();
    int _PC();
    int _type();
    int _TAG();
    void _label(std::string str);
    std::string _label();
    void _C(int c);
    void _PC(int pc);
    void _type(int t);
    void _TAG(int tag);

    Subtask(int id, int C, int PC, int type, int TAG);
    ~Subtask();
    Subtask *clone();
    // void empty();
    // bool is_empty();
    void display();
  };
}
#endif
