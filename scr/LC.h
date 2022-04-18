//
// Created by jctuesta on 19.04.2022.
//

#ifndef KNAPSACK_PROBLEM_LC_H
#define KNAPSACK_PROBLEM_LC_H
#include <vector>
#include <bits/stdc++.h>

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

void cast_data(Node& a, float upper_b, float lower_b, int level, bool flag, float tree_v, float tree_w);

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


#endif //KNAPSACK_PROBLEM_LC_H
