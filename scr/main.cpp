#include<iostream>
#include <vector>
//#include <bitset>
#include "LC.h"
#include "dp.h"
#include "brute_force.h"

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
