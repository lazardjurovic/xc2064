#ifndef SWITCHING_BLOCK_HPP
#define SWITCHING_BLOCK_HPP

#include <systemc>
#include <iostream>
#include <string>
#include <vector>

#include "switching_matrix.hpp"
#include "pip.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

#define ND_PIPS_COUNT 11
#define PIP_SIGNALS_COUNT 19
#define SWITCH_BOX_PORTS 24

SC_MODULE(switching_block){

    //entity ports

    sc_port<sc_signal_inout_if<sc_logic>> ports[SWITCH_BOX_PORTS];

    switching_block(sc_module_name name, string filename, int index) : sc_module(name), sw1("sw1",1), sw2("sw2",2){

        sw1.load_switching_config(filename,index);
        sw2.load_switching_config(filename,index);
        load_pip_nd_controls(filename,index);

        //configure ND PIPs

        for(int i=0 ;i<ND_PIPS_COUNT; i++){
            nd_pips.push_back(new pip("pip"));
            cout << nd_pips[i]->name() << endl;
        }

        for(int i =0; i<PIP_SIGNALS_COUNT;i++){
            pip_signals.push_back(new sc_signal_resolved);
        }

        // bind nd_pips

        //pip1
        nd_pips[0]->ports[0](*pip_signals[18]);
        nd_pips[0]->ports[1](*pip_signals[17]);
        nd_pips[0]->ports[2](ports[18]);
        nd_pips[0]->ports[3](ports[19]);

        //pip2
        nd_pips[1]->ports[0](ports[4]);
        nd_pips[1]->ports[1](*pip_signals[0]);
        nd_pips[1]->ports[2](*pip_signals[1]);
        nd_pips[1]->ports[3](*pip_signals[2]);

        //pip3
        nd_pips[2]->ports[0](*pip_signals[3]);
        nd_pips[2]->ports[1](*pip_signals[4]);
        nd_pips[2]->ports[2](*pip_signals[5]);
        nd_pips[2]->ports[3](*pip_signals[6]);

        //pip4
        nd_pips[3]->ports[0](*pip_signals[5]);
        nd_pips[3]->ports[1](*pip_signals[7]);
        nd_pips[3]->ports[2](*pip_signals[8]);
        nd_pips[3]->ports[3](*pip_signals[9]);

        //pip5
        nd_pips[4]->ports[0](*pip_signals[10]);
        nd_pips[4]->ports[1](*pip_signals[11]);
        nd_pips[4]->ports[2](*pip_signals[8]);
        nd_pips[4]->ports[3](ports[14]);

        //pip6
        nd_pips[5]->ports[0](*pip_signals[0]);
        nd_pips[5]->ports[1](*pip_signals[12]);
        nd_pips[5]->ports[2](*pip_signals[10]);
        nd_pips[5]->ports[3](*pip_signals[4]);

        //pip7
        nd_pips[6]->ports[0](ports[5]);
        nd_pips[6]->ports[1](ports[8]);
        nd_pips[6]->ports[2](*pip_signals[13]);
        nd_pips[6]->ports[3](*pip_signals[12]);

        //pip8
        nd_pips[7]->ports[0](*pip_signals[13]);
        nd_pips[7]->ports[1](ports[10]);
        nd_pips[7]->ports[2](ports[13]);
        nd_pips[7]->ports[3](*pip_signals[14]);

        //pip9
        nd_pips[8]->ports[0](ports[6]);
        nd_pips[8]->ports[1](ports[7]);
        nd_pips[8]->ports[2](*pip_signals[15]);
        nd_pips[8]->ports[3](*pip_signals[16]);

        //pip10
        nd_pips[9]->ports[0](*pip_signals[15]);
        nd_pips[9]->ports[1](ports[9]);
        nd_pips[9]->ports[2](ports[12]);
        nd_pips[9]->ports[3](*pip_signals[11]);

        //pip11
        nd_pips[10]->ports[0](*pip_signals[16]);
        nd_pips[10]->ports[1](ports[11]);
        nd_pips[10]->ports[2](ports[15]);
        nd_pips[10]->ports[3](*pip_signals[17]);

        //binding nd_pip control signals

        for(int i =0; i<ND_PIPS_COUNT;i++){
            nd_control_signals.push_back(new sc_signal<bool>);
            nd_control_signals[i]->write(nd_controls[i]);
            nd_pips[i]->control(*nd_control_signals[i]);
        }

        //binding switching matrixes

        //swithing matrix 1
        sw1.ports[0](ports[0]);
        sw1.ports[1](ports[1]);
        sw1.ports[2](*pip_signals[16]);
        sw1.ports[3](*pip_signals[6]);
        sw1.ports[4](ports[17]);
        sw1.ports[5](*pip_signals[18]);
        sw1.ports[6](ports[22]);
        sw1.ports[7](ports[23]);

        //switching matrix 2

        sw2.ports[0](ports[3]);
        sw2.ports[1](ports[4]);
        sw2.ports[2](*pip_signals[9]);
        sw2.ports[3](*pip_signals[14]);
        sw2.ports[4](*pip_signals[16]);
        sw2.ports[5](ports[16]);
        sw2.ports[6](ports[20]);
        sw2.ports[7](ports[21]);

        #ifdef DEBUG
        cout << "Created switching block." << endl;
        #endif

    }

    void bind_ports(vector<sc_signal_resolved*> north, vector<sc_signal_resolved*> south,vector<sc_signal_resolved*> east, vector<sc_signal_resolved*> west){

        for(int i = 0; i< 7; i++){
            ports[i].bind(*north[i]);
        }
        for(int i = 0; i< 7; i++){
            ports[12+i].bind(*south[i]);
        }
        for(int i = 0; i<5; i++){
            ports[7+i].bind(*east[i]);
        }
        for(int i =0; i<5;i++){
            ports[19+i].bind(*west[i]);
        }

    }

    ~switching_block(){
        for(auto pip: nd_pips){
            delete pip;
        }
        for(auto sig : pip_signals){
            delete sig;
        }
    }

private:

    void load_pip_nd_controls(string filename, int index){
    
    ifstream file(filename);
    string line;

    if(file.is_open()){
        
        int line_cnt = 0;

        while(getline(file,line)){
            if(line_cnt == index){
                break;
            }
                line_cnt++;
            }

        file.close();
    }else{
        cout << "Unable to open file " << filename << endl; 
    }

    vector<bool> line_bin = string_to_bin_vector(line);

    // moved tmp_pip_connections[28] to clb_pips.hpp

    bool tmp_nd_controls[11] = { line_bin[133], // 1
                                    line_bin[125], // 2
                                    line_bin[117], // 3
                                    line_bin[109], // 4
                                    line_bin[101], // 5
                                    line_bin[93], //  6
                                    line_bin[85], //  7
                                    line_bin[61], //  8
                                    line_bin[53], //  9
                                    line_bin[45], //  10
                                    line_bin[29] //   11

    };    

   // copy_array(tmp_pip_connections,pip_connections,28);
    copy_array(tmp_nd_controls,nd_controls,11);

    }

    switch_matrix sw1,sw2;
    //bool pip_connections[28];
    bool nd_controls[11];

    vector<sc_signal_resolved*> pip_signals;
    vector<sc_signal<bool>*> nd_control_signals;

    vector<pip*> nd_pips;


};

#endif