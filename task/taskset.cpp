#include "taskset.hpp"

#define SORT_UTI_DESC  0
#define SORT_UTI_CROI  1
#define SORT_PREMP_AWARE  2

namespace task{
    int Taskset::_size(){
        return list->size;
    }

    common::List<Task *> *Taskset::_list(){
        return list;
    }

    void Taskset::_list(common::List<Task *> * list){
        this->list = new common::List<Task *>();
        this->list = list;
    }


    Taskset::Taskset(int id){
        this->id = id;
    }
    Taskset::~Taskset(){

    }

    /**
     * Calculate the Least common multiple (LCM) of the 2 given numbers
     * @param a First number
     * @param b Second number
     * @return LCM of a and b
     */
    int Taskset::LCM(int a, int b){
        int x =a;
        int y = b;
        int t;
        while (b != 0) {
            t = b;
            b = a % b;
            a = t;
        }
        return (x*y)/a;
    }

    /**
     * Calculate the hyperperiod
     * @return The hyperperiod
     */
    int Taskset::hyperperiod(){
        int hyper = 1;
        common::Node<Task *> *  curr = list->head;
        for (int i=0; i< list->size ; i++){
            hyper = LCM(hyper,curr->el->_T());
            curr = curr -> next;
        }
        return hyper;

    }
    void Taskset::read(char *arg){

    }
    void Taskset::write(char *arg){

    }

    /**
     * Sort the task list using the given sort method.
     *
     * Sort the task list using the one of the following methods:
     *  - Sort by descending utilisation
     *  - Sort by premption index.
     *
     * @param METHOD The given method (SORT_UTI_DESC or SORT_PREMP_AWARE)
     */
    void Taskset::sort(int METHOD){
        common::List<Task *> * l_t = new common::List<Task *>();
        while (list->size > 0){
            Task * max_tau=list->head->el;
            double max_c;
            switch (METHOD){
                case SORT_UTI_DESC:
                    max_c =  max_tau->utilization();
                    break;
                case  SORT_PREMP_AWARE:
                    max_c = max_tau->preemp_index();
                    break;
                default:
                    std::cout<<"UNKNOW OPTION.. EXITTING"<<std::endl;
                    exit(-1);
            }
            common::Node<Task *> * curr = list->head;

            for (int j=0;j<list->size;j++){
                double  ex_t;
                switch (METHOD){
                    case SORT_UTI_DESC:
                        ex_t =  max_tau->utilization();
                        break;
                    case  SORT_PREMP_AWARE:
                        ex_t = max_tau->preemp_index();
                        break;
                    default:
                        std::cout<<"UNKNOW OPTION.. EXITTING"<<std::endl;
                        exit(-1);
                }
                if ( ex_t> max_c){
                    max_c  = ex_t;
                    max_tau = curr->el;
                }
                curr = curr->next;
            }
            list->remove(max_tau);
            l_t->add_at_tail(new common::Node<Task *  >(max_tau));
        }
        list = l_t;
    }

    /**
     * Calculate the utilization of all the taskset's task.
     * @return The Taskset utilization.
     */
    double Taskset::utilization(){
        double U = 0;
        common::Node<Task *> *  curr = list->head;
        for (int i=0; i< list->size ; i++){
            U +=  curr->el->utilization();
            curr = curr -> next;
        }
        return U;
    }

    void Taskset::display(){
        common::Node<Task *> *  curr = list->head;
        for (int i=0; i< list->size ; i++){
            curr->display();
            curr = curr -> next;
        }
    }

    Taskset* Taskset::copy(){
        Taskset *copy = new Taskset(this->id);
        common::List<Task *> *copylist = new common::List<Task *>();
        for (int i = 0; i < this->list->size; i++) {
            copylist->add_at_tail(new common::Node<Task *>(this->list->get(i)->el->copy()));
        }
        return copy;
    }
}
