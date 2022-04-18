//
// Created by jctuesta on 19.04.2022.
//
#include "dp.h"
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
