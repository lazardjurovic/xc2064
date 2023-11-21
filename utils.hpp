#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;


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



#endif

