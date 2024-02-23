#include <iostream>
#include <systemc>

//#define DEBUG
#define PIN_COUNT 54

#include "clk_gen.hpp"
#include "clb_one.hpp"
#include "switching_matrix.hpp"
#include "pip.hpp"
#include "switching_block.hpp"
#include "clb_pips.hpp"
#include "fpga.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

int sc_main(int argc, char *argv[]){

    sc_report_handler::set_actions (SC_WARNING, SC_DO_NOTHING);
    string *bitstream_file;

    if(argc>=2){
        char* arg_name = argv[1];
        bitstream_file = new string(arg_name);
    }else{
        bitstream_file = new string("bitstream/Parse_out.txt");
    }

    fpga device("xc2064",*bitstream_file);
    
    //generating stimuli

    sc_trace_file *tf;
    tf = sc_create_vcd_trace_file("tracefile");
    tf->set_time_unit(100,SC_NS);

    vector<sc_signal_resolved*> pin_signals;

    for(int i = 0; i<PIN_COUNT; i++){
        pin_signals.push_back(new sc_signal_resolved);
    }

    device.bind_ports(pin_signals);

    for(int i = 0; i< PIN_COUNT; i++){
        sc_trace(tf,*pin_signals[i], ("Pin " + to_string(i)));
    }

    // generate some random stimuli

    pin_signals[5]->write(SC_LOGIC_0);
    pin_signals[20]->write(SC_LOGIC_0);
    pin_signals[32]->write(SC_LOGIC_0);
    pin_signals[11]->write(SC_LOGIC_0);

    sc_start(10,SC_NS);

    pin_signals[5]->write(SC_LOGIC_1);
    pin_signals[20]->write(SC_LOGIC_1);
    pin_signals[32]->write(SC_LOGIC_1);
    pin_signals[11]->write(SC_LOGIC_1);

    sc_start(10,SC_NS);

    // close vcd and end simulation

	sc_close_vcd_trace_file(tf);

    sc_stop();

    cout << endl << "Simulation ended."<<endl;


    return 0;

}