#include <systemc>
#include <iostream>

using namespace sc_core;
using namespace std;

SC_MODULE(lut3on1){

//entity ports

    sc_in<bool> a, b, c;
    sc_out<bool> out;

    SC_CTOR(lut3on1){

        for(bool &b : vals){
            b = 0;
        }

        SC_THREAD(proc_lut);
    }

    void proc_lut(){

        while(true){

            int addr = 8*a + 4*b + c;

            out = vals[addr];

        }

    }

    void setup_lut(bool v[8]){
        for(int i =0 ;i< 8; i++){
            vals[i] = v[i];
        }
    }

    void print_lut(){
        cout << "LUT " << name() << endl;
        for(int i=0; i<8; i++){
            cout << i << ": " << vals[i] << endl;
        }
    }


private:
    bool vals[8];

};