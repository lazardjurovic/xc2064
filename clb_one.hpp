#include <systemc>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace sc_core;
using namespace std;

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

        big_lut_address = 1; // TESTING
        

        SC_THREAD(process_comb);
        sensitive << a << b << c << d<<clk;;

        SC_THREAD(process_ff)
        sensitive << clk;
    }

    void process_ff(){
        bool prev_d = false;

        while(true){
            wait();

            if(clk.posedge()){
                if(ff_s.read() == 1){
                    prev_d = 1;
                }else if(ff_r.read() == 1){
                    prev_d = 0;
                }else{
                    prev_d = ff_d.read();
                }
                ff_q.write(prev_d);
            }
        }
    }

    void process_comb(){

        //TODO: fiugre out how to handle oscilating input

        while(true){
            wait();

            if(clk.posedge()){
                if(separate_luts==0){
                    
                    bool dq_mux;

                    if(lut_input_muxes[2] == 1){
                        dq_mux = d;
                        //cout << "using d"<<endl;
                    }else{
                        dq_mux = ff_q;
                    }
                    
                    big_lut_address = 8*a + 4*b + 2*c + dq_mux;
                    //cout << "accessing lut at address: "<< big_lut_address<<endl;


                    lut_f = big_lut[big_lut_address];
                    lut_g = big_lut[big_lut_address];

                }else{
                    lut_f = upper_lut[upper_lut_address];
                    lut_g = lower_lut[lower_lut_address];
                }


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

                cout << lut_f << lut_g<<endl;

            }

        }
    }

    void load_matrix(string name, int index){

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

        //cout << "Loading CLB with: "<<endl;
        //cout << line <<endl;

        vector<bool> bin_line = string_to_bin_vector(line);

        separate_luts = !bin_line[64]; // BASE FG (separate LUTs)

        /*
        if(separate_luts==1){
            cout << "LUTs separated."<<endl;
        }else{
            cout << "Combining into lut4on1."<<endl;
        }
        */

        // signal F in datasheet
        bool upper_setup_vector[8] = {bin_line[128],bin_line[96],bin_line[120],bin_line[88],bin_line[136],
        bin_line[104],bin_line[112],bin_line[80]};

        //signal G in datasheet
        bool lower_setup_vector[8] = {bin_line[8],bin_line[40],bin_line[16],bin_line[48],bin_line[0],
        bin_line[32],bin_line[24],bin_line[56]};

        copy_array(upper_setup_vector,upper_lut,8);
        copy_array(lower_setup_vector,lower_lut,8);

        merge_arrays(upper_setup_vector,8,lower_setup_vector,8,big_lut,16);
        

        //control signals for muxes that selct LUT inputs
        bool comb_sels_vector[8] = {bin_line[81], bin_line[89], bin_line[129], bin_line[137], // selecting inputs for F LUT
        bin_line[49], bin_line[57], bin_line[9], bin_line[1] }; // selecting inputs for G LUT

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

        copy_array(comb_sels_vector,lut_input_muxes,8);
        copy_array(mux_tmp,clb_muxes,12);

        
        //print_array(upper_lut,8);
        //print_array(lower_lut,8);
        print_array(big_lut,16);
        //print_array(lut_input_muxes,8);
       // print_array(clb_muxes,12);
        

    }

    private:
        
    void copy_array(bool source[], bool destination[], int size) {
        for (int i = 0; i < size; i++) {
            destination[i] = source[i];
        }
    }

    void merge_arrays(bool arr1[], int size1, bool arr2[], int size2, bool result[], int resultSize) {
        for (int i = 0; i < size1; i++) {
            result[i] = arr1[i];
        }

        for (int i = 0; i < size2; i++) {
            result[size1 + i] = arr2[i];
        }

        resultSize = size1 + size2;
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

    void print_array(bool a[], int size){
        cout << "-----------------------------" <<endl;
        for(int i =0; i< size;i++){
            cout << i << ": " << a[i] << endl;
        }
    }

        sc_signal<bool> ff_s, ff_q, ff_r,ff_d; //flip flor signals
        bool upper_lut[8], lower_lut[8], big_lut[16];
        bool lut_input_muxes[8];
        bool clb_muxes[12];
        bool separate_luts;

        sc_signal<bool> lut_f,lut_g;
        int upper_lut_address = 0 , lower_lut_address = 0;
        int big_lut_address = 0;


};
