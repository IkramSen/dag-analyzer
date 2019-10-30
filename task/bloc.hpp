#ifndef BLOC_HPP
#define BLOC_HPP

#include <map>
#include <iostream>
#include <string.h>
#include <string>

namespace task {
  class Bloc {
  private:
    int id, Len, PC, BlocTime;
    //std::string label;
    
  public:
    
    int _id();
    int _Len();
    int _PC();
    int _BlocTime();
    void _Len(int c);
    void _PC(int pc);
    void _BlocTime(int BlocTime);
    Bloc(int id, int Len, int PC, int BlocTime);
    ~Bloc();
    // void empty();
    // bool is_empty();
    void display();
  };
}
#endif
