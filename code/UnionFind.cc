#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
    vector<int> C;
    // Initialize n disjoint sets with UnionFind(n)
    UnionFind(int n) : C(n) { for (int i = 0; i < n; i++) C[i] = i; }
    int find(int x) { return (C[x] == x) ? x : C[x] = find(C[x]); }
    void merge(int x, int y) { C[find(x)] = find(y); } // Merge two sets
};
