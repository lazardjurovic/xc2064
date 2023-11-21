#include <systemc>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "utils.hpp"

using namespace std;
using namespace sc_core;

SC_MODULE(pip_controler){

    //entity ports

    sc_in<bool> x, y;
    sc_out<bool> b,c,k,a,d;

  pip_controler(sc_module_name name, string filename, int index ) : sc_module(name){
    
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

    bool tmp_pip_connections[28] = { line_bin[140], // PIP B1,BY
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

    copy_array(tmp_pip_connections,pip_connections,28);

  }  

private:
    bool pip_connections[28];

};
