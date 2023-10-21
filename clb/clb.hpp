#include <systemc>
#include <iostream>

#include "comb_logic.hpp"
#include "flip_flop.hpp"

using namespace sc_core;
using namespace std;

SC_MODULE(clb){

//entity ports

    sc_in<bool> a, b, c, d, clk;
    sc_out<bool> x;
    sc_out<bool> y;

    SC_CTOR(clb){
        SC_THREAD(proc_clb);

        comb_logic comb("comb_logic");
        flip_flop dff("flip_flop");

        // routing ports
        comb.a(a);
        comb.b(b);
        comb.c(c);
        comb.d(d);
        comb.q(q);
        comb.f(f);
        comb.g(g);

        dff.clk(k);
        dff.r(r);
        dff.d(f);
        dff.s(s);
        dff.q(q);

    }

    void proc_clb(){

        while(true){

            if(mux_sels[0]== 1){
                s  = a;
            }else {
                s = f;
            }

            if(mux_sels[1] == 0 && mux_sels[2] == 0){
                k = g;
            }else if(mux_sels[1] == 0 && mux_sels[2] == 1){
                k = c;
            }else if(mux_sels[1] == 1 && mux_sels[2] == 0){
                k = clk;
            }

            if(mux_sels[3] == 1){
                r = d;
            }else{
                r = g;
            }

            if(mux_sels[4] == 0 && mux_sels[5] == 0){
                x = f;
            }else if(mux_sels[4] == 1 && mux_sels[5] == 0){
                x = g;
            }else if(mux_sels[4] == 0 && mux_sels[5] == 1){
                x = q;
            }

            if(mux_sels[6] == 0 && mux_sels[7] == 0){
                y = q;
            }else if(mux_sels[6] == 1 && mux_sels[7] == 0){
                y = g;
            }else if(mux_sels[6] == 0 && mux_sels[7] == 1){
                y = f;
            }
            
        }

    }

private:
    sc_signal<bool> f, g;
    sc_signal<bool> q, k, r, s;
    bool mux_sels[8];

};