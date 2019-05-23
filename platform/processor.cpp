#include "processor.hpp"

namespace platform{
    Processor::Processor() {

    }

    Processor::Processor(int id, int tag, task::Taskset* ts) {
        this->ts = ts;
        this->id = id;
        this->TAG = tag;
    }

    void Processor::_id(int id){
        this->id = id;
    }

    int Processor::_id(){
        return id;
    }

    void Processor::_ts(task::Taskset *ts){
        this->ts = ts;
    }

    task::Taskset *Processor::_ts(){
        return ts;
    }

    void Processor::_TAG(int tag){
        this->TAG = tag;
    }

    int Processor::_TAG(){
        return TAG;
    }

    Processor* Processor::copy() {
        Processor *copy = new Processor();
        copy->_id(this->id);
        copy->_ts(this->ts->copy());
        copy->_TAG( this->TAG);
        return  copy;
    }
}
