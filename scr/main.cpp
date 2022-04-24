#include<iostream>
#include <vector>
//#include <bitset>
#include "LC.h"
#include "dp.h"
#include "brute_force.h"
#include <chrono>
#include "generator.h"

int main() {
    std::vector<int> profit = { 10, 10, 12, 18 };
    std::vector<int> wt = { 2, 4, 6, 9 };
    int capacity = 15;
    /////////////
    auto start_bf = std::chrono::steady_clock::now();
    std::cout << brute_force(capacity, wt, profit) <<std::endl;
    auto end_bf = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in nanoseconds: "
         << std::chrono::duration_cast<std::chrono::nanoseconds>(end_bf - start_bf).count()
         << " ns" << std::endl;//10^9ns = 1 s
    //////////////
    auto start_dp = std::chrono::steady_clock::now();
    std::cout << dinamic_programing(capacity, wt, profit, profit.size()) << std::endl;
    auto end_dp = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in nanoseconds: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end_dp - start_dp).count()
              << " ns" << std::endl;
    //////////////
    LC branch_bound(capacity, wt, profit);
    auto start_bb = std::chrono::steady_clock::now();
    std::cout << branch_bound.knapsack() << std::endl;
    auto end_bb = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in nanoseconds: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end_bb - start_bf).count()
              << " ns" << std::endl;
    ///////////////

    return 0;
}
