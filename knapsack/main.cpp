//
// Created by jctuesta on 04.04.2022.
//

#include "main.h"
#include "brute_force.h"

int main () {
    std::cout<< "hi"<<std::endl;//introduce data
    //call function
    //maybe we can create a struct to sabe all this datasets
    std::vector<int> value = {60, 100, 120};
    std::vector<int> weight = {10, 20, 30};
    int  weight_max = 50;
    std::cout<<"Value = " << knapsack(weight_max, weight, value) << std::endl;

    return 0;

}
