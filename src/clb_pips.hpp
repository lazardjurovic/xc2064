#include <systemc>
#include <iostream>
#include <vector>
#include "pip.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

#define CLB_PIP_SIGNALS_COUNT 20
#define CLB_PIPS_COUNT 27

SC_MODULE(clb_pips){

    //entity ports
    sc_port<sc_signal_inout_if<sc_logic>> ports[22];
    sc_in<bool> controls[28];

    SC_CTOR(clb_pips){

        for(int i =0; i<CLB_PIPS_COUNT; i++){
            pips.push_back(new pip("pip"));
        }

        for(int i =0; i<CLB_PIP_SIGNALS_COUNT; i++){
            pip_signals.push_back(new sc_signal_resolved);
        }

        //binding all internal pips

        pips[0]->ports[0](ports[1]);
        pips[0]->ports[1](*pip_signals[0]);
        pips[0]->ports[2](*pip_signals[1]);
        pips[0]->ports[3](ports[21]);

        pips[1]->ports[0](ports[3]);
        pips[1]->ports[1](*pip_signals[2]);
        pips[1]->ports[2](*pip_signals[3]);
        pips[1]->ports[3](*pip_signals[0]);

        pips[2]->ports[0](ports[5]);
        pips[2]->ports[1](*pip_signals[4]); // not connected anywhere
        pips[2]->ports[2](*pip_signals[5]);
        pips[2]->ports[3](*pip_signals[2]);

    }
    private:
        vector<sc_signal_resolved*> pip_signals;
        vector<pip*> pips;


};