//llbb method
#include "LC.h"

void cast_data(Node& a, float upper_b, float lower_b, int level, bool flag, float tree_v, float tree_w) {
    a.upper_b = upper_b;
    a.lower_b = lower_b;
    a.level = level;
    a.flag = flag;
    a.tree_v = tree_v;
    a.tree_w = tree_w;
}

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
