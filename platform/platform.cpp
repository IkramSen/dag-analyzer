#include "platform.hpp"
namespace platform{
    common::List<Processor *> *Platform::_engines(){
        return engines;
    }

    void Platform::_engines(common::List<Processor *> * engines){
        this->engines = engines;
    }

    bool Platform::order_processors(){
        common::List<Processor *> * l_p = new common::List<Processor *> ();
        common::List<int> *l_t = list_tag();
        while (l_t->size > 0) {
            int tag = l_t->head->el;
            int max_c = nb_proc_tag(tag);
            for (int j = 0; j < l_t->size; j++) {
                int ex_t = nb_proc_tag(l_t->get(j)->el);
                if (ex_t < max_c) {
                    max_c = ex_t;
                    tag = l_t->get(j)->el;
                }
            }
            for (int i = 0; i < engines->size; i++) {
                if (tag == engines->get(i)->el->_TAG()) {
                    l_p->add_at_tail(new common::Node<Processor *>(engines->get(i)->el));
                }
            }
            for(int i = 0 ; i< l_p->size; i++){
                engines->remove(l_p->get(i)->el);
            }
            l_t->remove(tag);
        }
        engines = l_p;
        return true;
    }

    common::List<int> * Platform::list_tag(){
        common::List<int> * ret = new common::List<int>();
        for (int i = 0; i < engines->size ; i++) {
            if(!ret->contains(engines->get(i)->el->_TAG())){
                ret->add_at_tail(new common::Node<int>(engines->get(i)->el->_TAG()));
            }
        }
        return ret;
    }

    int Platform::nb_proc_tag(int tag){
        int ret = 0;
        for (int i = 0; i < engines->size; i++) {
            if(engines->get(i)->el->_TAG() ==tag ){
                ret++;
            }
        }
        return ret;
    }
}