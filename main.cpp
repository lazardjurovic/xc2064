#include <iostream>
#include <systemc>

#define DEBUG

#include "clk_gen.hpp"
#include "clb_one.hpp"
#include "switching_matrix.hpp"
#include "pip.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

int sc_main(int argc, char *argv[]){

    sc_signal<bool> a,b,c,d,clk_signal,x,y;
    sc_signal<bool> clb_out;


    //test of pip
    vector<sc_signal<bool>*> pip_ports;
    sc_signal<bool> pip_control;

    for(int i =0; i<4;i++){
        pip_ports.push_back(new sc_signal<bool>);
    }

    pip pip_dut("pip_dut");
    pip_dut.bind_ports(pip_ports);
    pip_dut.control(pip_control);

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

    return 0;

}