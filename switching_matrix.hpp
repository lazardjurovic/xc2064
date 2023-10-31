#include <systemc>
#include <string>
#include <vector>

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
    }

    void proc_switch(){
        
        while(true){
            
            if(control[0] == 1){
                
            }



        }

    }

    void load_switching_config(string name, int index){

        ifstream file(name);
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
            cout << "Unable to open file " << name << endl; 
        }

        vector<bool> line_bin = string_to_bin_vector(line);

        //TODO: LOAD BITS FROM LINE_BIN



    }

private:

    vector<bool> string_to_bin_vector(string line){

        vector<bool> res;

        for(char &c: line){
            if(c=='0'){
                res.push_back(0);
            }else{
                res.push_back(1);
            }
        }

        return res;

    }

    bool control[20];
    bool valid_connections[8][8] = {
        {0,0,1,0,1,1,1,1},
        {0,0,1,1,1,1,0,1},
        {1,1,0,0,1,0,1,1},
        {0,1,0,0,1,1,1,1},
        {1,1,1,1,0,0,1,0},
        {1,1,0,1,0,0,1,1},
        {1,0,1,1,1,1,0,0},
        {1,1,1,1,0,1,0,0,}
    };
};