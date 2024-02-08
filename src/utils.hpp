#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <bitset>

using namespace std;
using namespace sc_dt;


void print_array(bool a[], int size){
    std::cout << "-----------------------------" <<std::endl;
    for(int i =0; i< size;i++){
      std::cout << i << ": " << a[i] << std::endl;
    }
}


void copy_array(bool source[], bool destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

void copy_logic_array(sc_logic source[], sc_logic destination[], int size) {
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

std::vector<bool> string_to_bin_vector(std::string line){

    std::vector<bool> res;

    for(char &c: line){
        if(c=='0'){
            res.push_back(0);
        }else{
            res.push_back(1);
        }
    }

    return res;

}

void print_vector(std::vector<bool> v){
    for(int i =0; i< v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

void vector_to_array(std::vector<bool> v, bool array[]){

    for(int i =0; i<v.size(); i++){
        array[i] = v[i];
    }

}

string int_2_string_4(int number){

    if (number < 0 || number > 15) {
        return "Invalid input";
    }

    // Convert the number to a 4-character long binary string
    std::bitset<4> binary(number);
    
    // Convert the bitset to a string and return
    return binary.to_string();
}

string int_2_string_3(int number){

    if (number < 0 || number > 7) {
        return "Invalid input";
    }

    // Convert the number to a 4-character long binary string
    std::bitset<3> binary(number);
    
    // Convert the bitset to a string and return
    return binary.to_string();
}


#endif

