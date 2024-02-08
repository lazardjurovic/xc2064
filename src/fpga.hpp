#ifndef FPGA_HPP
#define FPGA_HPP

#include <systemc>
#include <iostream>
#include <string>
#include <vector>

#include "clk_gen.hpp"
#include "switching_matrix.hpp"
#include "clb_one.hpp"

using namespace std;
using namespace sc_core;

SC_MODULE(fpga){

    fpga(sc_module_name name, string bitstream_file) : sc_module(name){
        
        #ifdef DEBUG
        cout << "Creating fpga object."<<endl;
        cout << "Loading bitstream from file " << bitstream_file << endl;
        #endif

        for(int i =0; i<32;i++){
            clbs.push_back(new clb_one("clb"));
            clbs[i]->load_config(bitstream_file,i);
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

private:

    vector<clb_one*> clbs;

    void connect_internals(clb_one *clb, switch_matrix *sw){ // add PIPs


    }

    void read_block(){
        //connect_internals();
    }

};

#endif