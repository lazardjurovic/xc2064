#include <systemc>
#include <iostream>

#include "pip_new.hpp"
#include "../pip.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

SC_MODULE(pip_test){

    sc_port<sc_signal_inout_if<sc_logic>> a,b;
    sc_in<bool> cntrl;

    pip_test(sc_module_name name) : sc_module(name) , pip_a("pip_a"), pip_b("pip_b"){
        
        pip_a.control(cntrl);
        pip_b.control(cntrl);
        
        pip_a.ports[1](sig);
        pip_b.ports[1](sig);

        pip_a.ports[0](a);
        pip_a.ports[2](i);
        pip_a.ports[3](j);

        pip_b.ports[0](k);
        pip_b.ports[2](b);
        pip_b.ports[3](l);

    }   

private:
    pip_new pip_a,pip_b;
    sc_signal_resolved sig;
    sc_signal<sc_logic> i,j,k,l;
};