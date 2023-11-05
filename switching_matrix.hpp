#include <systemc>
#include <string>
#include <vector>

#include "conf_switch.hpp"
#include "utils.hpp"

using namespace sc_core;
using namespace std;

SC_MODULE(switch_matrix){

//entity ports
    sc_out<bool> a,b,c,d,e,f,g,h;

    /*
    a-1
    b-2
    c-3
    d-4
    e-5
    f-6
    g-7
    h-7
    */

    SC_CTOR(switch_matrix){
        SC_THREAD(proc_switch);
        sensitive << a << b << c << d << e << f << g << h;

        for(bool &bit : control){
            bit = 0;
        }
    }

    void proc_switch(){
        
        while(true){
            wait();
            if(control[0] == 1){
                if(e.posedge()){
                    h = 1;
                }else if(h.posedge()){
                    e = 1;
                }else{
                    h = 0;
                    e = 0;
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

        //TODO: LOAD BITS FROM LINE_BIN

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
                   line_bin[126], // 1-7
                   line_bin[118], // 4-6
                   line_bin[110], // 1-4
                   line_bin[102], // 1-3
                   line_bin[94], // 2-4
                   line_bin[86], // 5-8
                   line_bin[141], // 5-7
                   line_bin[85], // 2-8
        };

        copy_array(tmp_control,control,20);
        cout << "Switching matrix: " << name() << " configured with bits: " <<endl;
        print_array(control,20); 
    }

private:

    bool control[20];
};