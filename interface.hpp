#ifndef INTERFACE_HPP
#define INDERFACE_HPP

#include <systemc>

using namespace sc_core;

class interface : public sc_interface {

    public: 
        interface(sc_signal<bool>* d ){
                data = d;
        }

    sc_signal<bool>* data;

};

#endif