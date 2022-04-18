#include<iostream>
#include <vector>
//#include <bitset>
#include "LC.h"


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

int dinamic_programing(int W, std::vector<int>& wt, std::vector<int> val, int n) {
    std::vector<int> dp (W + 1, 0);
    
    for (int i = 1; i < n + 1; ++i) {
        for (int w = W; w >= 0; --w) {

            if (wt[i - 1] <= w)
                // finding the maximum profit
                dp[w] = std::max(dp[w],
                                 dp[w - wt[i - 1]] + val[i - 1]);
        }
    }
    return dp[W]; // returning the maximum profit of knapsack
}


int main() {
    std::vector<int> val = { 10, 10, 12, 18 };
    std::vector<int> wt = { 2, 4, 6, 9 };
    int capacity = 15;
    int n = val.size();

    std::cout << dinamic_programing(capacity, wt, val, n) << std::endl;
    std::cout << brute_force(capacity, wt, val) <<std::endl;

    LC branch_bound(capacity, wt, val);
    std::cout << branch_bound.knapsack() << std::endl;

    return 0;
}
