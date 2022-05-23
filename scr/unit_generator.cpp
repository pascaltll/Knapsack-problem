#include<iostream>
#include <vector>
#include <chrono>
#include "generator.h"

int main() {
   
    int capacity = 30;
    int n = 100;
    std::vector<int> profit(n);
    std::vector<int> weight(n);
    generator(n,weight, profit);
    for(auto i : weight) {
        std::cout<<i<<" ";
    }
    for(auto i : profit) {
        std::cout<<i<<" ";
    }
    return 0;
}
