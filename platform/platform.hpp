#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "../common/list.hpp"
#include "processor.hpp"
namespace platform{
    class Platform{
    private:
        common::List<platform::Processor *> *engines;


    public:
        void _engines(common::List<platform::Processor *> *engines);
        common::List<platform::Processor *> * _engines();
        bool order_processors();
        int nb_proc_tag(int tag);
        common::List<int> *list_tag();
    };
}

#endif