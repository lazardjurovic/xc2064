#include <systemc>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "comb_logic.hpp"
#include "flip_flop.hpp"

using namespace sc_core;
using namespace std;

SC_MODULE(clb){

//entity ports

    sc_in<bool> a, b, c, d, clk;
    sc_out<bool> x;
    sc_out<bool> y;

    SC_CTOR(clb) : x(0),y(0),comb("comb_logic"), dff("flip_flop"){
        SC_THREAD(proc_clb);
        sensitive << a<<b<<c<<d<<clk;

        // routing ports
        comb.a(a);
        comb.b(b);
        comb.c(c);
        comb.d(d);
        comb.q(q);
        comb.f(f);
        comb.g(g);

        dff.clk(wanted_clk);
        dff.r(reset);
        dff.d(f);
        dff.s(set);
        dff.q(q);

    }

    void proc_clb(){

        while(true){
            wait();
            cout << "CLB_PROC"<<endl;
            //page 7 of Datasheet for xc2000 family has detailed table for 
            //setting up logic aroung flip flops

            //creating 3 input muxes

            if(clb_mux_controls[0] == 1){
                reset = g;
            }else if(clb_mux_controls[1]== 1){
                reset = d | g;
            }else{
                reset = 0;
            }

            if(clb_mux_controls[2] == 1){
                set = 0;
            }else if(clb_mux_controls[3] == 1){
                set = f;
            }else{
                set = a;
            }

            if(clb_mux_controls[5] == 1){
                x.write(f);
            }else if(clb_mux_controls[6] == 1){
                x.write(g);
            }else{
                x.write(q);
            }

            if(clb_mux_controls[7]== 1){
                y.write(g);
            }else if(clb_mux_controls[8] == 1){
                y.write(f);
            }else{
                y.write(q);
            }


            //DOUBT THIS LOGIC WORKS
            //TODO: CHECK DATASHEET INTENSIVLY. TEST

            if(clb_mux_controls[9] == 1){
                clk_mux_out = c;
            }else{
                if(clb_mux_controls[11] == 0){
                    clk_mux_out = clk;
                }else{
                    clk_mux_out = g;
                }
            }

            if(clb_mux_controls[4] == 1){ // latch
                wanted_clk = 0;
            }else{
                if(clb_mux_controls[10] == 0){
                    wanted_clk = clk_mux_out;
                }else{
                    wanted_clk = !clk_mux_out;
                }
            }

        }


    }

    void load_clb_matrix(string name,int index){

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

        cout << "Loading CLB with: "<<endl;
        cout << line <<endl;

        vector<bool> bin_line = string_to_bin_vector(line);

        // signal F in datasheet
        bool upper_setup_vector[8] = {bin_line[128],bin_line[96],bin_line[120],bin_line[88],bin_line[136],
        bin_line[104],bin_line[112],bin_line[80]};

        //signal G in datasheet
        bool lower_setup_vector[8] = {bin_line[8],bin_line[40],bin_line[16],bin_line[48],bin_line[0],
        bin_line[32],bin_line[24],bin_line[56]};
        
        comb.setup_upper_lut(upper_setup_vector);
        comb.setup_lower_lut(lower_setup_vector);

        //control signals for muxes that selct LUT inputs
        bool comb_sels_vector[8] = {bin_line[81], bin_line[89], bin_line[129], bin_line[137], // selecting inputs for F LUT
        bin_line[49], bin_line[57], bin_line[9], bin_line[1] }; // selecting inputs for G LUT

        comb.setup_selects(comb_sels_vector);

        comb.print_controls();

        //setting up controls for muxes in CLB module
        bool mux_tmp[12] = {bin_line[138], // RES = G
                    bin_line[130], // RES = D OR G
                    bin_line[122], // SET = none
                    bin_line[114], // SET = F
                    bin_line[66], // Q = LATCH
                    bin_line[58], // X = F
                    bin_line[50], // X = G
                    bin_line[42], // Y = G
                    bin_line[34], // Y = F
                    bin_line[107], // CLK = C
                    bin_line[99], //CLK = inverted(FF), noninverted(LATCH)
                    bin_line[91] //CLK = enabled
        };  

        setup_mux_controls(mux_tmp);

    }

private:

    void setup_mux_controls(bool a[9]){
        for(int i = 0; i<12;i++){
            clb_mux_controls[i] = a[i];
        }
    }

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

    sc_signal<bool> f,g;
    sc_signal<bool> q,k,reset,set;
    sc_signal<bool> wanted_clk;
    sc_signal<bool> clk_mux_out;
    bool clb_mux_controls[12];

    comb_logic comb;
    flip_flop dff;

};