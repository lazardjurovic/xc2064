#include <systemc>
#include <iostream>
#include <vector>
#include "pip.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

#define CLB_PIP_SIGNALS_COUNT 26
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

        pips[3]->ports[0](ports[0]);
        pips[3]->ports[1](*pip_signals[6]);
        pips[3]->ports[2](*pip_signals[7]);
        pips[3]->ports[3](*pip_signals[8]);

        pips[4]->ports[0](*pip_signals[1]);
        pips[4]->ports[1](*pip_signals[9]);
        pips[4]->ports[2](*pip_signals[10]);
        pips[4]->ports[3](*pip_signals[6]);

        pips[5]->ports[0](ports[2]);
        pips[5]->ports[1](*pip_signals[11]);
        pips[5]->ports[2](*pip_signals[12]);
        pips[5]->ports[3](*pip_signals[9]);

        pips[6]->ports[0](*pip_signals[3]);
        pips[6]->ports[1](*pip_signals[13]);
        pips[6]->ports[2](*pip_signals[14]);
        pips[6]->ports[3](*pip_signals[11]);

        pips[7]->ports[0](ports[4]);
        pips[7]->ports[1](*pip_signals[15]);
        pips[7]->ports[2](*pip_signals[16]);
        pips[7]->ports[3](*pip_signals[13]);

        pips[8]->ports[0](*pip_signals[17]); // not connected anywhere else
        pips[8]->ports[1](*pip_signals[18]);
        pips[8]->ports[2](*pip_signals[19]);
        pips[8]->ports[3](*pip_signals[15]);

        pips[9]->ports[0](*pip_signals[5]);
        pips[9]->ports[1](*pip_signals[20]);
        pips[9]->ports[2](*pip_signals[21]);
        pips[9]->ports[3](*pip_signals[18]);

        pips[10]->ports[0](ports[6]);
        pips[10]->ports[1](*pip_signals[22]);
        pips[10]->ports[2](*pip_signals[23]);
        pips[10]->ports[3](*pip_signals[20]);

        pips[11]->ports[0](ports[7]);
        pips[11]->ports[1](*pip_signals[24]);
        pips[11]->ports[2](*pip_signals[25]);
        pips[11]->ports[3](*pip_signals[22]);

        pips[12]->ports[0](ports[8]);
        pips[12]->ports[1](ports[9]);
        pips[12]->ports[2](*pip_signals[26]); // not connected anywhere else
        pips[12]->ports[3](*pip_signals[24]);

    }
    private:
        vector<sc_signal_resolved*> pip_signals;
        vector<pip*> pips;


};