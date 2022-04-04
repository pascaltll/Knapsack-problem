//
// Created by jctuesta on 04.04.2022.
//
//time complexity 2^n
#include "brute_force.h"
#include <vector>

int max(int a, int b) { return (a > b)? a : b; }
// Returns the maximum value that can be put in a knapsack of capacity weight_max
int knapsack(int weight_max, std::vector<int> &weight, std::vector<int> &value) {

    std::vector<std::vector<int>> K (value.size() + 1, std::vector<int>(weight_max + 1));
    for (int i = 0; i <= value.size(); ++i) {
        for (int w = 0; w <= weight_max; w++) {
            if (i==0 || w==0) {
                K[i][w] = 0;
            } else if (weight[i - 1] <= w) {
                K[i][w] = max(value[i - 1] + K[i - 1][w - weight[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }
    return K[value.size()][weight_max];
}