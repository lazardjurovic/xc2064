#include <iostream>
#include <systemc>

#include "clk_gen.hpp"
#include "clb/clb.hpp"

using namespace std;
using namespace sc_core;

int sc_main(int argc, char *argv[]){

    sc_signal<bool> a,b,c,d,clk,x,y;

    clb cll("clb1");

    cll.a(a);
    cll.b(b);
    cll.c(c);
    cll.d(d);
    cll.clk(clk);
    cll.x(x);
    cll.y(y);

    cll.load_clb_matrix("bitstream/Parse_out.txt",0);

    sc_start(10, SC_US);

    return 0;

}