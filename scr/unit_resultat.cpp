#include<iostream>
#include <vector>
#include "LC.h"
#include "dp.h"
#include "brute_force.h"
#include <chrono>
#include "generator.h"

void test(int capacity, std::vector<int>& weight, std::vector<int>& profit) {

    int result_bt =  brute_force(capacity, weight, profit);
    
    int result_dp = dinamic_programing(capacity, weight, profit, profit.size());
    
    LC branch_bound(capacity, weight, profit);
    int result_bb = branch_bound.knapsack();
    
    std::cout << result_bt<< " "; 
    std::cout<< result_dp << " "; 
    std::cout<< result_bb << " "; 
    

}

int main() {
   
    int capacity = 30;
    for (int n = 5; n < 10; n++) {
        std::vector<int> profit(n);
        std::vector<int> weight(n);
        generator(n,weight, profit);
        test(capacity,weight, profit);
    }

    return 0;
}
