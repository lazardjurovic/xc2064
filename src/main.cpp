#include <iostream>
#include <systemc>

//#define DEBUG

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
    
    sc_start(10,SC_NS);

    cout << endl << "Simulation ended."<<endl;
/*
    switching_block sw("switching_block_1","bitstream/Parse_out.txt",0);
    clb_pips cpips("clb_pips","bitstream/Parse_out.txt",0);
    clb_one clb("clb1");
    clb.load_config("bitstream/Parse_out.txt",0);

    vector<sc_signal<bool> *> clb_sigs;

    for(int i =0; i < 7;i++){
        clb_sigs.push_back( new sc_signal<bool>);
    }

    clb.bind_ports(clb_sigs);


    vector<sc_signal_resolved*> sigs;
    vector<sc_signal_resolved*> clb_pip_sigs;

    for(int i = 0; i<24;i++){
        sigs.push_back(new sc_signal_resolved);
        sw.ports[i](*sigs[i]);
    }

    for(auto sig : sigs){
        sig->write(sc_logic_0);
    }

    // testing clb pips
    for(int i = 0; i<22;i++){
        clb_pip_sigs.push_back(new sc_signal_resolved);
        cpips.ports[i](*clb_pip_sigs[i]);
    }

    for(auto sig : clb_pip_sigs){
        sig->write(sc_logic_0);
    }

    sc_start(10,SC_NS);
    
    // test stimuli
    for(int i = 0; i<6;i++){
        sigs[i]->write(sc_logic_1);
    }

    for(int i = 0; i<8;i++){
        clb_pip_sigs[i]->write(sc_logic_1);
    }
    
*/


/*
    // switching matrix for test
    vector<sc_signal<bool>*> sigs;
    for(int i =0; i<8;i++){
            sigs.push_back(new sc_signal<bool>);
    }

    switch_matrix sw("matrix1",1);
    sw.load_switching_config("bitstream/Parse_out.txt",0);
    sw.bind_ports(sigs);

    // clb for test

    clb_one test_clb("clb");
    clk_gen clock("clock");

    clock.clk(clk_signal);

    a = 0;
    b = 0;
    c = 0;
    d = 0;

    test_clb.a(a);
    test_clb.b(b);
    test_clb.c(c);
    test_clb.d(d);
    test_clb.clk(clk_signal);
    test_clb.x(x);
    test_clb.y(y);

    test_clb.load_matrix("bitstream/Parse_out.txt",0); // HH CLB
    
    //sw.load_switching_config("bitstream/Parse_out.txt",0); // HH CLB

    //generating stimuli

    sc_trace_file *tf;
    tf = sc_create_vcd_trace_file("tracefile");
    tf->set_time_unit(100,SC_NS);

    sc_trace(tf,clk_signal, "clk");
    sc_trace(tf,a,"A");
    sc_trace(tf,b,"B");
    sc_trace(tf,c,"C");
    sc_trace(tf,d,"D");
    sc_trace(tf,x,"X");
    sc_trace(tf,y,"Y");

    for(int i = 0; i<=1; i++){
        for(int j = 0; j<=1; j++){
            for(int k = 0; k<=1; k++){
                for(int h = 0; h<=1; h++){
                    a = i;
                    b = j;
                    c = k;
                    d = h;
                    sc_start(10,SC_US);
                }
            }
        }
    }

	sc_close_vcd_trace_file(tf);

    // PIP stimuli

    cout << endl << endl <<"Testing PIP." <<endl;

    pip_control = 1;
    pip_ports[0]->write(1);
    sc_start(10,SC_NS);
    cout << pip_ports[1]->read() << pip_ports[2]->read() << pip_ports[3]->read() <<endl;
    pip_ports[0]->write(0);
    sc_start(10,SC_NS);
    cout << pip_ports[1]->read() << pip_ports[2]->read() << pip_ports[3]->read()<<endl;

    // Switching matrix stimuli

    cout <<endl << endl << "Testing Switvhing matrix." <<endl;

    sigs[0]->write(1);
    sc_start(10,SC_NS);

    */

    return 0;

}