#ifndef CLB_ONE_HPP
#define CLB_ONE_HPP

#include <systemc>
#include <iostream>
#include <string>
#include <fstream>
#include "utils.hpp"
#include "OpenQM/implicant.h"
#include "OpenQM/qm.h"

using namespace sc_core;
using namespace std;

#define QM

SC_MODULE(clb_one){

    //entitiy ports
    sc_in<bool> a,b,c,d,clk;
    sc_out<bool> x,y;

    SC_CTOR(clb_one){

        for(bool &element : upper_lut)
            element = 0;
        for(bool &element : lower_lut)
            element = 0;
        for(bool &element : big_lut)
            element = 0;

        big_lut_address = 0;
        upper_lut_address = 0;
        lower_lut_address = 0;

        SC_THREAD(process_comb);
        dont_initialize();
        sensitive << a << b << c << d;

        SC_THREAD(process_ff)
        sensitive << ff_d<<ff_s<<ff_r<<ff_clk;
    }

    void process_ff(){
        bool prev_d = false;

        while(true){
            wait();

            if(ff_clk.posedge()){
                if(ff_s.read() == 1){
                    prev_d = 1;
                }else if(ff_r.read() == 1){
                    prev_d = 0;
                }else{
                    prev_d = ff_d.read();
                }
                ff_q.write(prev_d);
                wait(SC_ZERO_TIME);
            }
        }
    }

    void process_comb(){

        while(true){
            wait();

                if(separate_luts==0){
                    
                    bool dq_mux;

                    if(lut_input_muxes[2] == 1){
                        dq_mux = d;
                        //cout << "using d"<<endl;
                    }else{
                        dq_mux = ff_q;
                    }
                    
                    big_lut_address = 8*a + 4*b + 2*c + dq_mux;

                    #ifdef DEBUG
                    cout << "accessing lut at address: "<< big_lut_address<<endl;
                    #endif

                    lut_f = big_lut[big_lut_address];
                    lut_g = big_lut[big_lut_address];

                    #ifdef DEBUG
                    cout << "Read form lut: " <<lut_f << lut_g <<endl;
                    #endif

                }else{
                    // if luts are separated
                    // currently only option 2 from datasheet supported until proved different

                    bool gin_3=0, gin_2=0, gin_1=0, fin_3=0,fin_2 = 0, fin_1 = 0;

                    // selecting inputs for g mux

                    if(lut_input_muxes[7] == 1){
                        gin_3 = d;
                    }else if(lut_input_muxes[6] == 1){
                        gin_3 = c;
                    }

                    if(lut_input_muxes[5] == 1){
                        gin_2 = b;
                    }else{
                        gin_2 = c;
                    }

                    if(lut_input_muxes[4] == 1){
                        gin_1 = a;
                    }else{
                        gin_1 = b;
                    }

                    // selecting inputs for f mux

                    if(lut_input_muxes[3] == 1){
                        fin_3 = d;
                    }else if(lut_input_muxes[2] == 1){
                        fin_3 = c;
                    }

                    if(lut_input_muxes[1] == 1){
                        gin_2 = b;
                    }else{
                        gin_2 = c;
                    }

                    if(lut_input_muxes[0] == 1){
                        gin_1 = a;
                    }else{
                        gin_1 = b;
                    }   

                    upper_lut_address = 4*fin_1 + 2*fin_2 + fin_3;
                    lower_lut_address = 4*gin_1 + 2*gin_2 + gin_3; 


                    lut_f = upper_lut[upper_lut_address];
                    lut_g = lower_lut[lower_lut_address];
                }

                wait(SC_ZERO_TIME);

                ff_d = lut_f;
                if(clb_muxes[0] == 1){
                    ff_r = lut_g;
                }else if(clb_muxes[1] == 1){
                    ff_r = d | lut_g;
                }

                if(clb_muxes[3] == 1){
                    ff_s = lut_f;
                }

                //DOUBLE CHECK NEEDED
                /*
                if(clb_muxes[4] == 1){
                    ff_q = ff_d;
                }
                */

                wait(SC_ZERO_TIME);

                //connecting x and y outputs

                if(clb_muxes[5] == 1){
                    x = lut_f;
                }else if(clb_muxes[6] ==1){
                    x = lut_g;
                }else{
                    x = ff_q;
                }

                if(clb_muxes[7] == 1){
                    y = lut_g;
                }else if(clb_muxes[8] == 1){
                    y = lut_f;
                }else{
                    y = ff_q;
                }

                if(clb_muxes[9] == 1){
                    ff_clk = c;

                    #ifdef DEBUG
                    cout << "Using c as ff_clk."<<endl;
                    #endif

                }else if(clb_muxes[10] == 1){
                    //CLK = inverted(FF), noninverted(LATCH)
                    //TODO
                }else if(clb_muxes[11] == 1){
                    //CLK = enabled
                    ff_clk = clk;

                    #ifdef DEBUG
                    cout << "Using external clk."<<endl;
                    #endif

                }
                
                wait(SC_ZERO_TIME);

        }
    }

    void bind_ports(vector<sc_signal<bool>*> signals){
        a.bind(*signals[0]);
        b.bind(*signals[1]);
        c.bind(*signals[2]);
        d.bind(*signals[3]);
        clk.bind(*signals[4]);
        x.bind(*signals[5]);
        y.bind(*signals[6]);
    }

    void load_config(string name, int index){

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
            return;
        }

        cout << "Loading CLB with: "<<endl;
        cout << line <<endl;

        vector<bool> bin_line = string_to_bin_vector(line);

        separate_luts = !bin_line[64]; // BASE FG (separate LUTs)

        #ifdef DEBUG
        if(separate_luts==1){
            cout << "LUTs separated."<<endl;
        }else{
            cout << "Combining into lut4on1."<<endl;
        }
        #endif        

        // signal F in datasheet
        bool upper_setup_vector[8] = {bin_line[128],bin_line[136],bin_line[120],bin_line[112],bin_line[96],
        bin_line[104],bin_line[88],bin_line[80]};

        //signal G in datasheet
        bool lower_setup_vector[8] = {bin_line[8],bin_line[0],bin_line[16],bin_line[24],bin_line[40],
        bin_line[32],bin_line[48],bin_line[56]};

        copy_array(upper_setup_vector,upper_lut,8);
        copy_array(lower_setup_vector,lower_lut,8);

        merge_arrays(upper_setup_vector,8,lower_setup_vector,8,big_lut,16);
        

        //control signals for muxes that selct LUT inputs
        bool lut_input_muxes_tmp[8] = {
            bin_line[81], // FIN_1 = A
            bin_line[89], // FIN_2 = B
            bin_line[129], // FIN_3 = C
            bin_line[137], // FIN_3 = D
            bin_line[49], // GIN_1 = A
            bin_line[41], // GIN_2 = B
            bin_line[9], // GIN_3 = C
            bin_line[1] // GIN_3 = D
            };

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

        copy_array(lut_input_muxes_tmp,lut_input_muxes,8);
        copy_array(mux_tmp,clb_muxes,12);

        print_setup_info();

        #ifdef QM

        // Print logic function of CLB minimized by OpenQM
        if(separate_luts == 0){
            for(int i = 0; i<15;i++){
                if(big_lut[i] == 1){
                    implicant_list.push_back(int_2_string(i,4));
                }
            }

            solution = makeQM(implicant_list,dont_care_list);

            string soulution_expression = getBooleanExpression(solution);

            cout << "Configured this LUT with function F = G = " << soulution_expression << endl;

        }else{

            for(int i = 0; i<8; i++){
                if(upper_lut[i] == 1){
                    implicant_list.push_back(int_2_string(i,3));
                }
            }

            solution = makeQM(implicant_list,dont_care_list);
            string soulution_expression = getBooleanExpression(solution);
            cout << "Configured upper LUT with function F = " << soulution_expression << endl;

            implicant_list.clear();

            for(int i = 0; i<8; i++){
                if(lower_lut[i] == 1){
                    implicant_list.push_back(int_2_string(i,3));
                }
            }

            solution = makeQM(implicant_list,dont_care_list);
            soulution_expression = getBooleanExpression(solution);
            cout << "Configured lower LUT with function G = " << soulution_expression << endl;

        }

        #endif

        #ifdef DEBUG
        //print_array(upper_lut,8);
        //print_array(lower_lut,8);
        print_array(big_lut,16);
        //print_array(lut_input_muxes,8);
        cout <<endl<< "--------- CLB MUXES ---------------" <<endl;
        print_array(clb_muxes,12);
        #endif

    }

    private:

        void print_setup_info(){

            cout << "Lut input muxes info: " << endl;

            if(separate_luts ){
                lut_input_muxes[0] == 1 ?  cout << "FIN_1 = A"<<endl : cout << ""<<endl;
                lut_input_muxes[1] == 1 ?  cout << "FIN_2 = B"<<endl : cout << ""<<endl;
                lut_input_muxes[2] == 1 ?  cout << "FIN_3 = C"<<endl : cout << ""<<endl;
                lut_input_muxes[3] == 1 ?  cout << "FIN_3 = D"<<endl : cout << ""<<endl;

                lut_input_muxes[4] == 1 ?  cout << "GIN_1 = A"<<endl : cout << ""<<endl;
                lut_input_muxes[5] == 1 ?  cout << "GIN_2 = B"<<endl : cout << ""<<endl;
                lut_input_muxes[6] == 1 ?  cout << "GIN_3 = C"<<endl : cout << ""<<endl;
                lut_input_muxes[7] == 1 ?  cout << "GIN_3 = D"<<endl : cout << ""<<endl;
            }else{
                lut_input_muxes[3] == lut_input_muxes[7] && lut_input_muxes[3] == 1 ? cout << "FIN_3 = GIN_3 = Q"<<endl : cout << "FIN_3 = GIN_3 = D"<<endl;
            }


        }

        sc_signal<bool> ff_s, ff_q, ff_r,ff_d, ff_clk; //flip flor signals
        bool upper_lut[8], lower_lut[8], big_lut[16];
        bool lut_input_muxes[8];
        bool clb_muxes[12];
        bool separate_luts;

        sc_signal<bool> lut_f,lut_g;
        int upper_lut_address = 0 , lower_lut_address = 0;
        int big_lut_address = 0;

        vector<Implicant> implicant_list,solution;
        vector<Implicant> dont_care_list = {};

};

#endif