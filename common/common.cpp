#include "common.hpp"


void fatal_error(int ErrorCode, std::string Message){
  std::cerr<<"Error code ("+std::to_string(ErrorCode)+") : "+Message <<std::endl;
  exit(-1);
}


void PRINT_DEBUG(std::string str){
#ifdef DEBUG
  std::cout<<str<<std::endl;
#endif
}
