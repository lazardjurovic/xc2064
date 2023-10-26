#include <systemc>
#include <iostream>

using namespace sc_core;
using namespace std;

SC_MODULE(lut3on1){

//entity ports

    sc_in<bool> a, b, c;
    sc_out<bool> out;

    SC_CTOR(lut3on1) : out(0){

        for(bool &b : vals){
            b = 0;
        }

        SC_THREAD(proc_lut);
        sensitive << a<<b<<c;
    }

    void proc_lut(){

        while(true){
            wait();
            int addr = 4*a + 2*b + c;
            out = vals[addr];
            
            cout << "LUT input: " << a << b << c<<endl;
            cout << "OUT FROM LUT: " << out <<endl;

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