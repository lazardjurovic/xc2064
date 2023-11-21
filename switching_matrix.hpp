#include <systemc>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

#include "utils.hpp"

using namespace sc_core;
using namespace std;

SC_MODULE(switch_matrix){
    
   //entity ports
    vector<sc_inout<bool>*> ports;

    //parametrized constructor
    switch_matrix(sc_module_name name, int n) : sc_module(name){

        cout << "Creating new switching matrix."<<endl;

        //initilizing ports

        for(int i =0; i<8;i++){
            ports.push_back(new sc_inout<bool>);
        }

        SC_HAS_PROCESS(switch_matrix);

        SC_THREAD(proc);
        for(int i =0; i<8; i++){
            sensitive << *ports[i];
        }

    }

    void bind_ports(vector<sc_signal<bool>*> sigs){
        for(int i =0; i<8;i++){
            ports[i]->bind(*sigs[i]);
        }
    }

    ~switch_matrix(){
        // free memory
        for (auto port : ports) {
            delete port;
        }
    }

    void proc(){
        while(true){
            wait();

            bool new_state[8];

            for(int i=0; i<8;i++){
                new_state[i] = ports[i]->read();
            }

            // find index of pin that changed
            int index_changed;

            for(int i =0; i<8;i++){
                if(new_state[i] != states[i]){
                    index_changed = i;

                    #ifdef DEBUG
                    cout << "Detected change on " << name() << "on port "<< index_changed <<endl;
                    #endif

                    break;
                }
            }   
            
            // update all ports connected to index_changed

            for(int i=0;i<8;i++){
                if(matrix[i][index_changed] == 1){
                    ports[i]->write(ports[index_changed]->read());
                    wait(SC_ZERO_TIME);
                }
            }

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

        //TODO: CHECK IF N IS 1 OR 2

        bool tmp_control[20] = {line_bin[143], // 6-8
                   line_bin[135], // 7-8
                   line_bin[127], // 2-6
                   line_bin[119], // 2-7
                   line_bin[111], // 4-8
                   line_bin[103], // 1-5
                   line_bin[95], //  1-2
                   line_bin[87], //  3-4
                   line_bin[89], // 3-5
                   line_bin[142], // 5-6
                   line_bin[134], // 3-7
                   line_bin[126], // 3-6
                   line_bin[118], // 1-7
                   line_bin[110], // 4-6
                   line_bin[102], // 1-4
                   line_bin[94], // 1-3
                   line_bin[86], // 2-4
                   line_bin[78], // 5-8
                   line_bin[141], // 5-7
                   line_bin[77], // 2-8
        };

        copy_array(tmp_control,control,20);
        cout << "Switching matrix: " << name() << " configured with bits: " <<endl;
        print_array(control,20); 

        make_matrix(control);
    } 


private:

    // TODO: FIND NORMAL SOLUTION PLEASE !!!!

    void make_matrix(bool cont[20]){

        matrix[7][5] = 1 ? cont[0]==1 : 0;
        matrix[5][7] = 1 ? cont[0]==1 : 0;
        matrix[7][6] = 1 ? cont[1]==1 : 0;
        matrix[6][7] = 1 ? cont[1]==1 : 0;
        matrix[5][1] = 1 ? cont[2]==1 : 0;
        matrix[1][5] = 1 ? cont[2]==1 : 0;
        matrix[6][1] = 1 ? cont[3]==1 : 0;
        matrix[1][6] = 1 ? cont[3]==1 : 0;
        matrix[7][3] = 1 ? cont[4]==1 : 0;
        matrix[3][7] = 1 ? cont[4]==1 : 0;
        matrix[4][0] = 1 ? cont[5]==1 : 0;
        matrix[0][4] = 1 ? cont[5]==1 : 0;
        matrix[1][0] = 1 ? cont[6]==1 : 0;
        matrix[0][1] = 1 ? cont[6]==1 : 0;
        matrix[3][2] = 1 ? cont[7]==1 : 0;
        matrix[2][3] = 1 ? cont[7]==1 : 0;
        matrix[4][2] = 1 ? cont[8]==1 : 0;
        matrix[2][4] = 1 ? cont[8]==1 : 0;
        matrix[5][4] = 1 ? cont[9]==1 : 0;
        matrix[4][5] = 1 ? cont[9]==1 : 0;
        matrix[6][2] = 1 ? cont[10]==1 : 0;
        matrix[2][6] = 1 ? cont[10]==1 : 0;
        matrix[5][2] = 1 ? cont[11]==1 : 0;
        matrix[2][5] = 1 ? cont[11]==1 : 0;
        matrix[6][0] = 1 ? cont[12]==1 : 0;
        matrix[0][6] = 1 ? cont[12]==1 : 0;
        matrix[5][3] = 1 ? cont[13]==1 : 0;
        matrix[3][5] = 1 ? cont[13]==1 : 0;
        matrix[3][0] = 1 ? cont[14]==1 : 0;
        matrix[0][3] = 1 ? cont[14]==1 : 0;
        matrix[2][0] = 1 ? cont[15]==1 : 0;
        matrix[0][2] = 1 ? cont[15]==1 : 0;
        matrix[3][1] = 1 ? cont[16]==1 : 0;
        matrix[1][3] = 1 ? cont[16]==1 : 0;
        matrix[7][4] = 1 ? cont[17]==1 : 0;
        matrix[4][7] = 1 ? cont[17]==1 : 0;
        matrix[6][4] = 1 ? cont[18]==1 : 0;
        matrix[4][6] = 1 ? cont[18]==1 : 0;
        matrix[7][1] = 1 ? cont[19]==1 : 0;
        matrix[1][7] = 1 ? cont[19]==1 : 0;


        for(int i =0 ;i<8;i++){
            for(int j = 0; j<8;j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool control[20];
    bool states[8];
    bool matrix[8][8] = {};

};