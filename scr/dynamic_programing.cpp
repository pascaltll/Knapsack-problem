//
// Created by jctuesta on 11.04.2022.
//

#include "dynamic_programing.h"
int dynamic_programing (std::vector<int>& value, std::vector<int>& weight, int n, int W) {
    if (W < 0) {
        return INT_MIN;
    }
    if (n < 0 || W == 0) {
        return 0;
    }
    int in = value[n] + dynamic_programing(value, weight, n - 1, W - weight[n]);
    int ex = dynamic_programing(value, weight, n - 1, W);
    return std::max (in, ex);
}
