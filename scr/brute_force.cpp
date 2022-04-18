//
// Created by jctuesta on 19.04.2022.
//
#include "brute_force.h"
int brute_force (int capacity, std::vector<int> &weight, std::vector<int> &value) {

    size_t bit_w = 1;
    size_t sum_w = 0;
    size_t profit_tmp = 0;
    size_t profit_max = 0;

    for (size_t i = 1; i < (bit_w << value.size()); i++) {
        //	std::cout  <<"---------" <<std::bitset<4>(i) << std::endl;
        for (size_t j = 0; j < value.size(); ++j) {
            //std::cout << std::bitset<4>(1<<j) <<" --j--";
            if (i & (bit_w << j) ) { //j is part of
                sum_w += weight[j];
                profit_tmp += value[j];
            }
            //std::cout << std::endl;
            //std::cout << "-sum_i-: " << sum_w << "-- profit : " << profit_tmp  << std::endl;
        }
        if (profit_max <= profit_tmp && sum_w <= capacity) {
            profit_max = profit_tmp;
            //set solution (1<<i)
        }
        profit_tmp = 0;
        sum_w = 0;
    }
    return profit_max;
}