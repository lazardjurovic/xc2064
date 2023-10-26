#include <iostream>
#include <systemc>

#include "clk_gen.hpp"
#include "clb/clb.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

int sc_main(int argc, char *argv[]){

    sc_signal<bool> a,b,c,d,clk_signal,x,y;

    clb test_clb("clb");
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
    test_clb.load_clb_matrix("bitstream/Parse_out.txt",0);

    sc_start(1, SC_US);
    
    cout << x << y<<endl;

    return 0;

}