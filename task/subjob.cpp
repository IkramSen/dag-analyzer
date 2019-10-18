

#include "subtask.hpp"
#include <string>
namespace task {

  Subjob::Subjob(int id, int C, int D, int T, int _abs_r, int j_id) {
      struct subjob * sjob =  (struct subjob *) (malloc(sizeof(struct subjob)));
      this->C=C;
      this->D = D;
      this->nextT = T;
      this->id = id;
      this->_abs_r= _abs_r;
      this->j_id = j_id;
  }

  
}




