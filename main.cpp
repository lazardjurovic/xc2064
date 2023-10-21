#include <iostream>
#include <systemc>

#include "clk_gen.hpp"
#include "clb/clb.hpp"

using namespace std;
using namespace sc_core;

int sc_main(int argc, char *argv[]){

/*
    sc_signal<bool> clk;
    sc_signal<bool> s, d, k, r;
    sc_signal<bool> q;
    
    flip_flop dff("DFF");
    dff.clk(clk);
    dff.s(s);
    dff.d(d);
    dff.r(r);
    dff.q(q);

    clk_gen gen("GEN");
    gen.clk(clk);

*/


    sc_start(10, SC_US);

    return 0;

}