#ifndef FPGA_HPP
#define FPGA_HPP

#include <systemc>
#include <iostream>
#include <string>
#include <vector>

#include "clk_gen.hpp"
#include "switching_block.hpp"
#include "clb_one.hpp"

using namespace std;
using namespace sc_core;

#define CLB_NUMBER 64
#define SWITCHING_BLOCK_NUMBER 49

SC_MODULE(fpga){

    
    sc_port<sc_signal_inout_if<sc_logic>> north[16];
    sc_port<sc_signal_inout_if<sc_logic>> south[16];
    sc_port<sc_signal_inout_if<sc_logic>> east[14];
    sc_port<sc_signal_inout_if<sc_logic>> west[8];
    

    fpga(sc_module_name name, string bitstream_file) : sc_module(name){
        
        #ifdef DEBUG
        cout << "Creating fpga object."<<endl;
        cout << "Loading bitstream from file " << bitstream_file << endl;
        #endif

        for(int i =0; i<CLB_NUMBER;i++){
            cout << endl;
            cout << "Building CLB number : " << i << endl;
            cout << "---------------------------------------------------------" << endl;
            clbs.push_back(new clb_one("clb"));
            clbs[i]->load_config(bitstream_file,i);
        }

        for(int i = 0; i< SWITCHING_BLOCK_NUMBER; i++){
            switching_blocks.push_back(new switching_block("SW_BLK",bitstream_file,i));
            // bind ports
        }

    }

    ~fpga(){
        #ifdef DEBUG
        cout << "Deleting fpga object."<<endl;
        #endif

        for(int i =0; i< clbs.size();i++){
            delete clbs[i];
        }

    }

    void bind_ports(vector<sc_signal_resolved*>pins){

        for(int i=0; i<16; i++){
            north[i].bind(*pins[i]);
        }
        for(int i=0; i<16; i++){
            south[i].bind(*pins[16+i]);
        }
        for(int i= 0; i<14; i++){
            east[i].bind(*pins[32+i]);
        }
        for(int i= 0; i<8; i++){
            west[i].bind(*pins[46+i]);
        }

    }

private:

    vector<clb_one*> clbs;
    vector<switching_block*> switching_blocks;

    void connect_internals(clb_one *clb, switch_matrix *sw){ // add PIPs


    }

    void read_block(){
        //connect_internals();
    }

};

#endif