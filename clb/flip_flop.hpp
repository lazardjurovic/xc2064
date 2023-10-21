#include <systemc>
#include <iostream>

using namespace sc_core;
using namespace std;

SC_MODULE(flip_flop){

// entity ports

    sc_in<bool> clk;
    sc_in<bool> s, d, r;
    sc_out<bool> q;

    void ff_process(){
        bool prev_d = false;

        while(true){
            wait();

            if(clk.posedge()){
                
                if(s.read() == 1){
                    prev_d = 1;
                }else if(r.read() == 1){
                    prev_d = 0;
                }else{
                    prev_d = d.read();
                }
                q.write(prev_d);
            }
        }
    }

    SC_CTOR(flip_flop){
        SC_THREAD(ff_process);
        sensitive << clk.pos();
    }

};