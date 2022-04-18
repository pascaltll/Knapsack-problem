#include <bits/stdc++.h>
#include<iostream>
#include <vector>


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

int brute_force(int weight_max, std::vector<int> &weight, std::vector<int> &value) {

    std::vector<std::vector<int>> K (value.size() + 1, std::vector<int>(weight_max + 1));
    for (int i = 0; i <= value.size(); ++i) {
        for (int w = 0; w <= weight_max; ++w) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (weight[i - 1] <= w) {
                K[i][w] = std::max(value[i - 1] +
                                   K[i - 1][w - weight[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }
    return K[value.size()][weight_max];
}
int main() {
    std::vector<int> val = { 10, 10, 12, 18 };
    std::vector<int> wt = { 2, 4, 6, 9 };
    std::vector<Item> arr;
    arr.push_back({ 2, 10, 0 });
    arr.push_back({ 4, 10, 1 });
    arr.push_back({ 6, 12, 2 });
    arr.push_back({ 9, 18, 3 });

    int capacity = 15;
    int n = val.size();
    int size = 4;
    std::cout << dinamic_programing(capacity, wt, val, n) << std::endl;
    std::cout << brute_force(capacity, wt, val) <<std::endl;
    LC branch_bound(capacity, wt, val);
    std::cout << branch_bound.knapsack() << std::endl;

    return 0;
}
