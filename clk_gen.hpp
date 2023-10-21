#include <systemc>

using namespace sc_core;

#define CLK_PERIOD 100

SC_MODULE(clk_gen){

//entity ports

    sc_out<bool> clk;

    SC_CTOR(clk_gen){
        SC_THREAD(gen_proc);
    }

    void gen_proc(){

        while(true){
            wait(CLK_PERIOD/2,SC_NS);
            clk = !clk;
        }

    }

};