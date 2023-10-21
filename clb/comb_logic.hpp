#include <systemc>
#include <iostream>
#include "lut3on1.hpp"

using namespace sc_core;
using namespace std;

SC_MODULE(comb_logic){

//entity ports
    sc_in<bool> a, b, c, d, q;
    sc_out<bool> f, g;

    SC_CTOR(comb_logic){
        SC_THREAD(proc_comb);

        lut3on1 upper("upper lut");
        lut3on1 lower("lowe lut");

        //routing inputs to lut3on1s
        upper.a(mux1_out);
        upper.b(mux2_out);
        upper.c(mux3_out);

        lower.a(mux4_out);
        lower.b(mux5_out);
        lower.c(mux6_out);

        //routing outputs
        upper.out(f);
        lower.out(g);

    }

    void proc_comb(){

        while(true){

            //upper lut muxes
            if(mux_sels[0] == 1){
                mux1_out = a;
            }else{
                mux1_out = b;
            }

            if(mux_sels[1] == 1){
                mux2_out = b;
            }else{
                mux2_out = c;
            }

            if(mux_sels[2] == 0 && mux_sels[3] == 0){
                mux3_out = c;

            }else if(mux_sels[2] == 0 && mux_sels[3] == 1){
                mux3_out = d;

            }else if(mux_sels[2] == 1 && mux_sels[3] == 0){
                mux1_out = q;
            }

            //lower lut muxes
            if(mux_sels[4] == 1){
                mux1_out = a;
            }else{
                mux1_out = b;
            }

            if(mux_sels[5] == 1){
                mux2_out = b;
            }else{
                mux2_out = c;
            }

            if(mux_sels[6] == 0 && mux_sels[7] == 0){
                mux3_out = c;

            }else if(mux_sels[6] == 0 && mux_sels[7] == 1){
                mux3_out = d;

            }else if(mux_sels[6] == 1 && mux_sels[7] == 0){
                mux1_out = q;
            }

        }

    }

    void setup_comb_logic();

private:
    bool mux_sels[8];
    sc_signal<bool> mux1_out, mux2_out, mux3_out, mux4_out, mux5_out, mux6_out;
    int addr1, addr2;

};