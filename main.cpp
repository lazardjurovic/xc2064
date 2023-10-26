#include <iostream>
#include <systemc>

#include "clk_gen.hpp"
#include "clb/clb.hpp"
#include "clb_one.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

int sc_main(int argc, char *argv[]){

    sc_signal<bool> a,b,c,d,clk_signal,x,y;

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

    test_clb.load_matrix("bitstream/Parse_out.txt",1); // GH CLB

    // F = ~A*Q + A*B
    // G = B

    sc_start(10,SC_US);

    d = 1;
    sc_start(10, SC_US);
    //cout << x.read() << y.read()<<endl;

    c = 1;
    sc_start(10,SC_US);
    //cout << x.read() << y.read()<<endl;

    b = 1;
    sc_start(10,SC_US);
    //cout << x.read() << y.read()<<endl;

    a = 1;
    sc_start(10,SC_US);
    //cout << x.read() << y.read()<<endl;

    a = 0;
    sc_start(10,SC_US);


    return 0;

}