#include<iostream>
#include <vector>
#include <chrono>
#include "generator.h"

void test(int capacity, std::vector<int>& weight, std::vector<int>& profit) {

    //std::cout << "Elapsed time in nanoseconds: " << std::endl;
    /*auto start_bf = std::chrono::steady_clock::now();
    int result_bt =  brute_force(capacity, weight, profit);
    auto end_bf = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_bf - start_bf).count() << std::endl;//10^9ns = 1 s
    
    auto start_dp = std::chrono::steady_clock::now();
    int result_dp = dinamic_programing(capacity, weight, profit, profit.size());
    auto end_dp = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_dp - start_dp).count() << std::endl;
    
    LC branch_bound(capacity, weight, profit);
    auto start_bb = std::chrono::steady_clock::now();
    int result_bb = branch_bound.knapsack();
    auto end_bb = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_bb - start_bf).count() << std::endl;
*/

}

int main() {
   
    int capacity = 30;
    for (int n = 5; n < 25; n++) {
        std::vector<int> profit(n);
        std::vector<int> weight(n);
        generator(n,weight, profit);
        test(capacity,weight, profit);
        for(auto i : weight) {
            std::cout<<i<<" ";
        }
        for(auto i : profit) {
            std::cout<<i<<" ";
        }
    }

    return 0;
}
