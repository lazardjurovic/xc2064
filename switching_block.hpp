#include <systemc>
#include <iostream>
#include <string>
#include <vector>

#include "switching_matrix.hpp"
#include "pip.hpp"
#include "interface.hpp"

using namespace std;
using namespace sc_core;

SC_MODULE(switching_block){

    //entity ports

    vector<sc_inout<bool>*> ports;
    sc_export<interface> out;

    switching_block(sc_module_name name, string filename, int index) : sc_module(name), sw1("sw1",1), sw2("sw2",2){

        for(int i =0; i< 28;i++){
            ports.push_back(new sc_inout<bool>);
        }

        sw1.load_switching_config(filename,index);
        sw2.load_switching_config(filename,index);
        load_pip_nd__controls(filename,index);

        //configure ND PIPs

        for(int i=0 ;i<11; i++){
            nd_pips.push_back(new pip("pip"));
        }

        // TODO: connect control        
        for(auto nd_pip: nd_pips){
            vector<sc_signal<bool>*> sigs = create_signal_vector(4);
            nd_pip->bind_ports(sigs);
            nd_pip_signals.push_back(sigs);
        }

        interface a(nd_pip_signals.at(0).at(0));

        out.bind(a);

    }

    ~switching_block(){
        for(auto port : ports){
            delete port;
        }
        for(auto sig: matrix1_signals){
            delete sig;
        }
        for(auto nd_pip: nd_pips){
            delete nd_pip;
        }
        for(auto vector_sigs : nd_pip_signals){
            for(auto sig : vector_sigs){
                delete sig;
            }
        }
    }

private:

    vector<sc_signal<bool>*> create_signal_vector(int size) {
        vector<sc_signal<bool>*> signal_vector;

        for (int i = 0; i < size; ++i) {
            sc_signal<bool>* signal = new sc_signal<bool>();
            signal_vector.push_back(signal);
        }

        return signal_vector;
    }

    void load_pip_nd__controls(string filename, int index){
    
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

    bool tmp_nd_connections[11] = { line_bin[133], // 1
                                    line_bin[125], // 2
                                    line_bin[117], // 3
                                    line_bin[109], // 4
                                    line_bin[101], // 5
                                    line_bin[93], //  6
                                    line_bin[85], //  7
                                    line_bin[61], //  8
                                    line_bin[53], //  9
                                    line_bin[45], //  10
                                    line_bin[29] //   11

    };    

    copy_array(tmp_pip_connections,pip_connections,28);
    copy_array(tmp_nd_connections,nd_connections,11);

    }

    switch_matrix sw1,sw2;
    vector<sc_signal<bool>*> matrix1_signals;
    vector<sc_signal<bool>*> matrix2_signals;
    bool pip_connections[28];
    bool nd_connections[11];

    vector<pip*> nd_pips;
    vector<vector<sc_signal<bool>*>> nd_pip_signals;   

};