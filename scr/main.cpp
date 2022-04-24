#include<iostream>
#include <vector>
#include "LC.h"
#include "dp.h"
#include "brute_force.h"
#include <chrono>
#include "generator.h"

void test(int capacity, std::vector<int>& weight, std::vector<int>& profit) {

    std::cout << "Elapsed time in nanoseconds: " << std::endl;
    auto start_bf = std::chrono::steady_clock::now();
    std::cout << brute_force(capacity, weight, profit) <<std::endl;
    auto end_bf = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_bf - start_bf).count()
              << " ns" << std::endl;//10^9ns = 1 s
    
    auto start_dp = std::chrono::steady_clock::now();
    std::cout << dinamic_programing(capacity, weight, profit, profit.size()) << std::endl;
    auto end_dp = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_dp - start_dp).count()
              << " ns" << std::endl;
    
    LC branch_bound(capacity, weight, profit);
    auto start_bb = std::chrono::steady_clock::now();
    std::cout << branch_bound.knapsack() << std::endl;
    auto end_bb = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_bb - start_bf).count()
              << " ns" << std::endl;


}

int main() {
   
    int capacity = 15;
    int n = 20;
    std::vector<int> profit(n);
    std::vector<int> weight(n);
    generator(n,weight, profit);
    test(capacity,weight, profit);

    return 0;
}
