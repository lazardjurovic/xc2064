#include <systemc>
#include <iostream>

using namespace std;
using namespace sc_core;

SC_MODULE(conf_switch){
    //entitiy ports
    sc_inout<bool> a, b; // pins to be connected
    sc_in<bool> c; // control

    SC_CTOR(conf_switch){
        SC_METHOD(proc);
        sensitive << a << b << c;
    }

    void proc(){
         if (c.read() == 1) {
            a.write(b.read());
        } else {
            a.write(0);
            b.write(0);
        }
    }

};