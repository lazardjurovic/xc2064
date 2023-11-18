#include <systemc>
#include <iostream>
#include <string>

#include "switching_matrix.hpp"

using namespace std;
using namespace sc_core;

SC_MODULE(switching_block){

    //entity ports

    vector<sc_inout<bool>*> ports;

    switching_block(sc_module_name name, string filename, int index) : sc_module(name), sw1("sw1",1), sw2("sw2",2){

        for(int i =0; i< 26;i++){
            ports.push_back(new sc_inout<bool>);
        }

        for(int i =0; i< 8; i++){
            matrix1_signals.push_back(new sc_signal<bool>);
        }

        for(int i =0; i< 8; i++){
            matrix2_signals.push_back(new sc_signal<bool>);
        }

        sw1.bind_ports(matrix1_signals);
        sw2.bind_ports(matrix2_signals);

        sw1.load_switching_config(filename,index);
        sw2.load_switching_config(filename,index);

        // inout ports directly to matrixes

        ports[0]->bind(*matrix1_signals[0]);
        ports[1]->bind(*matrix1_signals[1]);
        ports[2]->bind(*matrix2_signals[0]);
        ports[3]->bind(*matrix1_signals[1]);

        ports[18]->bind(*matrix2_signals[5]);

        ports[25]->bind(*matrix1_signals[7]);
        ports[24]->bind(*matrix1_signals[6]);
        ports[23]->bind(*matrix2_signals[7]);
        ports[22]->bind(*matrix2_signals[6]);

        // signals that bind matrixes together



    }

    ~switching_block(){
        for(auto port : ports){
            delete port;
        }
        for(auto sig: matrix1_signals){
            delete sig;
        }
    }

private:
    switch_matrix sw1,sw2;
    vector<sc_signal<bool>*> matrix1_signals;
    vector<sc_signal<bool>*> matrix2_signals;

};