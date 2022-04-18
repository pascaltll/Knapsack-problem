#include <bits/stdc++.h>
#include<iostream>
#include <vector>
#include <bitset>


typedef struct Item {
    float weight;
    int profit;//valor de gananci
    int idx;
} Item;

typedef struct Node {
    float upper_b;
    float lower_b;
    int level;
    bool flag;
    float tree_v;
    float tree_w;
} Node;
void cast_data(Node& a, float upper_b, float lower_b, int level, bool flag, float tree_v, float tree_w) {
    a.upper_b = upper_b;
    a.lower_b = lower_b;
    a.level = level;
    a.flag = flag;
    a.tree_v = tree_v;
    a.tree_w = tree_w;
}
class comp {
public:
    bool operator()(Node a, Node b) {
        return a.lower_b > b.lower_b;
    }
};

class LC {
private:
    int _size;
    float _capacity;
    std::vector<Item> _arr;
public:
    LC(int weight_max, std::vector<int> &weight, std::vector<int> &profit);
    float upper_bound(float tree_v, float tree_w, int idx);
    float lower_bound(float tree_v, float tree_w, int idx);
    int knapsack();

};

LC::LC(int weight_max, std::vector<int> &weight, std::vector<int> &profit) {
    _capacity = weight_max;
    _size = profit.size();
    for (int i = 0; i < _size; ++i) {
        _arr.push_back(Item{.weight = static_cast<float>(weight[i]),
                           .profit = profit[i] ,
                           .idx = i});
    }
}


float LC::upper_bound(float tree_v, float tree_w, int idx) {
    float value = tree_v;
    float weight = tree_w;
    for (int i = idx; i < _size; i++) {
        if (weight + _arr[i].weight <= _capacity) {
            weight += _arr[i].weight;
            value -= _arr[i].profit;
        } else {
            value -= (float)(_capacity - weight) / _arr[i].weight * _arr[i].profit;
            break;
        }
    }
    return value;
}

float LC::lower_bound(float tree_v, float tree_w, int idx) {
    float value = tree_v;
    float weight = tree_w;
    for (int i = idx; i < _size; i++) {
        if (weight + _arr[i].weight <= _capacity) {
            weight += _arr[i].weight;
            value -= _arr[i].profit;
        } else {
            break;
        }
    }
    return value;
}


int LC::knapsack() {
    sort(_arr.begin(), _arr.end(), [&](Item& a, Item& b) { return a.profit / a.weight > b.profit / b.weight; });
    float min_lower_b = 0;
    float final_lower_b = INT_MAX;

    std::vector<bool> curr_path(_size, false);
    std::vector<bool> final_path(_size, false);
    std::priority_queue<Node, std::vector<Node>, comp>pq;
    Node left, right;
    Node current;
    cast_data(current, 0, 0, 0, 0, 0, 0);

    pq.push(current);

    while (!pq.empty()) {
        current = pq.top();
        pq.pop();
        if (current.upper_b > min_lower_b || current.upper_b >= final_lower_b) {
            continue;
        }
        if (current.level != 0) {
            curr_path[current.level - 1] = current.flag;
        }
        if (current.level == _size) {
            if (current.lower_b < final_lower_b)
                for (int i = 0; i < _size; i++) {
                    final_path[_arr[i].idx] = curr_path[i];
                }
            final_lower_b = std::min(current.lower_b, final_lower_b);
            continue;
        }
        int level = current.level;
        cast_data(right,
                  upper_bound(current.tree_v, current.tree_w, level + 1),
                  lower_bound(current.tree_v, current.tree_w, level + 1),
                  level + 1,
                  false,
                  current.tree_v,
                  current.tree_w);
        if (current.tree_w + _arr[current.level].weight <= _capacity) {
            left.upper_b = upper_bound(current.tree_v - _arr[level].profit,
                                       current.tree_w + _arr[level].weight,
                                       level + 1);
            left.lower_b = lower_bound(current.tree_v - _arr[level].profit,
                                       current.tree_w + _arr[level].weight,
                                       level + 1);
            cast_data(left,
                      left.upper_b,
                      left.lower_b,
                      level + 1,
                      true,
                      current.tree_v - _arr[level].profit,
                      current.tree_w + _arr[level].weight);
        } else {
            left.upper_b = left.lower_b = 1;
        }
        min_lower_b = std::min(min_lower_b, left.lower_b);
        min_lower_b = std::min(min_lower_b, right.lower_b);

        if (min_lower_b >= left.upper_b)
            pq.push(left);
        if (min_lower_b >= right.upper_b)
            pq.push(right);
    }

    if (final_lower_b == INT_MAX)
        final_lower_b = 0;
    return -final_lower_b;
}

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
