#include <iostream>
#include <systemc>

#include "clk_gen.hpp"
#include "clb_one.hpp"
#include "switching_matrix.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

int sc_main(int argc, char *argv[]){

    sc_signal<bool> a,b,c,d,clk_signal,x,y;

    sc_signal<bool> sa,sb,sc,sd,se,sf,sg,sh;
    switch_matrix sw("switching matrix");

    sw.a(sa);
    sw.b(sb);
    sw.c(sc);
    sw.d(sd);
    sw.e(se);
    sw.f(sf);
    sw.g(sg);
    sw.h(sh);

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
    sw.load_switching_config("bitstream/Parse_out.txt",0); // HH CLB

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

    se = 1;
    sc_start(10,SC_US);
    cout << se << sh << endl;

    sh = 0;
    sc_start(10,SC_US);
    cout << se << sh << endl;

	sc_close_vcd_trace_file(tf);

    


    return 0;

}