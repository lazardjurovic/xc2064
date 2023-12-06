#ifndef PIP_HPP
#define PIP_HPP

#include <systemc>
#include <vector>
#include <iostream>

#include "utils.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

SC_MODULE(pip){

    //entity ports
    sc_port<sc_signal_inout_if<sc_logic>> ports[4];
    sc_in<bool> control;

    SC_CTOR(pip){

        SC_THREAD(proc);
        
        for(int i =0; i<4; i++){
            sensitive << ports[i];
        }
        
        #ifdef DEBUG
        cout << "Created PIP." <<endl;
        #endif

    }

    void proc(){
        while(true){
            wait();
            sc_logic new_state[4] = {sc_logic_0,sc_logic_0,sc_logic_0,sc_logic_0};

            for(int i =0; i<4;i++){
                new_state[i] = ports[i]->read();
            }

            int index_changed = 0;

                for(int i =0; i<4;i++){
                    if(last_state[i]  != new_state[i]){
                        index_changed = i;
                        
                        #ifdef DEBUG
                        cout << "Detected change on " << name() << "on port "<< index_changed <<endl;
                        #endif

                        break;
                    }
                }


            if(control.read() == 1){

                // update all ports according to one that changed

                for(int i =0; i<4; i++){
                    if(i != index_changed){
                        ports[i]->write(ports[index_changed]->read());
                    }
                }

                wait(SC_ZERO_TIME);

                copy_logic_array(new_state,last_state,4);

            }else{
                // if pip not actice pass horizontal and vertical accordingly
                if(index_changed == 0){
                    ports[2]->write(ports[0]->read());
                }else if(index_changed == 1){
                    ports[3]->write(ports[1]->read());
                }else if(index_changed == 2){
                    ports[0]->write(ports[2]->read());
                }else{
                    ports[1]->write(ports[3]->read());
                }

            }
        }
    }    

private:
    sc_logic last_state[4];
};

#endif