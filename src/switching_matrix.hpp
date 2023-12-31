#ifndef SWITCHING_MATRIX_HPP
#define SWITCHING_MATRIX_HPP

#include <systemc>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

#include "utils.hpp"

using namespace sc_core;
using namespace std;
using namespace sc_dt;

SC_MODULE(switch_matrix){
    
   //entity ports
    sc_port<sc_signal_inout_if<sc_logic>> ports[8];

    //parametrized constructor
    switch_matrix(sc_module_name name, int n) : sc_module(name){

        cout << "Creating new switching matrix."<<endl;
        n_matrix = n;

        //initilizing ports

        SC_HAS_PROCESS(switch_matrix);

        SC_THREAD(proc);
        for(int i =0; i<8; i++){
            sensitive << ports[i];
        }

    }

    void proc(){
        while(true){
            wait();

            sc_logic new_state[8];

            for(int i=0; i<8;i++){
                new_state[i] = ports[i]->read();
            }

            // find index of pin that changed
            vector<int> index_changed;

            for(int i =0; i<8;i++){
                if(new_state[i] != states[i]){
                    index_changed.push_back(i);

                    #ifdef DEBUG
                    cout << "Detected change on " << name() << "on port "<< i <<endl;
                    #endif

                    break;
                }
            }   
            
            // update all ports connected to index_changed

            for(int j = 0 ; j< index_changed.size(); j++){
                for(int i=0;i<8;i++){
                    if(matrix[i][index_changed[j]] == 1){
                        ports[i]->write(ports[index_changed[j]]->read());

                    }
                }
            }

            wait(SC_ZERO_TIME);
            copy_logic_array(new_state,states,8);

        }
    }

    void load_switching_config(string filename, int index){

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
        vector<bool> tmp_control;

        // deciding if matrix is of index 1 or 2

        if(n_matrix == 1){
                tmp_control = {line_bin[143], // 6-8
                    line_bin[135], // 7-8
                    line_bin[127], // 2-6
                    line_bin[119], // 2-7
                    line_bin[111], // 4-8
                    line_bin[103], // 1-5
                    line_bin[95],  //  1-2
                    line_bin[87],  //  3-4
                    line_bin[79],  // 3-5
                    line_bin[142], // 5-6
                    line_bin[134], // 3-7
                    line_bin[126], // 3-6
                    line_bin[118], // 1-7
                    line_bin[110], // 4-6
                    line_bin[102], // 1-4
                    line_bin[94],  // 1-3
                    line_bin[86],  // 2-4
                    line_bin[78],  // 5-8
                    line_bin[141], // 5-7
                    line_bin[77],  // 2-8
            };
        }else{
                tmp_control = {line_bin[7], // 1-3 
                    line_bin[15], // 1-2 
                    line_bin[23], // 3-7 
                    line_bin[31], // 2-7
                    line_bin[39], // 1-5 
                    line_bin[47], // 4-8 
                    line_bin[55], // 7-8 
                    line_bin[63], // 5-6 
                    line_bin[71], // 4-6 
                    line_bin[6],  // 3-4 
                    line_bin[14], // 2-6 
                    line_bin[22], // 3-6 
                    line_bin[30], // 2-8 
                    line_bin[38], // 3-5 
                    line_bin[46], // 5-8 
                    line_bin[54], // 6-8 
                    line_bin[62], // 5-7 
                    line_bin[70], // 1-4 
                    line_bin[13], // 2-4
                    line_bin[69], // 1-7 
            };
        }

        vector_to_array(tmp_control,control);

        #ifdef DEBUG
        cout << "Switching matrix: " << name() << " configured with bits: " <<endl;
        print_array(control,20); 
        #endif

        make_matrix(control);
    } 


private:

    void make_matrix(bool cont[20]){

        // TODO: FIND MORE CLEVER FORMULATION !!!
        
        if(n_matrix == 1){
            matrix[6][8] = 1 ? cont[0]==1 : 0;
            matrix[8][6] = 1 ? cont[0]==1 : 0;
            matrix[7][8] = 1 ? cont[1]==1 : 0;
            matrix[8][7] = 1 ? cont[1]==1 : 0;
            matrix[2][6] = 1 ? cont[2]==1 : 0;
            matrix[6][2] = 1 ? cont[2]==1 : 0;
            matrix[2][7] = 1 ? cont[3]==1 : 0;
            matrix[7][2] = 1 ? cont[3]==1 : 0;
            matrix[4][8] = 1 ? cont[4]==1 : 0;
            matrix[8][4] = 1 ? cont[4]==1 : 0;
            matrix[1][5] = 1 ? cont[5]==1 : 0;
            matrix[5][1] = 1 ? cont[5]==1 : 0;
            matrix[1][2] = 1 ? cont[6]==1 : 0;
            matrix[2][1] = 1 ? cont[6]==1 : 0;
            matrix[3][4] = 1 ? cont[7]==1 : 0;
            matrix[4][3] = 1 ? cont[7]==1 : 0;
            matrix[3][5] = 1 ? cont[8]==1 : 0;
            matrix[5][3] = 1 ? cont[8]==1 : 0;
            matrix[5][6] = 1 ? cont[9]==1 : 0;
            matrix[6][5] = 1 ? cont[9]==1 : 0;
            matrix[3][7] = 1 ? cont[10]==1 : 0;
            matrix[7][3] = 1 ? cont[10]==1 : 0;
            matrix[3][6] = 1 ? cont[11]==1 : 0;
            matrix[6][3] = 1 ? cont[11]==1 : 0;
            matrix[1][7] = 1 ? cont[12]==1 : 0;
            matrix[7][1] = 1 ? cont[12]==1 : 0;
            matrix[4][6] = 1 ? cont[13]==1 : 0;
            matrix[6][4] = 1 ? cont[13]==1 : 0;
            matrix[1][4] = 1 ? cont[14]==1 : 0;
            matrix[4][1] = 1 ? cont[14]==1 : 0;
            matrix[1][3] = 1 ? cont[15]==1 : 0;
            matrix[3][1] = 1 ? cont[15]==1 : 0;
            matrix[2][4] = 1 ? cont[16]==1 : 0;
            matrix[4][2] = 1 ? cont[16]==1 : 0;
            matrix[5][8] = 1 ? cont[17]==1 : 0;
            matrix[8][5] = 1 ? cont[17]==1 : 0;
            matrix[5][7] = 1 ? cont[18]==1 : 0;
            matrix[7][5] = 1 ? cont[18]==1 : 0;
            matrix[2][8] = 1 ? cont[19]==1 : 0;
            matrix[8][2] = 1 ? cont[19]==1 : 0;
        }else{
            matrix[1][3] = 1 ? cont[0]==1 : 0;
            matrix[3][1] = 1 ? cont[0]==1 : 0;
            matrix[1][2] = 1 ? cont[1]==1 : 0;
            matrix[2][1] = 1 ? cont[1]==1 : 0;
            matrix[3][7] = 1 ? cont[2]==1 : 0;
            matrix[7][3] = 1 ? cont[2]==1 : 0;
            matrix[2][7] = 1 ? cont[3]==1 : 0;
            matrix[7][2] = 1 ? cont[3]==1 : 0;
            matrix[1][5] = 1 ? cont[4]==1 : 0;
            matrix[5][1] = 1 ? cont[4]==1 : 0;
            matrix[4][8] = 1 ? cont[5]==1 : 0;
            matrix[8][4] = 1 ? cont[5]==1 : 0;
            matrix[7][8] = 1 ? cont[6]==1 : 0;
            matrix[8][7] = 1 ? cont[6]==1 : 0;
            matrix[5][6] = 1 ? cont[7]==1 : 0;
            matrix[6][5] = 1 ? cont[7]==1 : 0;
            matrix[4][6] = 1 ? cont[8]==1 : 0;
            matrix[6][4] = 1 ? cont[8]==1 : 0;
            matrix[3][4] = 1 ? cont[9]==1 : 0;
            matrix[4][3] = 1 ? cont[9]==1 : 0;
            matrix[2][6] = 1 ? cont[10]==1 : 0;
            matrix[6][2] = 1 ? cont[10]==1 : 0;
            matrix[3][6] = 1 ? cont[11]==1 : 0;
            matrix[6][3] = 1 ? cont[11]==1 : 0;
            matrix[2][8] = 1 ? cont[12]==1 : 0;
            matrix[8][2] = 1 ? cont[12]==1 : 0;
            matrix[3][5] = 1 ? cont[13]==1 : 0;
            matrix[5][3] = 1 ? cont[13]==1 : 0;
            matrix[5][8] = 1 ? cont[14]==1 : 0;
            matrix[8][5] = 1 ? cont[14]==1 : 0;
            matrix[6][8] = 1 ? cont[15]==1 : 0;
            matrix[8][6] = 1 ? cont[15]==1 : 0;
            matrix[5][7] = 1 ? cont[16]==1 : 0;
            matrix[7][5] = 1 ? cont[16]==1 : 0;
            matrix[1][4] = 1 ? cont[17]==1 : 0;
            matrix[4][1] = 1 ? cont[17]==1 : 0;
            matrix[2][4] = 1 ? cont[18]==1 : 0;
            matrix[4][2] = 1 ? cont[18]==1 : 0;
            matrix[1][7] = 1 ? cont[19]==1 : 0;
            matrix[7][1] = 1 ? cont[19]==1 : 0;
        }



        for(int i =0 ;i<8;i++){
            for(int j = 0; j<8;j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool control[20];
    sc_logic states[8];
    bool matrix[9][9] = {}; // fix size error
    int n_matrix;


};

#endif