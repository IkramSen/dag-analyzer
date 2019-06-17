#include "common.hpp"

//#define DEBUG


void fatal_error(int ErrorCode, std::string Message){
   std::cerr << "\033[1;31m ERROR CODE ("+std::to_string(ErrorCode)+"): \033[0m ";
   std::cerr << Message  << std::endl;
  exit(-1);
}


void PRINT_DEBUG(std::string str){
#ifdef DEBUG
  std::cout << "\033[1;34m PRINT_DEBUG : \033[0m ";
  std::cout << str << std::endl;
#endif
}


void PRINT_WARNING(std::string str){
#ifdef DEBUG
  std::cout << "\033[1;32m PRINT_WARNING : \033[0m ";
  std::cout << str << std::endl;
#endif
}
