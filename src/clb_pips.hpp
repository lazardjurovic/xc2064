#include <systemc>
#include <iostream>
#include <vector>
#include <fstream>
#include "pip.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

#define CLB_PIP_SIGNALS_COUNT 47
#define CLB_PIPS_COUNT 27

SC_MODULE(clb_pips){

    //entity ports
    sc_port<sc_signal_inout_if<sc_logic>> ports[22];

    clb_pips(sc_module_name name, string filename, int index) : sc_module(name){

        for(int i =0; i<CLB_PIPS_COUNT; i++){
            pips.push_back(new pip("pip"));
        }

        for(int i =0; i<CLB_PIP_SIGNALS_COUNT; i++){
            pip_signals.push_back(new sc_signal_resolved);
        }

        //binding all internal pips

        pips[0]->ports[0](ports[1]);
        pips[0]->ports[1](*pip_signals[0]);
        pips[0]->ports[2](*pip_signals[1]);
        pips[0]->ports[3](ports[21]);

        pips[1]->ports[0](ports[3]);
        pips[1]->ports[1](*pip_signals[2]);
        pips[1]->ports[2](*pip_signals[3]);
        pips[1]->ports[3](*pip_signals[0]);

        pips[2]->ports[0](ports[5]);
        pips[2]->ports[1](*pip_signals[4]); // not connected anywhere
        pips[2]->ports[2](*pip_signals[5]);
        pips[2]->ports[3](*pip_signals[2]);

        pips[3]->ports[0](ports[0]);
        pips[3]->ports[1](*pip_signals[6]);
        pips[3]->ports[2](*pip_signals[7]);
        pips[3]->ports[3](*pip_signals[8]);

        pips[4]->ports[0](*pip_signals[1]);
        pips[4]->ports[1](*pip_signals[9]);
        pips[4]->ports[2](*pip_signals[10]);
        pips[4]->ports[3](*pip_signals[6]);

        pips[5]->ports[0](ports[2]);
        pips[5]->ports[1](*pip_signals[11]);
        pips[5]->ports[2](*pip_signals[12]);
        pips[5]->ports[3](*pip_signals[9]);

        pips[6]->ports[0](*pip_signals[3]);
        pips[6]->ports[1](*pip_signals[13]);
        pips[6]->ports[2](*pip_signals[14]);
        pips[6]->ports[3](*pip_signals[11]);

        pips[7]->ports[0](ports[4]);
        pips[7]->ports[1](*pip_signals[15]);
        pips[7]->ports[2](*pip_signals[16]);
        pips[7]->ports[3](*pip_signals[13]);

        pips[8]->ports[0](*pip_signals[17]); // not connected anywhere else
        pips[8]->ports[1](*pip_signals[18]);
        pips[8]->ports[2](*pip_signals[19]);
        pips[8]->ports[3](*pip_signals[15]);

        pips[9]->ports[0](*pip_signals[5]);
        pips[9]->ports[1](*pip_signals[20]);
        pips[9]->ports[2](*pip_signals[21]);
        pips[9]->ports[3](*pip_signals[18]);

        pips[10]->ports[0](ports[6]);
        pips[10]->ports[1](*pip_signals[22]);
        pips[10]->ports[2](*pip_signals[23]);
        pips[10]->ports[3](*pip_signals[20]);

        pips[11]->ports[0](ports[7]);
        pips[11]->ports[1](*pip_signals[24]);
        pips[11]->ports[2](*pip_signals[25]);
        pips[11]->ports[3](*pip_signals[22]);

        pips[12]->ports[0](ports[8]);
        pips[12]->ports[1](ports[9]);
        pips[12]->ports[2](*pip_signals[26]); // not connected anywhere else
        pips[12]->ports[3](*pip_signals[24]);

        pips[13]->ports[0](*pip_signals[6]);
        pips[13]->ports[1](*pip_signals[27]);
        pips[13]->ports[2](*pip_signals[28]);
        pips[13]->ports[3](*pip_signals[29]); // not connected anywhere else

        pips[14]->ports[0](*pip_signals[10]);
        pips[14]->ports[1](*pip_signals[30]);
        pips[14]->ports[2](ports[18]);
        pips[14]->ports[3](*pip_signals[27]);

        pips[15]->ports[0](*pip_signals[12]);
        pips[15]->ports[1](*pip_signals[31]);
        pips[15]->ports[2](*pip_signals[32]);
        pips[15]->ports[3](*pip_signals[30]);

        pips[16]->ports[0](*pip_signals[14]);
        pips[16]->ports[1](*pip_signals[33]);
        pips[16]->ports[2](ports[16]);
        pips[16]->ports[3](*pip_signals[31]);

        pips[17]->ports[0](*pip_signals[16]);
        pips[17]->ports[1](*pip_signals[34]);
        pips[17]->ports[2](*pip_signals[35]);
        pips[17]->ports[3](*pip_signals[33]);

        pips[18]->ports[0](*pip_signals[21]);
        pips[18]->ports[1](*pip_signals[36]);
        pips[18]->ports[2](ports[14]);
        pips[18]->ports[3](*pip_signals[34]);

        pips[19]->ports[0](*pip_signals[23]);
        pips[19]->ports[1](*pip_signals[37]);
        pips[19]->ports[2](*pip_signals[38]);
        pips[19]->ports[3](*pip_signals[36]);

        pips[20]->ports[0](*pip_signals[39]); // not connected anywhere else
        pips[20]->ports[1](ports[10]);
        pips[20]->ports[2](ports[12]);
        pips[20]->ports[3](*pip_signals[37]);

        pips[21]->ports[0](*pip_signals[38]);
        pips[21]->ports[1](*pip_signals[40]);
        pips[21]->ports[2](*pip_signals[41]);
        pips[21]->ports[3](*pip_signals[42]); // not connected anywhere else

        pips[22]->ports[0](*pip_signals[25]);
        pips[22]->ports[1](ports[11]);
        pips[22]->ports[2](ports[13]);
        pips[22]->ports[3](*pip_signals[40]);

        pips[23]->ports[0](*pip_signals[28]);
        pips[23]->ports[1](*pip_signals[43]);
        pips[23]->ports[2](ports[19]);
        pips[23]->ports[3](ports[20]);
        
        pips[24]->ports[0](*pip_signals[32]);
        pips[24]->ports[1](*pip_signals[44]);
        pips[24]->ports[2](ports[17]);
        pips[24]->ports[3](*pip_signals[43]);

        pips[25]->ports[0](*pip_signals[35]);
        pips[25]->ports[1](*pip_signals[45]); // ? try finding better solution bcs of pips[7]
        pips[25]->ports[2](ports[16]);
        pips[25]->ports[3](*pip_signals[44]);

        pips[26]->ports[0](*pip_signals[41]);
        pips[26]->ports[1](*pip_signals[46]); // not connected anywhere else
        pips[26]->ports[2](ports[14]);
        pips[26]->ports[3](*pip_signals[45]);

        // bind control ports of pips

        read_config(filename,index);

        for(int i = 0; i< 28; i++){
            control_sigs[i].write(controls[i]);
        }

        for(int i = 0; i < CLB_PIPS_COUNT; i++){
            pips[i]->control(control_sigs[i]);
        }

    }
    private:

    void read_config(string filename, int index){
                
        ifstream file(filename);
        string line;

        if(file.is_open()){
            
            int line_cnt = 0;

            while(getline(file,line)){
                if(line_cnt == index){
                    break;
                }
                    line_cnt++;
                }

            file.close();
        }else{
            cout << "Unable to open file " << filename << endl; 
        }

        vector<bool> line_bin = string_to_bin_vector(line);

        bool tmp_pip_connections[28] = { 
                            line_bin[140], // PIP B1,BY
                            line_bin[132], // PIP C1,C2
                            line_bin[124], // PIP B2,BC
                            line_bin[116], // PIP B4,B5
                            line_bin[108], // PIP c4,C5
                            line_bin[100], // PIP C6,C7
                            line_bin[92], //  PIP B6,B7
                            line_bin[84], //  PIP C3,CX (inverted)
                            line_bin[76], //  PIP X2
                            line_bin[68], //  PIP C1,C3,C4,C7
                            line_bin[60], //  PIP B3,BX (inverted)
                            line_bin[52], //  PIP B2,B5,B6,BX,BY 
                            line_bin[139], // PIP Y1
                            line_bin[131], // PIP Y3
                            line_bin[123], // PIP K2
                            line_bin[115], // PIP K1
                            line_bin[83], //  PIP X1
                            line_bin[67], //  PIP X3
                            line_bin[59], //  PIP Y4
                            line_bin[51], //  PIP Y2
                            line_bin[43], //  PIP D3,DX
                            line_bin[35], //  PIP D1, D4
                            line_bin[27], //  PIP A1,A4
                            line_bin[19], //  PIP A3,A4,A5
                            line_bin[11], //  PIP A2,A5 (inverted)
                            line_bin[3], //   PIP D2,D5 (inverted)
                            line_bin[21], //  PIP D3,D4,D5
                            line_bin[37], //  PIP A3,AX
        };

        copy_array(tmp_pip_connections,controls,28);

    }

        vector<sc_signal_resolved*> pip_signals;
        vector<pip*> pips;
        bool controls[28];
        sc_signal<bool> control_sigs[28];

};