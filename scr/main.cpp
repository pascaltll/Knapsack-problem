//
// Created by jctuesta on 04.04.2022.
//

#include "main.h"
#include "brute_force.h"
#incude "dynamic_programing.h"
#include<iostream>
#include <fstream>

int main () {
    /*std::ifstream value_input;
    value_input.open("scr/input/value.txt");
    if(!value_input) { // file couldn't be opened
        std::cout << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    int num;
    value_input >> num;
    while ( !value_input.eof() ) { // keep reading until end-of-file
        std::cout << "The next number is " << num << std::endl;
        value_input >> num; // sets EOF flag if no value found
    }
    value_input.close();
    std::cout<<num;*/
    //call function
    //maybe we can create a struct to save the input data
    std::vector<size_t> value = {60, 100, 120};
    std::vector<size_t> weight = {10, 20, 30};
    size_t  weight_max = 40;
    //std::cout<<"Value = " << scr(weight_max, weight, value) << std::endl;
    return 0;

}
